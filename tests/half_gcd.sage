import matplotlib.pyplot as plt
import time
from sage.all import *

def special_shift(f,k):
    return f.shift(k-f.degree())

def strassen_multiply_2x2(A, B):
    """
    Multiplies two 2x2 matrices using the Strassen algorithm.
    """
    # Step 1: Create the seven products of the input matrices
    p1 = A[0,0] * (B[0,1] - B[1,1])
    p2 = (A[0,0] + A[0,1]) * B[1,1]
    p3 = (A[1,0] + A[1,1]) * B[0,0]
    p4 = A[1,1] * (B[1,0] - B[0,0])
    p5 = (A[0,0] + A[1,1]) * (B[0,0] + B[1,1])
    p6 = (A[0,1] - A[1,1]) * (B[1,0] + B[1,1])
    p7 = (A[0,0] - A[1,0]) * (B[0,0] + B[0,1])

    # Step 2: Compute the elements of the output matrix
    C = Matrix(A.base_ring(), 2, 2)
    C[0,0] = p5 + p4 - p2 + p6
    C[0,1] = p1 + p2
    C[1,0] = p3 + p4
    C[1,1] = p5 + p1 - p3 - p7

    return C

# NAIVE ALGORITHM

def EuclidAlgorithm(a,b):
    r0 = a
    r1 = b
    i = 1
    while r1 != 0:
        # Note: the next three lines could be done shortly, hiding the temporary,
        # using:   (q, r1), r0 = r0.quo_rem(r1), r1
        tmp = r0
        r0 = r1
        (q,r1) = tmp.quo_rem(r1)
        i += 1
    return r0

def ExtendedEuclidAlgorithm(a,b):

    r0, u0, v0 = a, 1, 0
    r1, u1, v1 = b, 0, 1
    i=1
    while r1 != 0:
        # Note: the next three lines could be done shortly, hiding the temporary,
        # using:   (q, r1), r0 = r0.quo_rem(r1), r1
        tmp = r0
        r0 = r1
        (q,r1) = tmp.quo_rem(r1)
        # Note: the next three lines could be done shortly, hiding the temporary,
        # using:    u1, u0 = u0 - q*u1, u1
        tmp = u1
        u1 = u0 - q*u1
        u0 = tmp
        # Note: the next three lines could be done shortly, hiding the temporary,
        # using:    v1, v0 = v0 - q*v1, v1
        tmp = v1
        v1 = v0 - q*v1
        v0 = tmp
        i += 1

    return (r0, u0, v0)


def random_matrix(ring,i):
    A = Matrix.random(ring, 2, 2, degree=i)
    B = Matrix.random(ring, 2, 2, degree=i)
    return A,B


# FAST HALF GCD

def fast_half_gcd(r0, r1, k):
    """
    Function to calculate the half-gcd as seen in
    Gathen Gehrard - Modern Computer Algebra on page 321.
    """
    # polynomial ring
    pring = r0.parent()

    # Check if deg r1 < deg r0
    n0 = r0.degree()
    n1 = r1.degree()

    # Step 1
    if r1 == 0 or k < n0 - n1:
        return 0, [], matrix.identity(pring, 2)
    elif k == 0 and n0 - n1 == 0:
        lead_coeff = r0.leading_coefficient() // r1.leading_coefficient()
        return 1, [lead_coeff], matrix(pring, 2, 2, [[0, 1], [1, -lead_coeff]])
    if n1 > n0:
        raise ValueError("The degree of r1 must be lower than the degree of r0.")
    if k > n0 or k < 0:
        raise ValueError("Wrong value for k")
    # Step 2
    d = ceil(k/2)
    # Step 3
    eta, q, R = fast_half_gcd(special_shift(r0,2*d-2), special_shift(r1,2*d-2-(n0-n1)), d-1)
    # Step 4
    j = eta + 1
    if (R[1,1] == 1):
        sigma = 0
    else:
        sigma = R[1,1].degree()
    res_r = R * matrix(pring, 2, 1, [[special_shift(r0,2*k)], [special_shift(r1,2*k-(n0-n1))]])
    r_j_1 = res_r[0,0]
    r_j = res_r[1,0]
    r = matrix(pring, 2, 1, [[r_j_1], [r_j]])
    res_n = matrix([[r_j_1.degree()], [r_j.degree()]])
    # Step 5
    if r_j == 0 or k < sigma + res_n[0,0] - res_n[1,0]:
        return j - 1, q[0:j-1], R
    # Step 6
    q.append(r_j_1 // r_j)
    Qj = matrix(pring, [[0, 1], [1, -q[-1]]])
    r_j_plus_one = r_j_1 % r_j
    n_j_plus_one = r_j_plus_one.degree()
    # Step 7
    d_star = k - sigma - (res_n[0,0] - res_n[1,0])
    # Step 8
    eta_2, q_2, S = fast_half_gcd(special_shift(r_j,2*d_star), special_shift(r_j_plus_one,2*d_star-(res_n[1,0]-n_j_plus_one)), d_star)
    # Step 9
    h = eta_2 + j
    return h, q[0:h] + q_2, S * Qj * R

def fast_extended_euclidean_algorithm(f, g, k):
    h, q, R = fast_half_gcd(f, g, k)
    return q[0:h], R[0][0], R[0][1], R[0][0] * f + R[0][1] * g

# HALF GCD WITH STRASSEN

def fast_half_gcd_strassen(r0, r1, k):
    """
    Function to calculate the half-gcd as seen in
    Gathen Gehrard - Modern Computer Algebra on page 321.
    """
    # polynomial ring
    pring = r0.parent()

    # Check if deg r1 < deg r0
    n0 = r0.degree()
    n1 = r1.degree()

    # Step 1
    if r1 == 0 or k < n0 - n1:
        return 0, [], matrix.identity(pring, 2)
    elif k == 0 and n0 - n1 == 0:
        lead_coeff = r0.leading_coefficient() // r1.leading_coefficient()
        return 1, [lead_coeff], matrix(pring, 2, 2, [[0, 1], [1, -lead_coeff]])
    if n1 > n0:
        raise ValueError("The degree of r1 must be lower than the degree of r0.")
    if k > n0 or k < 0:
        raise ValueError("Wrong value for k")
    # Step 2
    d = ceil(k/2)
    # Step 3
    eta, q, R = fast_half_gcd_strassen(special_shift(r0,2*d-2), special_shift(r1,2*d-2-(n0-n1)), d-1)
    # Step 4
    j = eta + 1
    if (R[1,1] == 1):
        sigma = 0
    else:
        sigma = R[1,1].degree()
    res_r = R * matrix(pring, 2, 1, [[special_shift(r0,2*k)], [special_shift(r1,2*k-(n0-n1))]])
    r_j_1 = res_r[0,0]
    r_j = res_r[1,0]
    r = matrix(pring, 2, 1, [[r_j_1], [r_j]])
    res_n = matrix([[r_j_1.degree()], [r_j.degree()]])
    # Step 5
    if r_j == 0 or k < sigma + res_n[0,0] - res_n[1,0]:
        return j - 1, q[0:j-1], R
    # Step 6
    q.append(r_j_1 // r_j)
    Qj = matrix(pring, [[0, 1], [1, -q[-1]]])
    r_j_plus_one = r_j_1 % r_j
    n_j_plus_one = r_j_plus_one.degree()
    # Step 7
    d_star = k - sigma - (res_n[0,0] - res_n[1,0])
    # Step 8
    eta_2, q_2, S = fast_half_gcd_strassen(special_shift(r_j,2*d_star), special_shift(r_j_plus_one,2*d_star-(res_n[1,0]-n_j_plus_one)), d_star)
    # Step 9
    h = eta_2 + j
    return h, q[0:h] + q_2, strassen_multiply_2x2(S, strassen_multiply_2x2(Qj, R))

def fast_extended_euclidean_algorithm_strassen(f, g, k):
    h, q, R = fast_half_gcd_strassen(f, g, k)
    return q[0:h], R[0][0], R[0][1], R[0][0] * f + R[0][1] * g


# TIME MEASURMENTS

pring.<x> = PolynomialRing(GF(997))

y_xgcd = 0
y_naive = 0
y_half_fast_gcd = 0
y_half_fast_gcd_strassen = 0


for i in range(1000, 2000000, 1000):
    A = pring.random_element(i)
    B = pring.random_element(i-1)

    # XGCD
    start_time = time.time()
    r = xgcd(A, B)
    end_time = time.time()
    y_xgcd = end_time - start_time

    # NAIVE
    start_time = time.time()
    r = ExtendedEuclidAlgorithm(A, B)
    end_time = time.time()
    y_naive = end_time - start_time
    
    # fast_half_gcd
    start_time = time.time()
    r = fast_extended_euclidean_algorithm(A, B, i)
    end_time = time.time()
    y_half_fast_gcd = end_time - start_time

    # fast_half_gcd_strassen
    start_time = time.time()
    r = fast_extended_euclidean_algorithm_strassen(A, B, i)
    end_time = time.time()
    y_half_fast_gcd_strassen = end_time - start_time

    print(i, " ", y_xgcd, " ", y_naive, " ", y_half_fast_gcd, " ", y_half_fast_gcd_strassen)

y_strassen = 0
y_mult = 0
# TIME MEASURMENTS FOR MULTIPLICATION
for i in range(1000, 2000000, 1000):

    # GENERATE TWO 2x2 RANDOM MATRICES A AND B
    A , B = random_matrix(pring,i)

    # NAIVE
    start_time = time.time()
    r2 = matrix(A)*matrix(B)
    end_time = time.time()
    y_mult = end_time - start_time
    
    # STRASSEN
    start_time = time.time()
    r = strassen_multiply_2x2(A, B)
    end_time = time.time()
    y_strassen = end_time - start_time
    
    print(i, " ", y_mult, " ", y_strassen)


import matplotlib.pyplot as plt
import time
def special_shift(f,k):
    return f.shift(k-f.degree())

def fast_half_gcd(r0, r1, k):
    """
    Function to calculate the half-gcd as seen in
    Gathen Gehrard - Modern Computer Algebra on page 321.
    """
    # Check if deg r1 < deg r0
    n0 = r0.degree()
    n1 = r1.degree()
    #print("k:",k)
    #print("n0:",n0)
    #print("n1:",n1)
    #if (n0 == -1):
    #    n0 = 0
    # Step 1
    #print("k:",k, "n0 - n1", n0 - n1)
    if r1 == 0 or k < n0 - n1:
        return 0, [], matrix.identity(2)
    elif k == 0 and n0 - n1 == 0:
        lead_coeff = r0.leading_coefficient() // r1.leading_coefficient()
        return 1, [lead_coeff], matrix([[0, 1], [1, -lead_coeff]], ring=r0.parent())
    if n1 > n0:
        raise ValueError("The degree of r1 must be lower than the degree of r0.")
    if k > n0 or k < 0:
        raise ValueError("Wrong value for k")
    # Step 2
    d = ceil(k/2)
    # Step 3
    #print("enter step 3")
    eta, q, R = fast_half_gcd(special_shift(r0,2*d-2), special_shift(r1,2*d-2-(n0-n1)), d-1)
    #print(eta, q, R)
    # Step 4
    j = eta + 1
    #print("R: ", R[1][1])
    if (R[1][1] == 1):
        sigma = 0
    else:
        sigma = R[1][1].degree()
    #print(sigma)
    res_r = R * matrix([[special_shift(r0,2*k)], [special_shift(r1,2*k-(n0-n1))]], ring=r0.parent())
    r_j_1 = res_r[0][0]
    #print("r_j_1:", r_j_1)
    r_j = res_r[1][0]
    #print("r_j:", r_j)
    r = matrix([[r_j_1], [r_j]], ring=r0.parent())
    res_n = matrix([[r_j_1.degree()], [r_j.degree()]])
    # Step 5
    if r_j == 0 or k < sigma + res_n[0][0] - res_n[1][0]:
        return j - 1, q[0:j-1], R
    # Step 6
    q.append(r_j_1 // r_j)
    Qj = matrix([[0, 1], [1, -q[-1]]], ring=r0.parent())
    r_j_plus_one = r_j_1 % r_j
    n_j_plus_one = r_j_plus_one.degree()
    # Step 7
    d_star = k - sigma - (res_n[0][0] - res_n[1][0])
    # Step 8
    eta_2, q_2, S = fast_half_gcd(special_shift(r_j,2*d_star), special_shift(r_j_plus_one,2*d_star-(res_n[1][0]-n_j_plus_one)), d_star)
    S = matrix(S, ring=r0.parent())
    # Step 9
    h = eta_2 + j
    return h, q[0:h] + q_2, S * Qj * R

def fast_extended_euclidean_algorithm(f, g, k):
    h, q, R = fast_half_gcd(f, g, k)
    return q, R[:0, :0], R[:0, :1], R[0][0] * f + R[0][1] * g

pring.<x> = PolynomialRing(GF(997))

x_values = []
y_values = []

for i in range (100000,1000000,100000):
    A = pring.random_element(i)
    B = pring.random_element(i-1)

    start_time = time.time()
    r = fast_half_gcd(A, B, i)
    end_time = time.time()
    execution_time = end_time - start_time
    x_values.append(i)
    y_values.append(execution_time)

plt.plot(x_values, y_values)
plt.title("Temps d'execution de fast_half_gcd en fonction du degré du polynome")
plt.xlabel("degré de A et B")
plt.ylabel("Temps d'execution (secondes)")
plt.show()

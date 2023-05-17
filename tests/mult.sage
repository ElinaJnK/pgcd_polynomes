import time

def random_matrix(ring,i):
    A = Matrix.random(ring, 2, 2, degree=i)
    B = Matrix.random(ring, 2, 2, degree=i)
    return A,B

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

pring.<x> = PolynomialRing(GF(997))

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

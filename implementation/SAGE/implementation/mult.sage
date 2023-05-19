import time

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

list_degs = list(range(1000, 100000, 1000)) \
        + list(range(100000, 1000000, 5000)) \
        + list(range(1000000, 10000000, 25000))

# TIME MEASURMENTS FOR MULTIPLICATION
for i in list_degs:

    # GENERATE TWO 2x2 RANDOM MATRICES A AND B
    A = Matrix.random(pring, 2, 2, degree=i)
    B = Matrix.random(pring, 2, 2, degree=i)

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

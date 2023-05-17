from half_gcd import strassen_multiply_2x2
from half_gcd import random_matrix
import time
from sage.all import *
# TIME MEASURMENTS

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

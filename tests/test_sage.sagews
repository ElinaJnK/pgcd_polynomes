# This was done on cocalc.com and does not work yet because
# I am not really sure I understand everything

def truncate_polynomial(A, k):
    """ This function truncates the polynomial as defined in 
        Gathen Gehrard - Modern Computer Algebra.
        See page 314 """
    list_coeffs = A.coefficients()
    len_list = len(list_coeffs)
    # our new truncated polynomial
    A_new = 0
    while (k > 0) and len_coeffs > 0:
        f = list_coeffs[len_coeffs - 1][0]
        len_coeffs -= 1
        A_new += f*(x^k)
    return A_new

def fast_half_gcd(A, B, k):
	""" (TO DO) Funtion to calculate the half-gcd as see in
		Gathen Gehrard - Modern Computer Algebra.
	"""
    # p, g polynomials
    # check if deg B < deg A
    deg_a = A.degree()
    deg_b = B.degree()
    if deg_b > deg_a:
        raise Exception("The degree of B must be lower than the degree of A.\n Remeber, the call to the function is fast_half_gcd(A,B)")
    if k > deg_a:
        raise Exception("Wrong value for k")
    m = ceil(n/2)
    # STEP 1
    if (deg_b < m) or (k < deg_a - deg_b):
        return 0, "", matrix.identity(2)
    elif (k == 0) or (deg_a - deg_b == 0):
        # should we return a list of leading coeffs here ?
        lead_coeff = A.leading_coefficient() / B.leading_coefficient()
        return 1, lead_coeff, matrix([[0,1],[1,-lead_coeff]])
    # STEP 3
    """ This call returns eta(d - 1), q_1, ..., q_eta(d - 1) and R = Q_eta(d - 1) ... Q_1"""
    eta, q, R = fast_half_gcd(truncate_polynomial(A, 2 * d - 2), truncate_polynomial(B, 2 * d - 2 - (deg_a - deg_b)), d - 1)
    # STEP 4
    j = eta + 1
    # I do not really understand what it means
    sigma = R.degree()
    res_r = R * matrix([truncate_polynomial(A, 2 * k), truncate_polynomial(B, 2 * k - (deg_A - deg_B))])
    r_j_1 = res_r[0]
    r_j = res_r[1]
    r = matrix([r_j_1, r_j])
    res_n = matrix([r_j_1.degree(), r_j.degree()])
    # STEP 5
    # i have no idea how to truncate q to q1, ..., q_j-1
    if r_j == 0 or k < sigma + res_n[0] - res_n[1]:
        return j - 1, q[j - 1:], R
    # STEP 6
    q[j] = r_j_1 / r_j
    r_j_plus_one = r_j_1 % r_j
    n_j_plus_one = r_j_plus_one.degree()
    
    
    

R.<x> = PolynomialRing(QQ)
A = x^2 + 3*x + 1; A.degree(); A.leading_coefficient()
B = (x+1) * (x+2)
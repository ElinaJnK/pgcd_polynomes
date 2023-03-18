def fast_half_gcd(A, B, k):
    """
    Function to calculate the half-gcd as seen in
    Gathen Gehrard - Modern Computer Algebra on page 321.
    TODO: Change all truncate_polynomial to truncate() function
    in sage (probably safer)
    """
    # p, g polynomials
    # check if deg B < deg A
    deg_a = A.degree()
    deg_b = B.degree()
    if deg_b > deg_a:
        raise Exception("The degree of B must be lower than the degree of A.\n Remeber, the call to the function is fast_half_gcd(A,B)")
    if k > deg_a:
        raise Exception("Wrong value for k")
    m = ceil(deg_a/2)
    # STEP 1
    if (deg_b < m) or (k < deg_a - deg_b):
        return 0, "", matrix.identity(2)
    elif (k == 0) or (deg_a - deg_b == 0):
        # change leading_coefficient (might make a error)
        lead_coeff = A.leading_coefficient() / B.leading_coefficient()
        return 1, lead_coeff, matrix([[0,1],[1,-lead_coeff]])
    # STEP 3
    """ This call returns eta(d - 1), q_1, ..., q_eta(d - 1) and R = Q_eta(d - 1) ... Q_1"""
    d = ceil((deg_a + deg_b - k)/2)
    eta, q, R = fast_half_gcd(A.truncate(2 * d - 2), B.truncate(2 * d - 2 - (deg_a - deg_b)), d - 1)
    # STEP 4
    j = eta + 1
    sigma = R.degree()
    res_r = R * matrix([A.truncate(2 * k), B.truncate(2 * k - (deg_a - deg_b))])
    r_j_1 = res_r[0]
    r_j = res_r[1]
    r = matrix([r_j_1, r_j])
    res_n = matrix([r_j_1.degree(), r_j.degree()])
    # STEP 5
    if r_j == 0 or k < sigma + res_n[0] - res_n[1]:
        return j - 1, q[0:j-1], R
    # STEP 6
    q[j] = r_j_1 / r_j
    Qj = matrix([[0,1], [1, -q[j]]])
    r_j_plus_one = r_j_1 % r_j
    n_j_plus_one = r_j_plus_one.degree()
    # STEP 7
    d_star = k - sigma - (res_n[0] - res_n[1])
    # STEP 8
    eta_2, q_2, S = fast_half_gcd(r_j.truncate(2 * d_star), r_j_plus_one.truncate(2 * d_star - (res_n[1] - n_j_plus_one)), d_star)
    # STEP 9
    h = eta_2 + j
    return h, q[0:j] + q_2, S * Qj * R

R.<x> = PolynomialRing(QQ)
A = x^2 + 3*x + 1;
B = (x+1) * (x+2)
fast_half_gcd(A, B, 1)
gcd(A, B)










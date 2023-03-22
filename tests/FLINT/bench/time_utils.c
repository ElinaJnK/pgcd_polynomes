/**
 * This code was made to measure FLINT performance over NTL, however it produces a segfault
 * To compile, simply run make and then ./flint
 */
#include "../include/time_utils.h"
#include <flint/nmod_poly.h>
#include <flint/profiler.h>

/**
 * Function to generate random polynomials
 */
void _nmod_vec_rand(mp_ptr vec,
            		flint_rand_t state,
            		slong len,
            		nmod_t mod)
{
    for (slong i = 0; i < len; i++)
        vec[i] = n_randint(state, mod.n);
}

void nmod_poly_rand(nmod_poly_t pol, flint_rand_t state, slong len)
{
    if (len <= 0)
        nmod_poly_zero(pol);
    else
    {
        nmod_poly_fit_length(pol, len);
        _nmod_vec_rand(pol->coeffs, state, len, pol->mod);
        pol->length = len;
        _nmod_poly_normalise(pol);
    }
}

/**
 * Choose the operation you want to conduct.
 */
double su_operation_time(int choice_op, nmod_poly_t poly_A,nmod_poly_t poly_B, int n, long k)
{
	// might eventually show the polynome with nmod_poly_print(product);
	long thres = 500; // threshold, millisecond
	long ts = 0; // total time, millisecond
	long iter = 0;
	// for walltime
	timeit_t tt;
	//clock_t start, end;
	// the same results could be stored in sum and gcd, but i think it's clearer that way
	nmod_poly_t sum, mul, gcd, divisor, quotient, remainder, g, s, t;
	flint_rand_t state;
	flint_randinit(state);
	nmod_poly_init(sum, n);
	nmod_poly_init(mul, n);
	nmod_poly_init(gcd, n);
	nmod_poly_init(divisor, n);
	nmod_poly_init(quotient, n);
	nmod_poly_init(remainder, n);
	nmod_poly_init(g, n);
	nmod_poly_init(s, n);
	nmod_poly_init(t, n);

	while (ts < thres && iter < 100000)
	{
		//start = flint_randint(state);
		nmod_poly_rand(poly_A, state, k);
		choice_op == 3 ? nmod_poly_rand(poly_B, state, 2*k) : nmod_poly_rand(poly_B, state, k);
		timeit_start(tt);
		//start = clock();
		switch(choice_op)
		{
			case 0:
				nmod_poly_add(sum, poly_A, poly_B);
				break;
			case 1:
				nmod_poly_mul(mul, poly_A, poly_B);
				break;
			case 2:
				nmod_poly_gcd(gcd, poly_A, poly_B);
				break;
			case 3:
				nmod_poly_divrem(quotient, remainder, poly_A, poly_B);
				break;
			case 4:
				nmod_poly_xgcd(g, s, t, poly_A, poly_B);
				break;
			default:
				printf("There seems to be an error in the choice of operation.\n");
				return (0);
		}
		//end = clock();
		//ts += ((double) (end - start)) / CLOCKS_PER_SEC;
		timeit_stop(tt);
		ts += tt->cpu;
		++iter;
	}

	nmod_poly_clear(sum);
	nmod_poly_clear(mul);
	nmod_poly_clear(gcd);
	nmod_poly_clear(quotient);
	nmod_poly_clear(remainder);
	nmod_poly_clear(g);
	nmod_poly_clear(s);
	nmod_poly_clear(t);

	return ((double)ts / (1000*iter));
}

/**
 * Function to initialize parameters
 */
void	su_choice_params_flint(long *d, long *b, int *choice_op, int ac, char **av)
{
	if (ac > 1)
    {
		if (av[1])
			*choice_op = atoi(av[1]);
		if (av[2])
        	*d = atoi(av[2]);
		if (av[3])
        	*b = atoi(av[3]);
    } else {
		printf("By default, the polynome is generated with FFT, the operation is the GCD,\nthe degree of the polynomial is set to 1000,	\
		\nand the number of bits is set to 60.\nIf you wish to change those values	\
		\nplease execute the program with : \n\t./flint <choice of operation> <degree of polynomial> <number of bits> <file to save results>	\
		\n<choice of operation> can be:	\
		\n\t- 0 : addition	\
		\n\t- 1 : multiplication	\
		\n\t- 2 : GCD	\
		\n\t- 3 : division	(divided by 2 by default (TODO))\
		\n\t- 4 : XGCD \
		\nFor example, you could try ./flint 0 1 1000 60\n");
        *d = 1000;
        *b = 60;
		*choice_op = 2;
	}
}

int main(int ac, char **av)
{
	// generate our polynome
	nmod_poly_t poly_A;
	nmod_poly_t poly_B;
	mp_limb_t n;
	long num_bits, degree, k;
	double ti_add, ti_mult, ti_div, ti_gcd, ti_xgcd;
	int choice_op;
	FILE *file_gcd_xgcd, *file_mult_div;
	flint_rand_t state;
	flint_randinit(state);

	su_choice_params_flint(&degree, &num_bits, &choice_op, ac, av);
	n = n_randprime(state, num_bits, 1);
	printf("n: %lu\n", n);
	nmod_poly_init(poly_A, n);
	nmod_poly_init(poly_B, n);

	//state = flint_rand_alloc();
	// file to write results to (eventually include that in choice_params)
	file_gcd_xgcd = fopen("results_gcd_xgcd_flint.txt", "a");
	file_mult_div = fopen("results_mult_div_flint.txt", "a");
    if (!file_gcd_xgcd || !file_mult_div)
    {
        printf ("File does not exist");
        return 0;
    }
	for (k = degree; k <= 100000000; k += 1000)
	{
		//ti_add = su_operation_time(0, poly_A, poly_B, n);
		ti_mult = su_operation_time(1, poly_A, poly_B, n, k);
		ti_gcd = su_operation_time(2, poly_A, poly_B, n, k);
		ti_div = su_operation_time(3, poly_A, poly_B, n, k);
		ti_xgcd = su_operation_time(4, poly_A, poly_B, n, k);
		printf("added : %ld %.9f %.9f %.9f %.9f\n", k, ti_mult, ti_div, ti_gcd, ti_xgcd);
		fprintf(file_gcd_xgcd, "%ld %.9f %.9f\n", k, ti_gcd, ti_xgcd);
		fflush(file_gcd_xgcd);
		fprintf(file_mult_div, "%ld %.9f %.9f\n", k, ti_mult, ti_div);
		fflush(file_mult_div);
	}
	// free the polynome
	nmod_poly_clear(poly_A);
	nmod_poly_clear(poly_B);
	//flint_rand_free(state);
	fclose(file_gcd_xgcd);
	fclose(file_mult_div);
	flint_randclear(state);
	return (0);
}

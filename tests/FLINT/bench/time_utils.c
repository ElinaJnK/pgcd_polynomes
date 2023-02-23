/**
 * This code was made to measure FLINT performance over NTL, however it produces a segfault
 * To compile, simply run make and then ./flint
 */
#include "../include/time_utils.h"

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
		//if (av[5])
        //	std::string charactersFilename(av[5]);

    } else {
		printf("By default, the polynome is generated with FFT, the operation is the GCD,\nthe degree of the polynomial is set to 1000,	\
		\nand the number of bits is set to 60.\nIf you wish to change those values	\
		\nplease execute the program with : \n\t./graph <choice of operation> <degree of polynomial> <number of bits> <file to save results (TODO)>	\
		\n<choice of operation> can be:	\
		\n\t- 0 : addition	\
		\n\t- 1 : multiplication	\
		\n\t- 2 : GCD	\
		\n\t- 3 : division	(divided by 2 by default (TODO))\
		\n\t- 4 : XGCD \
		\nFor example, you could try ./ntl 0 1 1000 60\n");
        *d = 1000;
        *b = 60;
		*choice_op = 2;
	}
}

int main(int ac, char **av)
{
	// our polynome mod n
	fmpz_mod_poly_t mpt_poly;
	// our modulo
	fmpz_mod_ctx_t mct;
	// i don't really know but for bits (?)
	const fmpz_t n;
	long num_bits, degree;
	int choice_op;

	su_choice_params_flint(&num_bits, &degree, &choice_op, ac, av);

	// init fmpz_t (just a slong), the value is set to zero
	fmpz_init(n);
	for (long i = 0; i < num_bits; i++)
	{
		// set bit index i of n
		// does this function just set everything to one ?
		fmpz_setbit(n, i);
	}
	// the context object for arithmetic modulo integers
	// initialize ctx for arithmetic modulo n, which is expected to be positive
	fmpz_mod_ctx_init(mct, n);

	// Initialises poly with space for at least alloc coefficients and sets 
	// the length to zero. The allocated coefficients are all set to zero.
	fmpz_mod_poly_init2(mpt_poly, degree+1, mct);

	for (long i = 0; i <= degree; i++) {
		fmpz_mod_poly_set_coeff_fmpz(mpt_poly, i, n, mct);
	}
	// free everything
	fmpz_mod_poly_clear(n, mct);
	fmpz_mod_ctx_clear(n);
	fmpz_clear(n);
}

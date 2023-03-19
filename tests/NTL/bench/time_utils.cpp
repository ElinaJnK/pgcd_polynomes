/***
 * To compile run 
 * g++ -g -O2 -std=c++11 -pthread  big_int.cpp -o big_int -lntl -lgmp -lm
 * If you are missing the gmp library: https://libntl.org/doc/tour-unix.html
 * when you do make install (from here https://libntl.org/doc/tour-gmp.html) 
 * do not forget to add 'sudo' before make.
 * ***/

#include "../include/time_utils.h"

/**
 * Write collected data in a file. The data will be written at the end of the file.
 */
void	su_write_in_file(int degree, double ti_add, double ti_mult, double ti_div, double ti_gcd, double ti_xgcd)
{
	ofstream outdata;

	outdata.open("res_all.txt", std::ios::app);
	if (!outdata)
	{
		cerr << "Error, file could not be opened." << endl;
		exit(1);
	}
	outdata << degree << " " << ti_add << " " << ti_mult << " " << ti_div << " " << ti_gcd << " " << ti_xgcd << endl;
	outdata.close();
}

/**
 * Choose the operation you want to conduct.
 */
long su_operation_time(int choice_op, zz_pX P, zz_pX G, int d, int n=2)
{
	double thres = 0.5;
    double t = 0.0, start = 0.0;
	int iter = 0;
	zz_pX g, u, v, reste;
	while (t < thres && iter < 100000)
	{
        random(P, d+1);
        random(G, d+1);
        start = GetWallTime();
		switch(choice_op)
		{
			case 0:
				add(g, P, G);
				break;
			case 1:
				mul(g, P, G);
				break;
			case 2:
				g = GCD(P, G);
				break;
			case 3:
				DivRem(g, reste, P, G);
				break;
			case 4:
				XGCD(g, u, v, P, G);
				break;
			default:
				printf("There seems to be an error in the choice of operation.\n");
				return (0);
		}
		t += GetWallTime() - start;
    	++iter;
	}
	
	std::cout << "degree: "<< d << ", bench poly power NTL:" << (t / iter) << "s" << std::endl;
	return (t/iter);
}

/**
 * Function to initialize parameters
 */
void	su_choice_params(long *d, long *b, long *p, int *choice_p, int *choice_op, int ac, char **av)
//, char **file)
{
	if (ac > 1)
    {
		if (av[1])
			*choice_p = atoi(av[1]);
		if (av[2])
			*choice_op = atoi(av[2]);
		if (av[3])
        	*d = atoi(av[3]);
		if (av[4])
        	*b = atoi(av[4]);
		//if (av[5])
        //	std::string charactersFilename(av[5]);

    } else {
		printf("By default, the polynome is generated with FFT, the operation is the GCD,\nthe degree of the polynomial is set to 1000,	\
		\nand the number of bits is set to 60.\nIf you wish to change those values	\
		\nplease execute the program with : \n\t./graph <choice of implementation> <choice of operation> <degree of polynomial> <number of bits> <file to save results (TODO)>	\
		\n<choice of implementation> can either be\n\t- 0 : using a FFT generated polynomial	\
		\n\t- 1 : using a bits generated polynomial	\
		\n<choice of operation> can be:	\
		\n\t- 0 : addition	\
		\n\t- 1 : multiplication	\
		\n\t- 2 : GCD	\
		\n\t- 3 : division	(divided by 2 by default (TODO))\
		\n\t- 4 : XGCD \
		\nFor example, you could try ./ntl 0 1 1000 60\n");
        *d = 1000;
        *b = 60;
		*choice_p = 0;
		*choice_op = 2;
    }
}

int	main(int ac, char **av)
{
    // faire fichier avec valeurs
    // analyse de l'existant
    long d, b, p;
	int choice_p, choice_op;
	su_choice_params(&d, &b, &p, &choice_p, &choice_op, ac, av);
	//printf("file : %s\n", *file);
    zz_pX c;
	switch (choice_p)
	{
		case 0:
			zz_p::FFTInit(0); //nbres premiers FFT, premier de cette liste, 60 bits -> tandis que celui la est directement un nbre FFT
			p = zz_p::modulus();
			printf("Polynome generated with FFT prime\n");
			break;
		case 1:
			p = GenPrime_long(b); //nbre de bits -> se repose sur plusieurs nbre FFT //lim = 60 61 
			zz_p::init(p);
			printf("Polynome generated with GenPrime\n");
			break;
		default:
			zz_p::FFTInit(0);
			long p = zz_p::modulus();
	}
	zz_pX P;
	zz_pX G;
	long k;
	double ti_add, ti_mult, ti_div, ti_gcd, ti_xgcd;
	// generate graphs quicker
	for (k = d; k <= 10000000; k += 1000)
	{
		ti_add = su_operation_time(0, P, G, k);
		ti_mult = su_operation_time(1, P, G, k);
		ti_gcd = su_operation_time(2, P, G, k);
		ti_div = su_operation_time(3, P, G, k);
		ti_xgcd = su_operation_time(4, P, G, k);
		su_write_in_file(d, ti_add, ti_mult, ti_div, ti_gcd, ti_xgcd);
	}
    return (0);
}//complexity : O(dlog(d)) -> methodes a base de FFT
//divRem et variables en zzpx refaire eea
//mesurer efficacite

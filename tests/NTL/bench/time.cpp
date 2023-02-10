/***
 * To compile run 
 * g++ -g -O2 -std=c++11 -pthread  big_int.cpp -o big_int -lntl -lgmp -lm
 * If you are missing the gmp library: https://libntl.org/doc/tour-unix.html
 * when you do make install (from here https://libntl.org/doc/tour-gmp.html) 
 * do not forget to add 'sudo' before make.
 * ***/

#include "../include/time.h"

/**
 * Choose the operation you want to conduct.
 */
long	su_operation_time(int choice_op, zz_pX P, zz_pX G, int d)
{
	double thres = 0.5;
    double t = 0.0, start = 0.0;
	int iter = 0;
	zz_pX g;
	switch(choice_op)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			while (t < thres && iter < 100000)
    		{
        		random(P, d+1);
        		random(G, d+1);
        		start = GetWallTime();
       			g = GCD(P,G);
        		t += GetWallTime() - start;
        		++iter;
			}
			break;
		default:
			return (0);
	}
	std::cout << "degree: "<< d << ", bench poly power NTL:" << (t / iter) << "s" << std::endl;
	return (0.0);
}

/**
 * Function to initialize parameters
 */
void	su_choice_params(long *d, long *b, long *p, int *choice_p, int *choice_op, int ac, char **av)
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
    } else {
		printf("By default, the polynome is generated with FFT, the operation is the GCD,\nthe degree of the polynomial is set to 1000,	\
		\nand the number of bits is set to 60.\nIf you wish to change those values	\
		\nplease execute the program with : \n\t./graph <choice of implementation> <choice of operation> <degree of polynomial> <number of bits>	\
		\n<choice of implementation> can either be\n\t- 0 : using a FFT generated polynomial	\
		\n\t- 1 : using a bits generated polynomial	\
		\n<choice of operation> can be:	\
		\n\t- 0 : addition	\
		\n\t- 1 : multiplication	\
		\n\t- 2 : GCD	\
		\n\t- 3 : division	\n");
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
    zz_pX c;
	switch (choice_p)
	{
		case 0:
			zz_p::FFTInit(0); //nbres premiers FFT, premier de cette liste, 60 bits -> tandis que celui la est directement un nbre FFT
			p = zz_p::modulus();
			printf("Polynome generated with FFT\n");
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
	su_operation_time(choice_op, P, G, d);
	//random(P,d);
	//random(G,d);
	//auto start = std::chrono::system_clock::now();
	//c = GCD(P,G);
	//auto end = std::chrono::system_clock::now();
    return 0;
}//complexity : O(dlog(d)) -> methodes a base de FFT
//divRem et variables en zzpx refaire eea
//mesurer efficacite
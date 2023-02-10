/***
 * To compile run 
 * g++ -g -O2 -std=c++11 -pthread  big_int.cpp -o big_int -lntl -lgmp -lm
 * If you are missing the gmp library: https://libntl.org/doc/tour-unix.html
 * when you do make install (from here https://libntl.org/doc/tour-gmp.html) 
 * do not forget to add 'sudo' before make.
 * ***/

#include "../include/time.h"

int main(int argc, char **argv)
{
    // faire fichier avec valeurs
    // analyse de l'existant
    long d, b, p;
	int choice_p, choice_op;
    if (argc > 1)
    {
		if (argv[1])
			choice_p = atoi(argv[1]);
		if (argv[2])
			choice_op = atoi(argv[2]);
		if (argv[3])
        	d = atoi(argv[3]);
		if (argv[4])
        	b = atoi(argv[4]);
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
        d = 1000;
        b = 60;
		choice_p = 0;
		choice_op = 2;
    }
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
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
	zz_pX g;
	//random(P,d);
	//random(G,d);
	//auto start = std::chrono::system_clock::now();
	//c = GCD(P,G);
	//auto end = std::chrono::system_clock::now();
    double thres = 0.5;
    double t = 0.0, start = 0.0;
	int iter = 0;
    while (t < thres && iter < 100000)
    {
        random(P, d+1);
        random(G, d+1);
        start = GetWallTime();
        g = GCD(P,G);
        t += GetWallTime() - start;
        ++iter;
    }
	std::cout << "degree: "<< d << " and p = "<< b << ", bench poly power NTL:" << (t / iter) << "s" << std::endl;
	//std::chrono::duration<double> elapsed_seconds = end-start;    //}
	//std::cout << "degre: "<< d << "  and p = "<< b << ",  elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    return 0;
}//complexity : O(dlog(d)) -> methodes a base de FFT
//divRem et variables en zzpx refaire eea
//mesurer efficacite
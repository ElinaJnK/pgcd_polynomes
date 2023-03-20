#ifndef TIME_H
#define TIME_H

# include <NTL/ZZ.h>
# include <NTL/lzz_p.h>
# include <NTL/lzz_pX.h>
# include <stdlib.h>
//#include <chrono>
//#include <utility>
//#include <stdio.h>


using namespace std;
using namespace NTL;

//#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
//#define timeNow() std::chrono::high_resolution_clock::now()
#define N 5
typedef std::chrono::high_resolution_clock::time_point TimeVar;

#include <iostream>
using std::cerr;
using std::endl;
#include <fstream>
using std::ofstream;
#include <cstdlib>

double	su_operation_time(int choice_op, zz_pX P, zz_pX G, int d, int n);
void	su_write_in_file(int degree, double ti_add, double ti_mult, double ti_div, double ti_gcd, double ti_xgcd);
void	su_choice_params(long *d, long *b, long *p, int *choice_p, int *choice_op, int ac, char **av);


#endif

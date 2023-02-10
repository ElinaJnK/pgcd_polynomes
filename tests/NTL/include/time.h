#ifndef TIME_H
# define TIME_H

#include <NTL/ZZ.h>
#include <NTL/ZZX.h>
#include <NTL/lzz_p.h>
#include <NTL/lzz_pX.h>
#include <NTL/lzz_pE.h>
#include <NTL/lzz_pEX.h>
#include <NTL/ZZXFactoring.h>
#include <NTL/lzz_pXFactoring.h>
//#include <chrono>
#include <utility>
#include <stdio.h>

using namespace std;
using namespace NTL;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
#define N 5

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#endif
/***
 * To compile run 
 * g++ -g -O2 -std=c++11 -pthread  big_int.cpp -o big_int -lntl -lgmp -lm
 * If you are missing the gmp library: https://libntl.org/doc/tour-unix.html
 * when you do make install (from here https://libntl.org/doc/tour-gmp.html) 
 * do not forget to add 'sudo' before make.
 * ***/
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

int main()
{
   ZZ a, b, c; 

   cin >> a; 
   cin >> b; 
   c = (a+1)*(b+1);
   cout << c << "\n";
}
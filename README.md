# PGCD of polynomes by approximation/interpolation
## _Supervised by Professor NEIGER Vincent_

The objective of this project is to develop and implement an efficient algorithm for computing the greatest common divisor (GCD) of two polynomials on the finite field Fp = Z/pZ. The implementation will be compared to the GCD implementations in the FLINT and NTL software libraries, which provide efficient computation on a finite field Fp = Z/pZ for univariate polynomials, particularly when p has a good root of unity that enables fast Fourier transform (FFT). Given that the GCD is used in various operations, optimizing its computation is crucial for improving efficiency. By analyzing the strengths and weaknesses of the variant algorithm, we aim to optimize specific parts of the existing implementation.

## Files and implemented functions
- FLINT or NTL/bench/time_utils.cpp : a first look into the time taken by the algorithms implemented by NTL/FLINT
- commandes.txt : a list of commands for gnuplot (see 'To run gnuplot')
- .sagews : containing the new implemented algorithm for half-gcd in sage
- *.h : header files

## Run the program

To run the program simply do:
```sh
make
./ntl 
```
Instructions will guide you towards what you wish to test.

You can also run:

```sh
make re # delete and make the project again
make clean # delete all the compiled files
make fclean # delete everything
```

## To run gnuplot for algorithm analysis

Install gnuplot;

```sh
brew install gnuplot
```
```sh
gnuplot -p < commandes.txt
```

## Try to make graphs

- For NTL
```sh
cd tests/NTL
make
# do tests for FFTInit
./ntl
# do tests for GenPrime_long
./ntl 1 0 1000 60
```
I will generate the graphs from these results.

- Pour FLINT

```sh
cd tests/FLINT
make
./flint
```


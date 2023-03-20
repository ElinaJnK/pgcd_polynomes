# PGCD of polynomes by approximation/interpolation

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

## Comment faire les graphes ?

- Pour NTL
```sh
cd tests/NTL
make
# faire les tests pour FFTInit (va generer automatiquement pour FFTInit)
./ntl
# faire les tests pour GenPrime_long
./ntl 1 0 1000 60
# devrait generer la phrase "Polynome generated with GenPrime\n" -> argv[1] indique que l'on utilise GenPrime_long
```
I will generate the graphs from these results.

- Pour FLINT

DOES NOT WORK YET
```sh
cd tests/FLINT
make
./flint
```


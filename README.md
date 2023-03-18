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



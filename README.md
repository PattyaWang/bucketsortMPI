This code is for generating random numbers in an array ranging from 0 - 999,999.
INPUT 1 [n] number of processors, node to be divided from the one single process.
INPUT 2 [i] size your dataset (Eg. 1000000, 2000000)

so the array would be [1092,999999,0,12345,..., n]
you can change this in the code with by reading the markdown.

###### library used.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

##################################################################
NOTE: the server use linuxOS and we will be compile here in linux OS
##################################################################
transfer your file SSH into the server with WinSCP for example

#######################   Steps   ##############################
(1) type in the terminal: ls (list files)
ls <- type this in the terminal

(2) if the file is over there then we will compile the file
compile if there is any error, try different way to compile the MPI file.

(3) try to compile
// if you cannot compile with gcc then try to compile like this for example
mpicc -std=gnu99 -o [name that you want to compile (Eg.A)] [filename.c (Eg. filename = A.c)]
## example mpicc -std=gnu99 -o bucketsort bucketsort.c
## example. gcc -nopenmp -o bucketsortMPI bucketsortMPI.c
## exampl mpicc -std=gnu99 -o bucketsortMPI bucketsortMPI.c

(4) run
mpirun -np [amount of processes] ./[name that you compiled (Eg.A)]
### example. mpirun -np 0 ./bucketsort
mpirun -np 16 ./bucketsort
[input number of integer generated in an array] 100000
result print: run time by 0.001 seconds

end of the text.

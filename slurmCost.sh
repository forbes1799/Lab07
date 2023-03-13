#!/bin/bash -l

#SBATCH -D ./
#SBATCH -t 5
#SBATCH -p course
#SBATCH --export=ALL

module load mpi/intel-mpi/2019u5/bin

module load compilers/intel/2019u5

mpiicc costOfComms.c

mpirun -np 2 ./a.out

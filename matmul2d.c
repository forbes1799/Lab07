#include <mpi.h>
#include <stdio.h>

#define MAXSIZE 8			/* change the size of matrices as required*/

int X[MAXSIZE][MAXSIZE], Y[MAXSIZE][MAXSIZE], Z[MAXSIZE][MAXSIZE];

void fill_matrix(int mat[MAXSIZE][MAXSIZE])
{
    /* write code to fill mat with values*/
}

void print_matrix(int mat[MAXSIZE][MAXSIZE])
{
    /* write the code that will print the 2D mat*/
}


int main(int argc, char *argv[])
{
  int my_rank, comm_size, from, to;
  int part_size = MAXSIZE*MAXSIZE/comm_size;
  int i, j, k;
  int root = 0;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

  /* write code that checkes if MAXSIZE is divisible by comm_size, else exit(-1)*/


  from = my_rank * MAXSIZE/comm_size;
  to = (my_rank+comm_size) * MAXSIZE/comm_size;

  /* Root process will fills the input matrices X and Y*/
  MPI_Bcast (Y, MAXSIZE*MAXSIZE, MPI_INT, root, MPI_COMM_WORLD);
  
  
  MPI_Scatter (X, part_size, MPI_INT, X[from], part_size, MPI_INT, root, MPI_COMM_WORLD);
  for (i=from; i<to; i++) 
    for (j=0; j<MAXSIZE; j++) {
      Z[i][j]=0;
      for (k=0; k<MAXSIZE; k++)
        Z[i][j] += X[i][k]*Y[k][j];
    }
  MPI_Gather (Z[from], part_size, MPI_INT, Z, part_size, MPI_INT, root, MPI_COMM_WORLD);

  /*if root print mat Z*/

  MPI_Finalize();
  return 0;
}
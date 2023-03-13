#include <mpi.h>
#include <stdio.h>

#define MAXSIZE 8			/* change the size of matrices as required*/

int X[MAXSIZE][MAXSIZE], Y[MAXSIZE][MAXSIZE], Z[MAXSIZE][MAXSIZE];

void fill_matrix(int mat[MAXSIZE][MAXSIZE])
{
	/*fill matrices here with rand() % 10*/
}

void print_matrix(int mat[MAXSIZE][MAXSIZE])
{
	/*print out the matrix here*/
}


int main(int argc, char *argv[])
{
  int my_rank, comm_size, from, to;
  int part_size = MAXSIZE*MAXSIZE/comm_size;
  int localX[part_size][MAXSIZE], localY[part_size][MAXSIZE], localZ[part_size][MAXSIZE];
  int i, j, k;
  int root = 0;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	if(MAXSIZE % comm_size != 0){
		exit(-1);
	}

  from = my_rank * MAXSIZE/comm_size;
  to = (my_rank+comm_size) * MAXSIZE/comm_size;

  /*if root rank, fill the matrices X and Y*/
  
  MPI_Bcast (Y, MAXSIZE*MAXSIZE, MPI_INT, root, MPI_COMM_WORLD);
  
  /*What's the difference here between MPI_Bcast and MPI_Scatter*/
  
  MPI_Scatter (X, part_size, MPI_INT, localX, part_size, MPI_INT, root, MPI_COMM_WORLD);

  for (i=from; i<to; i++) 
    for (j=0; j<MAXSIZE; j++) {
      localZ[i][j]=0;
      for (k=0; k<MAXSIZE; k++)
        localZ[i][j] += localX[i][k]*Y[k][j];  /*Why are we using localX and Y?*/
    }
  /*Here, use MPI gather to pull localZ from all the other ranks and store it in Z./*

  /*if root print mat Z*/


  MPI_Finalize();
  return 0;
}

#include<mpi.h>
#include<stdio.h>
#include<time.h>

#define NUMELEMENTS 1000000000

void finalise();
void sendOneMessagePerFloat(float*, int);
void sendOneLargerMessage(float*, int);


int main(void){

	float *sendBuf;
	int myRank, commSize;
	int i;
	
	sendBuf = (float*) malloc(NUMELEMENTS * sizeof(float));

	MPI_Init(NULL, NULL);

	srand(time(NULL) + myRank); //seed generated with time + myRank to generate a thread-safe random number

	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);

	if(commSize != 2){
		printf("2 Processes only for this program");
		finalise();
		return 0;
	}
	
	
	if(myRank == 0){
		double start, end;
		printf("Rank %d: generating randomNumbers\n", myRank);
		for(i = 0; i < NUMELEMENTS; i++){
			sendBuf[i] = rand() % 100;
		}

		
	}

	sendOneMessagePerFloat(sendBuf, myRank);
	sendOneLargerMessage(sendBuf, myRank);

	finalise();
}

void sendOneMessagePerFloat(float* sendBuf, int myRank){
	double start, end;
	int i;

	start = MPI_Wtime();

	/*Here, send NUMELEMENT messages one float at a time*/

	end = MPI_Wtime();

	printf("Rank %d: Time taken to send one message per float %f\n", myRank, 1000*(end - start));
}

void sendOneLargerMessage(float* sendBuf, int myRank){
	double start, end;

	start = MPI_Wtime();

	/*Here, send the 1 message of NUMELEMENT floats*/
	
	end = MPI_Wtime();

	printf("Rank: %d: Time taken to send one larger message of many floats %f\n", myRank, 1000*(end - start));
}

void finalise(){
	MPI_Finalize();
}

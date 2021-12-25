#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DIMENTION 5


int main(int argc, char** argv) 
{ 
	int a[DIMENTION];
	int b[DIMENTION];

	int size_of_dataset = DIMENTION;

    	srand(time(NULL));

	for (int i = 0; i < size_of_dataset; i++)
	{	
        	a[i] = rand() % 101 - 50; // in range (-50, 50)
		b[i] = rand() % 101 - 50;
	}

    	int process_Rank, size_Of_Cluster;

    	MPI_Init(&argc, &argv);
    	MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Cluster);
    	MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);
    	
	int range, res = 0; 

    	for (int i = range * process_Rank; i <= range * (process_Rank + 1); i++)
    	{
    		res = a[i] * b[i];
	}
 


	int ress;
    	MPI_Reduce(&res, &ress, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    	if (process_Rank == 0)
        	printf("scalar product is: %d", ress);
    	MPI_Finalize();



   	 return 0;


}

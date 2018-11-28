#include <iostream>
#include <mpi.h>

int  main()
{
int ierr, procid, numprocs ; 

ierr = MPI_Init(NULL, NULL);

// Get the number of processes

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

double val = 1.0 * procid ;
MPI_Send(&val, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
printf("ProcID %d sent value %lf to ProcID 0. \n", procid, val ) ;


if (procid  == 0)
{
int i ; 
double val, sum = 0 ;
MPI_Status status ;
for ( i = 0 ; i != numprocs; i++ )
{
	ierr = MPI_Recv(&val, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	if (ierr ==MPI_SUCCESS)
	{
		printf("ProcID %d  successfully received a value %lf!\n", procid, val);
		sum += val;
	}
	else
		MPI_Abort(MPI_COMM_WORLD, 1);
}

printf("The total is %lf .\n", sum);
}

MPI_Finalize();

return 0;
}


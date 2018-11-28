#include <iostream>
#include <mpi.h>

int  main()
{
int ierr, procid, numprocs ; 

MPI_Init(NULL, NULL);

// Get the number of processes

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

if (numprocs != 2)
{
printf("ERROR: Number of Processors is not 2!\n");
return MPI_Abort(MPI_COMM_WORLD,1);
}
if (procid == 0)
{
//procid 0 will send the number 3.14 to procid 1 ...
double pi = 3.14 ;
MPI_Send(&pi, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
printf("ProcID %d sent value %lf to ProcID 1. \n", procid, pi) ;
}
else{
//procid 1 will wait to receive a double from procid 0 ...
double value ;
MPI_Status status ;
ierr = MPI_Recv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
if(ierr ==MPI_SUCCESS)
printf("ProcID %d didnot successfully receive a value !\n", procid);
}

MPI_Finalize();

return 0;
}


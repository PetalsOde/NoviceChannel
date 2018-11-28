#include <iostream>
#include <mpi.h>

int  main()
{
int ierr, procid, numprocs ; 

ierr = MPI_Init(NULL, NULL);

// Get the number of processes

ierr = MPI_Comm_rank(MPI_COMM_WORLD, &procid);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

if (numprocs % 2 != 0)
{
printf("ERROR: Number of Processors is even!\n");
return MPI_Abort(MPI_COMM_WORLD,1);
}
if (procid %2 == 0)
{
//even procid i will send the number pi + i to procid i + 1 ...
double val = 3.14 + procid  ;
MPI_Send(&val, 1, MPI_DOUBLE, procid+1, 0, MPI_COMM_WORLD);
printf("ProcID %d sent value %lf to ProcID %d. \n", procid, val, procid+1 ) ;
}
else{
//procid 1 will wait to receive a double from procid 0 ...
double val ;
MPI_Status status ;
ierr = MPI_Recv(&val, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
if(ierr == MPI_SUCCESS)
printf("ProcID %d  successfully received a value %lf!\n", procid, val);
else
printf("ProcID %d didnot successfully receive a value !\n", procid);
}

MPI_Finalize();

return 0;
}


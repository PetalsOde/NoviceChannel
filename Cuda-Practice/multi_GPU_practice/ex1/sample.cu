#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cuda.h>

#define NB 32
#define NT 500
#define N NB*NT

__global__ void add( double *a, double *b, double *c);

//===========================================
__global__ void add( double *a, double *b, double *c){

    int tid = threadIdx.x + blockIdx.x * blockDim.x; 

    while(tid < N){
        c[tid] = a[tid] + b[tid];
        tid += blockDim.x * gridDim.x;
    }

}

//============================================
//BEGIN
//===========================================
int main( void ) {

    double *a, *b, *c;
    double *dev_a, *dev_b, *dev_c;

    // allocate the memory on the CPU
    a=(double *)malloc(N*sizeof(double));
    b=(double *)malloc(N*sizeof(double));
    c=(double *)malloc(N*sizeof(double));

    // allocate the memory on the GPU
    cudaMalloc( (void**)&dev_a, N * sizeof(double) );
    cudaMalloc( (void**)&dev_b, N * sizeof(double) );
    cudaMalloc( (void**)&dev_c, N * sizeof(double) );

    // fill the arrays 'a' and 'b' on the CPU
    for (int i=0; i<N; i++) {
        a[i] = (double)i;
        b[i] = (double)i*2;
    }

    // copy the arrays 'a' and 'b' to the GPU
    cudaMemcpy( dev_a, a, N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy( dev_b, b, N * sizeof(double), cudaMemcpyHostToDevice);

    for(int i=0;i<10000;++i)
        add<<<NB,NT>>>( dev_a, dev_b, dev_c );

    // copy the array 'c' back from the GPU to the CPU
    cudaMemcpy( c, dev_c, N * sizeof(double), cudaMemcpyDeviceToHost);

    // display the results
    // for (int i=0; i<N; i++) {
    //      printf( "%g + %g = %g\n", a[i], b[i], c[i] );
    //  }
    printf("\nGPU done\n");

    // free the memory allocated on the GPU
    cudaFree( dev_a );
    cudaFree( dev_b );
    cudaFree( dev_c );
    // free the memory allocated on the CPU
    free( a );
    free( b );
    free( c );

    return 0;
}

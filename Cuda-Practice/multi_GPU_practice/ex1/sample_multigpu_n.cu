#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cuda.h>

#define NB 32
#define NT 500
#define N NB*NT



__global__ void add( double *a, double *b, double *c, const int Ns );

//===========================================
__global__ void add( double *a, double *b, double *c, const int Ns){

    int tid = threadIdx.x + blockIdx.x * blockDim.x; 

    while(tid < Ns){
        c[tid] = a[tid] + b[tid];
        tid += blockDim.x * gridDim.x;
    }

}

//============================================
//BEGIN
//===========================================
int main( void ) {

    double *a, *b, *c;

    // allocate the memory on the CPU
    a=(double *)malloc(N*sizeof(double));
    b=(double *)malloc(N*sizeof(double));
    c=(double *)malloc(N*sizeof(double));
	
    int gpu_n;
    cudaGetDeviceCount(&gpu_n);
    printf("CUDA-capable device count: %i\n", gpu_n);

	int m_size = gpu_n   ;
	double *dev_a[m_size], *dev_b[m_size], *dev_c[m_size];
	int Ns[m_size] ;

	for (int i = 0 ; i < m_size ; i++ )
	{ 
		if(i<(N%gpu_n))
		{
			Ns[i] = N/gpu_n + 1 ;
		}
		else 
		{
			Ns[i] = N/gpu_n ;
		}
		
	}
	std::cout<<"Ns is created"<<'\n' ;

	// allocate the memory on the GPUs
	for(int dev=0; dev<m_size; dev++) 
	{
		cudaSetDevice(dev);
		cudaMalloc( (void**)&dev_a[dev], Ns[dev] * sizeof(double) );
		cudaMalloc( (void**)&dev_b[dev], Ns[dev] * sizeof(double) );
		cudaMalloc( (void**)&dev_c[dev], Ns[dev] * sizeof(double) );
	}

    // fill the arrays 'a' and 'b' on the CPU
    for (int i=0; i<N; i++) {
        a[i] = (double)i;
        b[i] = (double)i*2;
    }
	std::cout<<"data created"<<'\n' ;	

 
	// copy the arrays 'a' and 'b' to the GPUs
	for(int dev=0,pos=0; dev<m_size; pos+=Ns[dev], dev++) 
	{
		cudaSetDevice(dev);
		cudaMemcpy( dev_a[dev], a+pos, Ns[dev] * sizeof(double), cudaMemcpyHostToDevice);
		cudaMemcpy( dev_b[dev], b+pos, Ns[dev] * sizeof(double), cudaMemcpyHostToDevice);
		std::cout<<Ns[dev] <<'\n' ;
	}
	std::cout<<"cudamemcpy done"<<'\n' ;	


	for(int i=0;i<10000;++i) 
	{
		for(int dev=0; dev<m_size; dev++) 
		{
			cudaSetDevice(dev);
			add<<<NB,NT>>>( dev_a[dev], dev_b[dev], dev_c[dev], Ns[dev] );
			cudaDeviceSynchronize();
		//	std::cout<<"next Kernel started for dev "<< dev<< '\n' ;
		}
	}
	std::cout<<"kernel done"<<'\n' ;	
	
	// copy the arrays 'c' from the GPUs
	for(int dev=0,pos=0; dev<m_size; pos+=Ns[dev], dev++) 
	{
		cudaSetDevice(dev);
		cudaMemcpy( c+pos,dev_c[dev], Ns[dev] * sizeof(double), cudaMemcpyDeviceToHost);
		std::cout<<"cudaMemcpyDeviceToHost     "<<dev<<'\n' ;
	}
	std::cout<<"cudaMemcpyDeviceToHost done"<<'\n' ;

    // display the results
     for (int i=0; i<N; i++) {
         printf( "%g + %g = %g\n", a[i], b[i], c[i] );
      }
    printf("\nGPU done\n");

    // free the memory allocated on the GPUS
	for(int dev=0; dev<m_size; dev++) 
	{
		cudaFree( dev_a[dev] );
		cudaFree( dev_b[dev] );
		cudaFree( dev_c[dev] );
	}
//	for (int i = 0 ; i < N ; i++ )
//	{
//		std::cout<<c[i]<<"    "<< i <<'\n' ;
//	}

	std::cout<<"cudafree done"<<'\n' ;

    // free the memory allocated on the CPU
    free( a );
    free( b );
    free( c );

    return 0;
}

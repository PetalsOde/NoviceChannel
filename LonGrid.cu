#include<iostream>
#include<stdio.h>
#include<cuda.h>

#include "LonGrid.h"
using namespace std;

__global__ void lonkernel(float* d_new_lon, int nlons, float del_lon)
{
	unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
	if (x < nlons)
	{
		float a_lon = 0.0;
		d_new_lon[x] = a_lon + (x) * del_lon ;
	}
}



float NewLonGrid::new_lon_grid(float *h_new_lon, int &NLON, float del_lon)
{
//	const int NLON = 144;
	float *d_new_lon;
//	float del_lon = 1.25;
	NLON = ( 360 + 0 )/del_lon;
	size_t nxx_size = NLON * sizeof( float ); 
    h_new_lon = (float *)malloc( nxx_size );

	cudaMalloc( (void **)&d_new_lon, nxx_size ); 

	int blocknum;
	int blocksize;

	blocksize=8;
	blocknum=(int)ceil((float)NLON/8);
	
	// execute device kernel

	lonkernel<<<blocknum,blocksize>>>(d_new_lon, NLON, del_lon);
	
	cudaMemcpy(h_new_lon,d_new_lon,nxx_size,cudaMemcpyDeviceToHost);

	cudaFree(d_new_lon);
	
	for (int i =0 ; i< NLON; i++)
	{
		cout << "*****lonpos["<<i<<"] = "<< h_new_lon[i]<<endl;
	}
	cout<<"NLON ="<<NLON<<endl;
	cudaDeviceSynchronize();
	return 0;
	
}
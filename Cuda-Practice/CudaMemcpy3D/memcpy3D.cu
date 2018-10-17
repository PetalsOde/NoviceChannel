#include <iostream>
#include<stdio.h>
#include<cuda.h>
#include<cuda_runtime.h>
#include<device_launch_parameters.h>
using namespace std;

#define BLOCKSIZE_x 16
#define BLOCKSIZE_y 16

#define N 128
#define M 64
#define W 16

/*****************/
/* CUDA MEMCHECK */
/*****************/
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort=true)
{
    if (code != cudaSuccess) 
    {
        fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if ( abort )
                        exit( code );
    }
}

/*******************/
/* iDivUp FUNCTION */
/*******************/
int iDivUp(int a, int b){ return ((a % b) != 0) ? (a / b + 1) : (a / b); }

/******************/
/* TEST KERNEL 3D */
/******************/
__global__ void test_kernel_3D(cudaPitchedPtr devPitchedPtr)
{
    int tidx =  blockIdx.x*blockDim.x+threadIdx.x;
    int tidy =  blockIdx.y*blockDim.y+threadIdx.y;

    char* devPtr = (char*) devPitchedPtr.ptr;
    size_t pitch = devPitchedPtr.pitch;
    size_t slicePitch = pitch * N;

    for (int w = 0; w < W; w++) {
        char* slice = devPtr + w * slicePitch;
        float* row = (float*)(slice + tidy * pitch);
        row[tidx] = row[tidx] * row[tidx];
    }
}

/********/
/* MAIN */
/********/
int main()
{
    float a[N][M][W];

    for (int i=0; i<N; i++)
        for (int j=0; j<M; j++) 
            for (int w=0; w<W; w++) {
                a[i][j][w] = 3.f;
                //printf("row %i column %i depth %i value %f \n",i,j,w,a[i][j][w]);
            }

    // --- 3D pitched allocation and host->device memcopy
    cudaExtent extent = make_cudaExtent(M * sizeof(float), N, W);

    cudaPitchedPtr devPitchedPtr;
    gpuErrchk(cudaMalloc3D(&devPitchedPtr, extent));

    cudaMemcpy3DParms p = { 0 };
    p.srcPtr.ptr = a;
    p.srcPtr.pitch = M * sizeof(float);
    p.srcPtr.xsize = M;
    p.srcPtr.ysize = N;
    p.dstPtr.ptr = devPitchedPtr.ptr;
    p.dstPtr.pitch = devPitchedPtr.pitch;
    p.dstPtr.xsize = M;
    p.dstPtr.ysize = N;
    p.extent.width = M * sizeof(float);
    p.extent.height = N;
    p.extent.depth = W;
    p.kind = cudaMemcpyHostToDevice;
    gpuErrchk(cudaMemcpy3D(&p));

    dim3 GridSize(iDivUp(M,BLOCKSIZE_x),iDivUp(N,BLOCKSIZE_y));
    dim3 BlockSize(BLOCKSIZE_y,BLOCKSIZE_x);
    test_kernel_3D<<<GridSize,BlockSize>>>(devPitchedPtr);
    gpuErrchk(cudaPeekAtLastError());
    gpuErrchk(cudaDeviceSynchronize());

    p.srcPtr.ptr = devPitchedPtr.ptr;
    p.srcPtr.pitch = devPitchedPtr.pitch;
    p.dstPtr.ptr = a;
    p.dstPtr.pitch = M * sizeof(float); 
    p.kind = cudaMemcpyDeviceToHost;
    gpuErrchk(cudaMemcpy3D(&p));

    for (int i=0; i<N; i++) 
        for (int j=0; j<M; j++) 
            for (int w=0; w<W; w++)
                printf("row %i column %i depth %i value %f\n",i,j,w,a[i][j][w]);

    int ch = std::cin.get();
    return 0;
}

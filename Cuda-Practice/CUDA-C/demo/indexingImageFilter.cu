#include <stdio.h>
#include <stdlib.h>
// these are just for timing measurments
#include <time.h>
//3D cuda kernel for indexing image filtering
// Computes minimum in a 3D volume, at each output point
// To compile it with nvcc execute: nvcc -O2 -o grid3d grid3d.cu
//define the window size (cubic volume) and the data set size
//
#define WSIZE 6
#define DATAXSIZE 100
#define DATAYSIZE 100
#define DATAZSIZE 20
//define the chunk sizes that each threadblock will work on
#define BLKXSIZE 8
#define BLKYSIZE 8
#define BLKZSIZE 8

// for cuda error checking
#define cudaCheckErrors(msg) \
    do { \
        cudaError_t __err = cudaGetLastError(); \
        if (__err != cudaSuccess) { \
            fprintf(stderr, "Fatal error: %s (%s at %s:%d)\n", \
                msg, cudaGetErrorString(__err), \
                __FILE__, __LINE__); \
            fprintf(stderr, "*** FAILED - ABORTING\n"); \
            return 1; \
        } \
    } while (0)
// device function to compute 3D volume minimum at each output point
__global__ void cmp_win(int knode[][DATAYSIZE][DATAXSIZE], const int kcell[][DATAYSIZE+(WSIZE-1)][DATAXSIZE+(WSIZE-1)])
{
    __shared__ int smem[(BLKZSIZE + (WSIZE-1))][(BLKYSIZE + (WSIZE-1))][(BLKXSIZE + (WSIZE-1))];
    int tempnode, i, j, k;
    int idx = blockIdx.x*blockDim.x + threadIdx.x;
    int idy = blockIdx.y*blockDim.y + threadIdx.y;
    int idz = blockIdx.z*blockDim.z + threadIdx.z;
    if ((idx < (DATAXSIZE+WSIZE-1)) && (idy < (DATAYSIZE+WSIZE-1)) && (idz < (DATAZSIZE+WSIZE-1))){
      smem[threadIdx.z][threadIdx.y][threadIdx.x]=kcell[idz][idy][idx];
      if ((threadIdx.z > (BLKZSIZE - WSIZE)) && (idz < DATAZSIZE))
        smem[threadIdx.z + (WSIZE-1)][threadIdx.y][threadIdx.x] = kcell[idz + (WSIZE-1)][idy][idx];
      if ((threadIdx.y > (BLKYSIZE - WSIZE)) && (idy < DATAYSIZE))
        smem[threadIdx.z][threadIdx.y + (WSIZE-1)][threadIdx.x] = kcell[idz][idy+(WSIZE-1)][idx];
      if ((threadIdx.x > (BLKXSIZE - WSIZE)) && (idx < DATAXSIZE))
        smem[threadIdx.z][threadIdx.y][threadIdx.x + (WSIZE-1)] = kcell[idz][idy][idx+(WSIZE-1)];
      if ((threadIdx.z > (BLKZSIZE - WSIZE)) && (threadIdx.y > (BLKYSIZE - WSIZE)) && (idz < DATAZSIZE) && (idy < DATAYSIZE))
        smem[threadIdx.z + (WSIZE-1)][threadIdx.y + (WSIZE-1)][threadIdx.x] = kcell[idz+(WSIZE-1)][idy+(WSIZE-1)][idx];
      if ((threadIdx.z > (BLKZSIZE - WSIZE)) && (threadIdx.x > (BLKXSIZE - WSIZE)) && (idz < DATAZSIZE) && (idx < DATAXSIZE))
        smem[threadIdx.z + (WSIZE-1)][threadIdx.y][threadIdx.x + (WSIZE-1)] = kcell[idz+(WSIZE-1)][idy][idx+(WSIZE-1)];
      if ((threadIdx.y > (BLKYSIZE - WSIZE)) && (threadIdx.x > (BLKXSIZE - WSIZE)) && (idy < DATAYSIZE) && (idx < DATAXSIZE))
        smem[threadIdx.z][threadIdx.y + (WSIZE-1)][threadIdx.x + (WSIZE-1)] = kcell[idz][idy+(WSIZE-1)][idx+(WSIZE-1)];
      if ((threadIdx.z > (BLKZSIZE - WSIZE)) && (threadIdx.y > (BLKYSIZE - WSIZE)) && (threadIdx.x > (BLKXSIZE - WSIZE)) && (idz < DATAZSIZE) && (idy < DATAYSIZE) && (idx < DATAXSIZE))
        smem[threadIdx.z+(WSIZE-1)][threadIdx.y+(WSIZE-1)][threadIdx.x+(WSIZE-1)] = kcell[idz+(WSIZE-1)][idy+(WSIZE-1)][idx+(WSIZE-1)];
      }
    __syncthreads();
    if ((idx < DATAXSIZE) && (idy < DATAYSIZE) && (idz < DATAZSIZE)){
      tempnode = knode[idz][idy][idx];
      for (i=0; i<WSIZE; i++)
        for (j=0; j<WSIZE; j++)
          for (k=0; k<WSIZE; k++)
          if (smem[threadIdx.z + i][threadIdx.y + j][threadIdx.x + k] < tempnode)
            tempnode = smem[threadIdx.z + i][threadIdx.y + j][threadIdx.x + k];
      knode[idz][idy][idx] = tempnode;
      }
}

int main(int argc, char *argv[])
{
    typedef int cRarray[DATAYSIZE+WSIZE-1][DATAXSIZE+WSIZE-1];
    typedef int nRarray[DATAYSIZE][DATAXSIZE];
    int i, j, k, u, v, w, temphnode;
    const dim3 blockSize(BLKXSIZE, BLKYSIZE, BLKZSIZE);
    const dim3 gridSize(((DATAXSIZE+BLKXSIZE-1)/BLKXSIZE), ((DATAYSIZE+BLKYSIZE-1)/BLKYSIZE), ((DATAZSIZE+BLKZSIZE-1)/BLKZSIZE));
// these are just for timing
    clock_t t0, t1, t2, t3;
    double t1sum=0.0f;
    double t2sum=0.0f;
    double t3sum=0.0f;
// overall data set sizes
    const int nx = DATAXSIZE;
    const int ny = DATAYSIZE;
    const int nz = DATAZSIZE;
// window (cubic minimization volume) dimensions
    const int wx = WSIZE;
    const int wy = WSIZE;
    const int wz = WSIZE;
// pointers for data set storage via malloc
    nRarray *hnode; // storage for result computed on host
    nRarray *node, *d_node;  // storage for result computed on device
    cRarray *cell, *d_cell;  // storage for input
// start timing
    t0 = clock();
// allocate storage for data set
    if ((cell = (cRarray *)malloc(((nx+(wx-1))*(ny+(wy-1))*(nz+(wz-1)))*sizeof(int))) == 0) {fprintf(stderr,"malloc Fail \n"); return 1;}
    if ((node = (nRarray *)malloc((nx*ny*nz)*sizeof(int))) == 0) {fprintf(stderr,"malloc Fail \n"); return 1; }
    if ((hnode = (nRarray *)malloc((nx*ny*nz)*sizeof(int))) == 0) {fprintf(stderr, "malloc Fail \n"); return 1; }
// synthesize data
    for(i=0; i<(nz+(wz-1)); i++)
      for(j=0; j<(ny+(wy-1)); j++)
        for (k=0; k<(nx+(wx-1)); k++){
          cell[i][j][k] = rand(); // unless we use a seed this will produce the same sequence all the time
          if ((i<nz) && (j<ny) && (k<nx)) {
            node[i][j][k]  = RAND_MAX;
            hnode[i][j][k] = RAND_MAX;
            }
          }
    t1 = clock();
    t1sum = ((double)(t1-t0))/CLOCKS_PER_SEC;
    printf("Init took %3.2f seconds.  Begin compute\n", t1sum);
// allocate GPU device buffers
    cudaMalloc((void **) &d_cell, (((nx+(wx-1))*(ny+(wy-1))*(nz+(wz-1)))*sizeof(int)));
    cudaCheckErrors("Failed to allocate device buffer");
    cudaMalloc((void **) &d_node, ((nx*ny*nz)*sizeof(int)));
    cudaCheckErrors("Failed to allocate device buffer2");
// copy data to GPU
    cudaMemcpy(d_node, node, ((nx*ny*nz)*sizeof(int)), cudaMemcpyHostToDevice);
    cudaCheckErrors("CUDA memcpy failure");
    cudaMemcpy(d_cell, cell, (((nx+(wx-1))*(ny+(wy-1))*(nz+(wz-1)))*sizeof(int)), cudaMemcpyHostToDevice);
    cudaCheckErrors("CUDA memcpy2 failure");

    cmp_win<<<gridSize,blockSize>>>(d_node, d_cell);
    cudaCheckErrors("Kernel launch failure");
// copy output data back to host

    cudaMemcpy(node, d_node, ((nx*ny*nz)*sizeof(int)), cudaMemcpyDeviceToHost);
    cudaCheckErrors("CUDA memcpy3 failure");
    t2 = clock();
    t2sum = ((double)(t2-t1))/CLOCKS_PER_SEC;
    printf(" Device compute took %3.2f seconds.  Beginning host compute.\n", t2sum);
// now compute the same result on the host
    for (u=0; u<nz; u++)
      for (v=0; v<ny; v++)
        for (w=0; w<nx; w++){
          temphnode = hnode[u][v][w];
          for (i=0; i<wz; i++)
            for (j=0; j<wy; j++)
              for (k=0; k<wx; k++)
                if (temphnode > cell[i+u][j+v][k+w]) temphnode = cell[i+u][j+v][k+w];
          hnode[u][v][w] = temphnode;
          }
    t3 = clock();
    t3sum = ((double)(t3-t2))/CLOCKS_PER_SEC;
    printf(" Host compute took %3.2f seconds.  Comparing results.\n", t3sum);
// and compare for accuracy
    for (i=0; i<nz; i++)
      for (j=0; j<ny; j++)
        for (k=0; k<nx; k++)
          if (hnode[i][j][k] != node[i][j][k]) {
            printf("Mismatch at x= %d, y= %d, z= %d  Host= %d, Device = %d\n", i, j, k, hnode[i][j][k], node[i][j][k]);
            return 1;
            }
    printf("Results match!\n");
    free(cell);
    free(node);
    cudaFree(d_cell);
    cudaCheckErrors("cudaFree fail");
    cudaFree(d_node);
    cudaCheckErrors("cudaFree fail");
    return 0;
}

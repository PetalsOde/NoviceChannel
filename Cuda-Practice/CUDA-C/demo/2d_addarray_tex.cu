#include<stdio.h>
#include<cuda.h>
#define BLOCK_SIZE 16

__global__ static void AddKernel(float *d_Buff1, float *d_Buff2, float *d_Buff3, size_t pitch, int iMatSizeM, int iMatSizeN)
{
	const int tidx = blockDim.x * blockIdx.x + threadIdx.x;
	const int tidy = blockDim.y * blockIdx.y + threadIdx.y;
	int index = pitch/sizeof(float);
	if(tidx<iMatSizeM && tidy<iMatSizeN)
	{
		d_Buff3[tidx * index  + tidy] = d_Buff1[tidx * index + tidy] + d_Buff2[tidx * index + tidy];
	}
}

void printMatrix(float *pflMat, int iMatSizeM, int iMatSizeN)
{
	  for(int idxM = 0; idxM < iMatSizeM; idxM++)
	{
		for(int idxN = 0; idxN < iMatSizeN; idxN++)
		{
			printf("%f\t",pflMat[(idxM * iMatSizeN) + idxN]);
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	  int iMatSizeM=0,iMatSizeN=0;
	  printf("Enter size of Matrix(M*N):");
	  scanf("%d %d",&iMatSizeM,&iMatSizeN);

	  float *h_flMat1 = (float*)malloc(iMatSizeM * iMatSizeN * sizeof(float));
	  float *h_flMat2 = (float*)malloc(iMatSizeM * iMatSizeN * sizeof(float));
	  float *h_flMatSum = (float*)malloc(iMatSizeM * iMatSizeN * sizeof(float));

  for(int j=0;j<(iMatSizeM*iMatSizeN);j++)
	  {
			h_flMat1[j]=(float)rand()/(float)RAND_MAX;
			h_flMat2[j]=(float)rand()/(float)RAND_MAX;
	  }

  printf("Matrix 1\n");
  printMatrix(h_flMat1, iMatSizeM, iMatSizeN);
  printf("Matrix 2\n");
  printMatrix(h_flMat2, iMatSizeM, iMatSizeN);

  float *d_flMat1, *d_flMat2, *d_flMatSum;;
  size_t d_MatPitch;

   cudaMallocPitch((void**)&d_flMat1,&d_MatPitch,iMatSizeN*sizeof(float),iMatSizeM);
   cudaMallocPitch((void**)&d_flMat2,&d_MatPitch,iMatSizeN*sizeof(float),iMatSizeM);
   cudaMallocPitch((void**)&d_flMatSum,&d_MatPitch,iMatSizeN*sizeof(float),iMatSizeM);
   cudaMemcpy2D(d_flMat1,d_MatPitch,h_flMat1,iMatSizeN * sizeof(float), iMatSizeN * sizeof(float), iMatSizeM, cudaMemcpyHostToDevice);
   cudaMemcpy2D(d_flMat2,d_MatPitch,h_flMat2,iMatSizeN * sizeof(float), iMatSizeN * sizeof(float), iMatSizeM, cudaMemcpyHostToDevice);
   dim3 blocks(1,1,1);
   dim3 threadsperblock(BLOCK_SIZE,BLOCK_SIZE,1);

   blocks.x=((iMatSizeM/BLOCK_SIZE) + (((iMatSizeM)%BLOCK_SIZE)==0?0:1));
   blocks.y=((iMatSizeN/BLOCK_SIZE) + (((iMatSizeN)%BLOCK_SIZE)==0?0:1));
 
   AddKernel<<<blocks, threadsperblock>>>(d_flMat1, d_flMat2, d_flMatSum, d_MatPitch, iMatSizeM,iMatSizeN);

   cudaThreadSynchronize();
   cudaMemcpy2D(h_flMatSum, iMatSizeN * sizeof(float),d_flMatSum, d_MatPitch, iMatSizeN * sizeof(float), iMatSizeM, cudaMemcpyDeviceToHost);
   cudaFree(d_flMat1);
   cudaFree(d_flMat2);
   cudaFree(d_flMatSum);
   printf("Matrix Sum\n");
   printMatrix(h_flMatSum, iMatSizeM, iMatSizeN);
}

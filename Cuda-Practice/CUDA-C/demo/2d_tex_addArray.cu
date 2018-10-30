#include<stdio.h>
#include<cutil_inline.h>
#define BLOCK_SIZE 16

texture<float,2>texVecA;
texture<float,2>texVecB;
__constant__ int ciMatSizeM;
__constant__ int ciMatSizeN;
__global__ static void AddKernel(float *d_Result)
{
	const int tidx = blockDim.x * blockIdx.x + threadIdx.x;
	const int tidy = blockDim.y * blockIdx.y + threadIdx.y;
	if(tidx<ciMatSizeM && tidy<ciMatSizeN)
	{
		float flValA = tex2D(texVecA,tidx,tidy);
		float flValB = tex2D(texVecB,tidx,tidy);
		d_Result[tidx * ciMatSizeN + tidy] = flValA + flValB;
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
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
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

	float *d_flMat1 = NULL, *d_flMat2 = NULL, *d_flMatSum = NULL;
	cudaMalloc(&d_flMat1, iMatSizeM * iMatSizeN * sizeof(float));
	cudaMalloc(&d_flMat2, iMatSizeM * iMatSizeN * sizeof(float));
	cudaMalloc(&d_flMatSum, iMatSizeM * iMatSizeN * sizeof(float));

	cudaMemcpy(d_flMat1, h_flMat1, iMatSizeM * iMatSizeN * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(d_flMat2, h_flMat2, iMatSizeM * iMatSizeN * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpyToSymbol(ciMatSizeM,&iMatSizeM,sizeof(float),0);
	cudaMemcpyToSymbol(ciMatSizeN,&iMatSizeN,sizeof(float),0);

	cudaBindTexture2D(0, texVecA, d_flMat1, channelDesc, iMatSizeN, iMatSizeM, iMatSizeM * sizeof(float));
	cudaBindTexture2D(0, texVecB, d_flMat2, channelDesc, iMatSizeN, iMatSizeM, iMatSizeM * sizeof(float));

	dim3 blocks(1,1,1);
	dim3 threadsperblock(BLOCK_SIZE,BLOCK_SIZE,1);
	blocks.x=((iMatSizeM/BLOCK_SIZE) + (((iMatSizeM)%BLOCK_SIZE)==0?0:1));
	blocks.y=((iMatSizeN/BLOCK_SIZE) + (((iMatSizeN)%BLOCK_SIZE)==0?0:1));

	AddKernel<<<blocks,threadsperblock>>>(d_flMatSum);

	cudaThreadSynchronize();
	cudaMemcpy(h_flMatSum,d_flMatSum,iMatSizeM * iMatSizeN * sizeof(float), cudaMemcpyDeviceToHost);
	cudaUnbindTexture(texVecA);
	cudaUnbindTexture(texVecB);

	cudaFree(d_flMat1);
	cudaFree(d_flMat2);
	cudaFree(d_flMatSum);

	printf("Matrix Sum\n");
	printMatrix(h_flMatSum, iMatSizeM, iMatSizeN);
}

/*********************************************************************/
/**
*
*    tex3d_interpl_non_normalized.cu
*
*
*    Created on : 3 December, 2018
*
*
*    Author  : Newbie-Coder-1105
*
**********************************************************************/
/*********************************************************************/

#include <iostream>
#include <fstream>
#define NX 50
#define NY 50
#define NZ 10
#define IX 100
#define IY 100
#define IZ 20
#define ifact 2

texture<float, 3> tex;

__global__ void getInterpolatedFunctionValue(float *a, float *b, float *c,  float *result) // int IX, int IY, int IZ )
{
// Calculate normalized texture coordinates
unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
unsigned int z = blockIdx.z * blockDim.z + threadIdx.z;

if ((x < IX) && (y < IY) && (z < IZ))
{

	float w = a[x] + 0.5f, v = b[y] + 0.5f, u = c[z] + 0.5f  ;
	result[z * IZ * IY + y * IZ + x ] = tex3D(tex, u, v, w );
//	printf("texObj = %f,  tu = %f, tv = %f, tw = %f\n",tex, u, v, w);
	printf("output = %f, width =%d, height = %d, depth = %d\n",result[z * IZ * IY + y * IZ + x ], x, y, z);
}
}

#define cudaCheckErrors(msg) \
    do { \
        cudaError_t __err = cudaGetLastError(); \
        if (__err != cudaSuccess) { \
            fprintf(stderr, "Fatal error: %s (%s at %s:%d)\n", \
                msg, cudaGetErrorString(__err), \
                __FILE__, __LINE__); \
            fprintf(stderr, "*** FAILED - ABORTING\n"); \
            exit(1); \
        } \
    } while (0)

using namespace std;

int main(){

int nx=NX, ny=NY, nz=NZ;
float fff[nz][ny][nx];
float x[nx], y[ny], z[nz] ;

for(int ix=0; ix<nx; ix++)
  for(int iy=0; iy<ny; iy++)
    for(int iz=0; iz<nz; iz++){
      fff[iz][iy][ix] = (ix + iy + iz ) * 100;
    }

for(int ix=0; ix<IX; ix++)
  for(int iy=0; iy<IY; iy++)
    for(int iz=0; iz<IZ; iz++){
		x[ix] =  ix / ifact ;
		y[iz] =  iy / ifact ;
		z[iz] =  iz / ifact ;
	}
	
//*************************************************************************//
float *d_x, *d_y, *d_z, *d_result, *h_result ;


cudaMalloc((void**)&d_x, IX * sizeof(float));
cudaMalloc((void**)&d_y, IY * sizeof(float));
cudaMalloc((void**)&d_z, IZ * sizeof(float));
cudaMalloc((void**)&d_result, IX * IY * IZ * sizeof(float));


cudaMemcpy( d_x, x, IX * sizeof(float), cudaMemcpyHostToDevice );
cudaMemcpy( d_y, y, IY * sizeof(float), cudaMemcpyHostToDevice );
cudaMemcpy( d_z, z, IZ * sizeof(float), cudaMemcpyHostToDevice );



cudaCheckErrors("allocating an array is failed");
//*************************************************************************//
	

cudaArray *d_volumeArray ;

//const cudaExtent extent = make_cudaExtent(nx, ny, nz);
cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
cudaMalloc3DArray(&d_volumeArray, &channelDesc, make_cudaExtent(nz, ny, nx));
cudaCheckErrors("cudaMalloc3D error");

cudaMemcpy3DParms copyParams = {0};
copyParams.srcPtr   = make_cudaPitchedPtr((void*)fff, sizeof(float)*nz,ny,nx);
copyParams.dstArray = d_volumeArray;
copyParams.dstPos   = make_cudaPos(0,0,0);
copyParams.srcPos   = make_cudaPos(0,0,0);
copyParams.extent   = make_cudaExtent(nz, ny, nx);
copyParams.kind     = cudaMemcpyHostToDevice;
cudaCheckErrors("copyParams3D fail");
cudaMemcpy3D(&copyParams);
cudaCheckErrors("cudaMemcpy3DParms fail");

tex.normalized = false;
tex.filterMode = cudaFilterModeLinear;
tex.addressMode[0] = cudaAddressModeClamp;
tex.addressMode[1] = cudaAddressModeClamp;
tex.addressMode[2] = cudaAddressModeClamp;

cudaBindTextureToArray(tex, d_volumeArray, channelDesc);
cudaCheckErrors("bind fail");	

const dim3 blockSize(8, 8, 8 );
const dim3 gridSize(((IZ + blockSize.x )/blockSize.x),((IY + blockSize.y )/blockSize.y),((IX + blockSize.z)/blockSize.z));

printf("Blocksize.x = %i, blockSize.y = %i, blockSize.z = %i \n", blockSize.x, blockSize.y, blockSize.z);
printf("gridSize.x = %i, gridSize.y = %i, gridSize.z = %i \n", gridSize.x, gridSize.y, gridSize.z);

getInterpolatedFunctionValue<<<gridSize, blockSize>>>(d_x, d_y, d_z, d_result) ; // IX , IY , IZ ) ;

cudaCheckErrors("kernel fail");
cudaDeviceSynchronize();	
h_result = (float*) malloc(IX * IY * IZ * sizeof(float)) ;
cudaMemcpy( h_result, d_result, IX * IY * IZ * sizeof(float),cudaMemcpyDeviceToHost);		
cudaCheckErrors("cudaMemcpy fail");
  
cudaUnbindTexture(tex);
cudaCheckErrors("unbind fail");

cudaCheckErrors("cudaFree fail");
cudaFreeArray(d_volumeArray);
cudaCheckErrors("free fail");

printf("success!\n");

for(int ix=0; ix<IX; ix++)
  for(int iy=0; iy<IY; iy++)
    for(int iz=0; iz<IZ; iz++){
		std::cout<<h_result[iz * IZ * IY + iy * IZ + ix ] << '\n' ;
	}



return 0;
}

#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <mpi.h>

int main(int argc, char** argv)
{
  cudaSetDevice(0);
  cudaError_t error = cudaGetLastError();

  if(error != cudaSuccess)
      std::cerr << " -> CUDA set device failed with " << cudaGetErrorString(error) << std::endl;

  int canPeer;
  cudaDeviceCanAccessPeer(&canPeer, 0, 1);
  std::cout << "GPU 0 1 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 2);
  std::cout << "GPU 0 2 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 3);
  std::cout << "GPU 0 3 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 4);
  std::cout << "GPU 0 4 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 5);
  std::cout << "GPU 0 5 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 6);
  std::cout << "GPU 0 6 Peer2Peer ? :" << canPeer << std::endl; 
  cudaDeviceCanAccessPeer(&canPeer, 0, 7);
  std::cout << "GPU 0 7 Peer2Peer ? :" << canPeer << std::endl; 


  int nelem = 400000;
  int ncopies = 40;
  int matrix_size = nelem*sizeof(double);
  double *a;
  cudaMallocHost( (void**)&a, matrix_size);
  for(int i=0; i < nelem; i ++)
    a[i] = i;

  error = cudaGetLastError();
  if(error != cudaSuccess)
      std::cerr << " -> CUDA malloc dum failed with " << cudaGetErrorString(error) << std::endl;

  double *dataGPU[8];

  for(int i=0; i < 8; ++i)
  {
    cudaSetDevice(i);

    cudaMalloc( (void**)&dataGPU[i], matrix_size );
    error = cudaGetLastError();

    if(error != cudaSuccess)
        std::cerr << " -> CUDA malloc a failed with " << cudaGetErrorString(error) << std::endl;
  }

  double start = MPI_Wtime();
  for (int i = 0; i < ncopies; ++i)
  {
    cudaMemcpy( a, dataGPU[0], matrix_size, cudaMemcpyDefault); 
    error = cudaGetLastError();
    if(error != cudaSuccess)
      std::cerr << " -> CUDA failed with " << cudaGetErrorString(error) << std::endl;
  }
  double end = MPI_Wtime();
  std::cout << "TOTAL time  " << end - start << std::endl;
  std::cout << "Bandwidth CPU->GPU0: " << matrix_size*ncopies/(1024.0*1024.0*1024.0)/ (end-start) << std::endl;
 
  std::cout << "SIMPLEX" << std::endl;
  for(int i=0; i < 8; ++i)
  {
    double start = MPI_Wtime();

    cudaPointerAttributes attr;
    cudaPointerGetAttributes(&attr, dataGPU[i]);
    std::cout << "Pointer a in device " << attr.device << std::endl;

    cudaSetDevice(0);
    error = cudaDeviceEnablePeerAccess(i, 0);
    if(error != cudaSuccess)
      std::cerr << " -> CUDA error enabling peer 2 peer " << cudaGetErrorString(error) << std::endl;

    for (int n = 0; n < ncopies; ++n)
    {
      cudaMemcpy( dataGPU[i], dataGPU[0], matrix_size, cudaMemcpyDefault); 
      error = cudaGetLastError();
      if(error != cudaSuccess)
        std::cerr << " -> CUDA failed with " << cudaGetErrorString(error) << std::endl;
    }
    cudaSetDevice(0);
    cudaDeviceSynchronize();
    cudaSetDevice(i);
    cudaDeviceSynchronize();

    double end = MPI_Wtime();
    std::cout << "TOTAL time  " << end - start << std::endl;
    std::cout << "Bandwidth GPU0->GPU"<< i << ": " << matrix_size*ncopies/(1024.0*1024.0*1024.0)/ (end-start) << std::endl;
  }

  std::cout <<"DUPLEX" << std::endl;
  for(int i=0; i < 8; ++i)
  {
    double start = MPI_Wtime();

    cudaPointerAttributes attr;
    cudaPointerGetAttributes(&attr, dataGPU[i]);
    std::cout << "Pointer a in device " << attr.device << std::endl;

    cudaSetDevice(0);
    error = cudaDeviceEnablePeerAccess(i, 0);
    if(error != cudaSuccess)
      std::cerr << " -> CUDA error enabling peer 2 peer " << cudaGetErrorString(error) << std::endl;

    for (int n = 0; n < ncopies; ++n)
    {
      cudaMemcpy( dataGPU[i], dataGPU[0], matrix_size, cudaMemcpyDefault); 
      cudaMemcpy( dataGPU[0], dataGPU[i], matrix_size, cudaMemcpyDefault); 
      error = cudaGetLastError();
      if(error != cudaSuccess)
        std::cerr << " -> CUDA failed with " << cudaGetErrorString(error) << std::endl;
    }
    cudaSetDevice(0);
    cudaDeviceSynchronize();
    cudaSetDevice(i);
    cudaDeviceSynchronize();

    double end = MPI_Wtime();
    std::cout << "TOTAL time  " << end - start << std::endl;
    std::cout << "Bandwidth GPU0->GPU"<< i << ": " << matrix_size*2*ncopies/(1024.0*1024.0*1024.0)/ (end-start) << std::endl;
  }
 
  return 0;
}

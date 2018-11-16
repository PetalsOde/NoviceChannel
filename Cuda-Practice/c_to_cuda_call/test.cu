#include <stdio.h>
#include "test.h"


__global__ void my_kernel(){
  printf("Hello!\n");
}

void my_cuda_func(){
  my_kernel<<<1,1>>>();
  cudaDeviceSynchronize();
}

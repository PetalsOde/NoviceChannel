#include <stdio.h>
#include "test.h"

int main(){
  my_kernel<<<1,1>>>();
  cudaDeviceSynchronize();
  return 0;
}

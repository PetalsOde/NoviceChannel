#include <stdio.h>
#include "test.h"


__global__ void my_kernel(){
  printf("Hello!\n");
}

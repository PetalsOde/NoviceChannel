#include "stdio.h"

__device__ int addarray(int* a, int* b, int i)
{
return a[i] + b[i] + a[i+1];
}

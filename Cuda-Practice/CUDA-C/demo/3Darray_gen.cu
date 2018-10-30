#include <cstdio>
inline void GPUassert(cudaError_t code, char * file, int line, bool Abort=true)
{
    if (code != 0) {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code),file,line);
        if (Abort) exit(code);
    }
}

#define GPUerrchk(ans) { GPUassert((ans), __FILE__, __LINE__); }



 __global__ void doSmth(int*** a) {
  for(int i=0; i<2; i++)
   for(int j=0; j<2; j++)
    for(int k=0; k<2; k++)
     a[i][j][k]=i+j+k;
 }
 
 
 
 int main() {
  int*** h_c = (int***) malloc(2*sizeof(int**));
  for(int i=0; i<2; i++) {
   h_c[i] = (int**) malloc(2*sizeof(int*));
   for(int j=0; j<2; j++)
    GPUerrchk(cudaMalloc((void**)&h_c[i][j],2*sizeof(int)));
  }
  int ***h_c1 = (int ***) malloc(2*sizeof(int **));
  for (int i=0; i<2; i++){
    GPUerrchk(cudaMalloc((void***)&(h_c1[i]), 2*sizeof(int*)));
    GPUerrchk(cudaMemcpy(h_c1[i], h_c[i], 2*sizeof(int*), cudaMemcpyHostToDevice));
    }
  int*** d_c;
  GPUerrchk(cudaMalloc((void****)&d_c,2*sizeof(int**)));
  GPUerrchk(cudaMemcpy(d_c,h_c1,2*sizeof(int**),cudaMemcpyHostToDevice));
  doSmth<<<1,1>>>(d_c);
  GPUerrchk(cudaPeekAtLastError());
  int res[2][2][2];
  for(int i=0; i<2; i++)
   for(int j=0; j<2; j++)
    GPUerrchk(cudaMemcpy(&res[i][j][0], h_c[i][j],2*sizeof(int),cudaMemcpyDeviceToHost));

  for(int i=0; i<2; i++)
   for(int j=0; j<2; j++)
    for(int k=0; k<2; k++)
     printf("[%d][%d][%d]=%d\n",i,j,k,res[i][j][k]);
 }

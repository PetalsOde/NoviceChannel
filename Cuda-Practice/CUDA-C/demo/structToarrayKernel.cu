#include <cstdlib>
#include <cstdio>

inline void GPUassert(cudaError_t code, char * file, int line, bool Abort=true)
{
    if (code != 0) {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code),file,line);
        if (Abort) exit(code);
    }       
}

#define GPUerrchk(ans) { GPUassert((ans), __FILE__, __LINE__); }

typedef float Real;

typedef struct Array2D {
    Real* arr;        
    int rows;       
    int cols;       
} Array2D;

__global__ void kernel(const int m, const int n, Real *lval, Array2D *output)
{
    lval[threadIdx.x] = 1.0f + threadIdx.x;
    if (threadIdx.x == 0) {
        output->arr = lval;
        output->rows = m;
        output->cols = n;
    }
}

int main(void)
{
    const int m=8, n=8, mn=m*n;

    Array2D *d_output;
    Real *d_arr;
    GPUerrchk( cudaMalloc((void **)&d_arr,sizeof(Real)*size_t(mn)) ); 

    GPUerrchk( cudaMalloc((void **)&d_output, sizeof(Array2D)) );
    kernel<<<1,mn>>>(m,n,d_arr,d_output);
    GPUerrchk( cudaPeekAtLastError() );

    // This section of code is the same as the original question
    Array2D *h_output = (Array2D*)malloc(sizeof(Array2D));
    GPUerrchk( cudaMemcpy(h_output, d_output, sizeof(Array2D), cudaMemcpyDeviceToHost) );
    size_t sz = size_t(h_output->rows*h_output->cols)*sizeof(Real);
    Real *h_arr = (Real*)malloc(sz);
    GPUerrchk( cudaMemcpy(h_arr, h_output->arr, sz, cudaMemcpyDeviceToHost) );

    for(int i=0; i<h_output->rows; i++)
        for(int j=0; j<h_output->cols; j++)
            fprintf(stdout,"(%d %d) %f\n", i, j, h_arr[j + i*h_output->rows]);

    return 0;
}

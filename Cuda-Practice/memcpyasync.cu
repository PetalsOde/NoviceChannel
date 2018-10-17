#include <cstdio>
#include <cstdlib>


#define gpuErrchk(ans) { gpuAssert( (ans), __FILE__, __LINE__ ); }

inline void
gpuAssert( cudaError_t code, const char * file, int line, bool abort = true )
{
        if ( cudaSuccess != code )
        {
                fprintf( stderr, "\nGPUassert: %s %s %d\n", cudaGetErrorString( code ), file, line );
                if ( abort )
                        exit( code );
        }


        return;

} /* gpuAssert */


__global__ void Add( int N ,int Offset ,float * devA , float * devB , float *devC )
{

        for ( int idx = blockIdx.x * blockDim.x + threadIdx.x + Offset; idx < N; idx += blockDim.x * gridDim.x )

                devC[ idx ] = devA[ idx ] + devB[ idx ];

}



int main()
{

        int N = 4000000;

        int Threads = 256;

        const int NbStreams = 8;

        float *A , *B , *C;
        gpuErrchk( cudaHostAlloc( (void**) &A , N * sizeof(*A) ,cudaHostAllocDefault ) );
        gpuErrchk( cudaHostAlloc( (void**) &B , N * sizeof(*B) ,cudaHostAllocDefault ) );
        gpuErrchk( cudaHostAlloc( (void**) &C , N * sizeof(*C) ,cudaHostAllocDefault ) );

        for ( int i = 0; i < N; i++ )
        {
                A[ i ] = i;
                B[ i ] = i + 1;
        }

        float *devA , *devB , *devC;
        gpuErrchk( cudaMalloc( (void**) &devA , N * sizeof(*devA)) );
        gpuErrchk( cudaMalloc( (void**) &devB , N * sizeof(*devB)) );
        gpuErrchk( cudaMalloc( (void**) &devC , N * sizeof(*devC)) );

        cudaEvent_t EventPre,
                    EventPost;
        float PostPreTime;

        gpuErrchk( cudaEventCreate( &EventPre ) );
        gpuErrchk( cudaEventCreate( &EventPost ) );

    cudaStream_t Stream[ NbStreams ];
        for ( int i = 0; i < NbStreams; i++ )
        gpuErrchk( cudaStreamCreate(&Stream[ i ]) );

#ifdef NOSTREAMS

        gpuErrchk( cudaEventRecord(EventPre ) );

        gpuErrchk( cudaMemcpy(devA, A, N * sizeof(*A), cudaMemcpyHostToDevice) );
        gpuErrchk( cudaMemcpy(devB, B, N * sizeof(*B), cudaMemcpyHostToDevice) );
//        gpuErrchk( cudaMemcpy(devC, C, N * sizeof(*C), cudaMemcpyHostToDevice) );

        Add<<< N / Threads, Threads>>>( N ,0, devA , devB , devC );

//        gpuErrchk( cudaMemcpy(A, devA, N * sizeof(*A), cudaMemcpyDeviceToHost) );
//        gpuErrchk( cudaMemcpy(B, devB, N * sizeof(*B), cudaMemcpyDeviceToHost) );
        gpuErrchk( cudaMemcpy(C, devC, N * sizeof(*C), cudaMemcpyDeviceToHost) );

        gpuErrchk( cudaEventRecord( EventPost ) );
        gpuErrchk( cudaEventSynchronize( EventPost ) );
        gpuErrchk( cudaEventElapsedTime( &PostPreTime, EventPre, EventPost ) );
        printf( "\nTime not using streams: %f ms\n", PostPreTime );

#else

        const int StreamSize = N / NbStreams;
        gpuErrchk( cudaEventRecord( EventPre ) );
        for ( int i = 0; i < NbStreams; i++ )
        {
                int Offset = i * StreamSize;

                gpuErrchk( cudaMemcpyAsync(&devA[ Offset ], &A[ Offset ], StreamSize * sizeof(*A), cudaMemcpyHostToDevice, Stream[ i ]) );
                gpuErrchk( cudaMemcpyAsync(&devB[ Offset ], &B[ Offset ], StreamSize * sizeof(*B), cudaMemcpyHostToDevice, Stream[ i ]) );
//                gpuErrchk( cudaMemcpyAsync(&devC[ Offset ], &C[ Offset ], StreamSize * sizeof(*C), cudaMemcpyHostToDevice, Stream[ i ]) );

                Add<<< StreamSize / Threads, Threads, 0, Stream[ i ]>>>( Offset+StreamSize ,Offset, devA , devB , devC );

//                gpuErrchk( cudaMemcpyAsync(&A[ Offset ], &devA[ Offset ], StreamSize * sizeof(*devA), cudaMemcpyDeviceToHost, Stream[ i ]) );
//                gpuErrchk( cudaMemcpyAsync(&B[ Offset ], &devB[ Offset ], StreamSize * sizeof(*devB), cudaMemcpyDeviceToHost, Stream[ i ]) );
                gpuErrchk( cudaMemcpyAsync(&C[ Offset ], &devC[ Offset ], StreamSize * sizeof(*devC), cudaMemcpyDeviceToHost, Stream[ i ]) );

        }

        gpuErrchk( cudaEventRecord( EventPost ) );
        gpuErrchk( cudaEventSynchronize( EventPost ) );
        gpuErrchk( cudaEventElapsedTime( &PostPreTime, EventPre,EventPost ) );
        printf( "\nTime using streams: %f ms\n", PostPreTime );

#endif /* ! USE_STREAMS */

        for ( int i = 0; i < N; i++ )
                if (C[i] != (A[i]+B[i])) {printf("mismatch at %d, was: %f, should be: %f\n", i, C[i], (A[i]+B[i])); return 1;}

        for ( int i = 0; i < NbStreams; i++ )
                gpuErrchk( cudaStreamDestroy(Stream[ i ]) );

        gpuErrchk( cudaFree(devA) );
        gpuErrchk( cudaFree(devB) );
        gpuErrchk( cudaFree(devC) );

        gpuErrchk( cudaFreeHost(A) );
        gpuErrchk( cudaFreeHost(B) );
        gpuErrchk( cudaFreeHost(C) );

        gpuErrchk( cudaEventDestroy(EventPre) );
    gpuErrchk( cudaEventDestroy(EventPost) );

        printf("\n");

        return 0;

}

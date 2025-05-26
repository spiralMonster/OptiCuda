#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <vector>

#define CHECK_CUDA_RUNTIME(call)                                                 \
    do {                                                                         \
        cudaError_t err = call;                                                  \
        if (err != cudaSuccess) {                                                \
            std::cerr << "CUDA Runtime Error: " << cudaGetErrorString(err)      \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl;     \
            exit(EXIT_FAILURE);                                                  \
        }                                                                        \
    } while (0)

#define CHECK_CUDA_DRIVER(call)                                                  \
    do {                                                                         \
        CUresult err = call;                                                     \
        if (err != CUDA_SUCCESS) {                                               \
            const char* errStr;                                                  \
            cuGetErrorString(err, &errStr);                                      \
            std::cerr << "CUDA Driver Error: " << errStr                         \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl;     \
            exit(EXIT_FAILURE);                                                  \
        }                                                                        \
    } while (0)


float benchmarkKernel(CUmodule module, const char* kernelName) {
    const int N = 1 << 20;
    size_t size = N * sizeof(float);

    float *h_A = new float[N], *h_B = new float[N];
    for (int i = 0; i < N; ++i) {
        h_A[i] = static_cast<float>(i);
        h_B[i] = static_cast<float>(2 * i);
    }

    float *d_A, *d_B, *d_C;
    CHECK_CUDA_RUNTIME(cudaMalloc(&d_A, size));
    CHECK_CUDA_RUNTIME(cudaMalloc(&d_B, size));
    CHECK_CUDA_RUNTIME(cudaMalloc(&d_C, size));

    CHECK_CUDA_RUNTIME(cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice));
    CHECK_CUDA_RUNTIME(cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice));

    CUfunction kernel;
    CHECK_CUDA_DRIVER(cuModuleGetFunction(&kernel, module, kernelName));

    void* args[] = { &d_A, &d_B, &d_C, (void*)&N };

    dim3 threads(256);
    dim3 blocks((N + threads.x - 1) / threads.x);

    cudaEvent_t start, stop;
    CHECK_CUDA_RUNTIME(cudaEventCreate(&start));
    CHECK_CUDA_RUNTIME(cudaEventCreate(&stop));
    CHECK_CUDA_RUNTIME(cudaEventRecord(start));

    CHECK_CUDA_DRIVER(cuLaunchKernel(kernel,
                                     blocks.x, 1, 1,
                                     threads.x, 1, 1,
                                     0, 0, args, 0));

    CHECK_CUDA_RUNTIME(cudaEventRecord(stop));
    CHECK_CUDA_RUNTIME(cudaEventSynchronize(stop));

    float ms = 0.0f;
    CHECK_CUDA_RUNTIME(cudaEventElapsedTime(&ms, start, stop));

    CHECK_CUDA_RUNTIME(cudaFree(d_A));
    CHECK_CUDA_RUNTIME(cudaFree(d_B));
    CHECK_CUDA_RUNTIME(cudaFree(d_C));

    CHECK_CUDA_RUNTIME(cudaEventDestroy(start));
    CHECK_CUDA_RUNTIME(cudaEventDestroy(stop));

    delete[] h_A;
    delete[] h_B;

    return ms;
}

int main() {
    CHECK_CUDA_DRIVER(cuInit(0));

    CUdevice device;
    CHECK_CUDA_DRIVER(cuDeviceGet(&device, 0));

    CUcontext context;
    CHECK_CUDA_DRIVER(cuCtxCreate(&context, 0, device));

    CUmodule module;
    CHECK_CUDA_DRIVER(cuModuleLoad(&module, "vectorAdd.ptx")); 

    float time = benchmarkKernel(module, "vectorAdd");

    std::cout << "Kernel execution time: " << time << " ms" << std::endl;

    CHECK_CUDA_DRIVER(cuModuleUnload(module));
    CHECK_CUDA_DRIVER(cuCtxDestroy(context));

    return 0;
}


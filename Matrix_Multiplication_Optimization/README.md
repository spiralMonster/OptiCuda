# Opticuda

Opticuda is a compiler-assisted CUDA optimization framework that uses LLVM IR transformations to generate high-performance GPU kernels. It automates low-level optimizations at the IR stage, enabling warp-level enhancements and shared memory transformations for common computational kernels.

## Features

- Warp-level optimization for matrix multiplication
- Shared memory optimization for 2D convolution
- Benchmarking system to compare naive vs. optimized kernels
- LLVM IR-level manipulation of CUDA device code

## Workflow

1. Create a CUDA source file for the desired operation.
2. Convert the CUDA file into an unoptimized `.ll` (LLVM IR) file.
3. Write a custom LLVM pass in C++ that takes the `.ll` file as input and outputs an optimized `.ll` file.
4. Convert both the naive and optimized `.ll` files into `.ptx` files.
5. Benchmark both `.ptx` kernels using host-side benchmarking code written in C++.

## Optimizations Implemented

### Warp-Level Optimization (Matrix Multiplication)

- Aligns memory access for coalescing
- Reduces warp divergence
- Enhances instruction-level parallelism and reuse

### Shared Memory Optimization (2D Convolution)

- Uses shared memory to cache input tiles
- Minimizes global memory traffic
- Reduces memory latency and bank conflicts


## Requirements

- LLVM 14+ with NVPTX backend
- CUDA Toolkit 11.x or newer
- Clang with CUDA support
- CMake
- NVIDIA GPU with compute capability 6.0+

## Build Instructions

Build the LLVM pass using CMake, then follow the workflow to run the full optimization pipeline.

## Author

Developed by Amartya Pawar

## License

MIT License. See `LICENSE` for more information.


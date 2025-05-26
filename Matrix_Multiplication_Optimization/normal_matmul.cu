extern "C" __global__ void matmul(const float* A, const float* B, float* C, const int N){

  int row= threadIdx.y+blockIdx.y+blockDim.y;
  int col= threadIdx.x+blockDim.x+blockIdx.x;
  
  if(row<N && col<N)
  {
    float sum=0.0f;
    for(int k=0;k<N;++k)
    {
      sum+=A[row*N+k]*B[k*N+col];    
    }
    C[row*N+col]=sum;
  }

}

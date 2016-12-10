
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdio>
#include<stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);

const int N = 265;
const int prethread = 256;


__device__ int Max(int a,int b)
{
	return a < b ? b : a;
}

__global__ void cal(int *a,int *t)
{
	__shared__ int share[prethread];
	int pos = threadIdx.x + blockDim.x * blockIdx.x;
	int id = threadIdx.x;
	int temp = 0;
	while(pos < N)
	{
		temp = Max(temp,a[pos]);
		pos += blockDim.x * gridDim.x;
	}
	share[id] = temp;
	__syncthreads();
	int size = blockDim.x /2;

	while(size != 0)
	{
		if(id < size)
			share[id] = Max(share[id],share[id + size]);
		size >>= 1;
	}
	if(id == 0)
		t[blockIdx.x] = share[id];
}

void solve(int *dev_a,int *dev_t)
{
	cal <<<min(32, (N + prethread -1)/ prethread),prethread >>> (dev_a,dev_t);
	int *t =(int *) malloc(sizeof(int) * N);
	cudaMemcpy(t,dev_t,sizeof(int )*N ,cudaMemcpyDeviceToHost);
	for(int i = 0;i <= min(32, (N + prethread -1));i++)
		cout << t[i] <<" " ;
	cout <<endl;
}

int main()
{
	int *dev_a,*dev_t,Max = 0;
	int *a = (int*)malloc(sizeof(int) * N );
	srand(NULL);
	for(int i = 0;i < N;i++)
	{
		a[i] = rand() % N;
		Max = max(Max,a[i]);
	}
	cout << Max <<endl;
	cudaMalloc( (void**)&dev_a,sizeof(int)*N );
	cudaMalloc( (void**)&dev_t,sizeof(int)*N );
	cudaMemcpy(dev_a,a,sizeof(int )*N ,cudaMemcpyHostToDevice);
	cout << "can" <<endl;
	solve(dev_a,dev_t);
    return 0;
}


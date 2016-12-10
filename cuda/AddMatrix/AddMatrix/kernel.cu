
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <device_functions.h>
#include <cuda.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
using namespace std ;
const int N = 100;
const int M = 10;

__global__ void add(int *a,  int *b,  int *c)
{
	int x = threadIdx.x + blockIdx.x * blockDim.x;
	int y = threadIdx.y + blockIdx.y * blockDim.y;
	int offset = x + y * blockDim.x * gridDim.x;

	c[offset] = a[offset] + b[offset];
}

void random(int *a,int n,int m)
{
	srand(NULL);
	for(int i = 0;i < n*m;i++)
		a[i] = rand()%n;
}

void print(int *a,char op)
{
	printf("Mat %c\n",op);
	for(int i = 0;i < N;i++)
	{
		for(int j = 0;j < M;j++)
			printf("%d ",a[i * M + j]);
	    cout <<endl;
	}
}

int main()
{
	freopen("out.txt","w",stdout);
	int *b = (int *)malloc(sizeof(int) * N * M);
	int *a = (int *)malloc(sizeof(int) * N * M);
	int *c = (int *)malloc(sizeof(int) * N * M);
	random(a,N,M);
	random(b,N,M);
	print(a,'a');
	print(b,'b');
	int *dev_a,*dev_b,*dev_c;
	cudaMalloc((void**)&dev_a,sizeof(int) * N * M);
	cudaMalloc((void**)&dev_b,sizeof(int) * N * M);
	cudaMalloc((void**)&dev_c,sizeof(int) * N * M);
	cudaMemcpy(dev_a,a,sizeof(int)*N*M,cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b,b,sizeof(int)*N*M,cudaMemcpyHostToDevice);
	dim3 gird((N+15/16),(M+15)/16);
	dim3 block(16,16);
	add<<<gird,block>>>(dev_a,dev_b,dev_c);
	cudaMemcpy(c,dev_c,sizeof(int)*N*M,cudaMemcpyDeviceToHost);
	print(c,'c');
}


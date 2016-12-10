/*
两次规约求解最大值
*/
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <cstdio>
#include<stdlib.h>
#include <iostream>
#include <string.h>

#define judge(res) if(res!=cudaSuccess){exit(-1);}  

using namespace std;
const int maxn = 1000;
const int N = 256;
const int Size = 1000;
__global__ void get_Max(int *ans,int *c)
{
	__shared__ int share[N];
	int id = threadIdx.x;
	int temp = -1,i = id;
	int pos = id + blockDim.x*blockIdx.x;
	int t = pos ;
	if(pos >= Size)
		return ;
	while(pos < Size)
	{
		if(temp < c[pos])
			temp = c[pos];
		pos += gridDim.x*blockDim.x;
	}
	share[id] = temp;
    __syncthreads();

	int len = blockDim.x/2;
	while(len)
	{
		if(id < len && t + len < Size)
		{
			if(share[id] < share[id + len])
			share[id] = share[id + len];
		}
		len >>= 1;
		__syncthreads();
	}
	if(id == 0)
	{
		ans[blockIdx.x] = share[id];
	}
}

__global__ void get_ans(int *ans,int *c,int l)
{
	__shared__ int ta[N];
	int id = threadIdx.x;
	ta[id] = c[id];
	int len = l / 2;
	while(len)
	{
		if(id < len && id+len < l)
		{
			if(ta[id] < ta[id+len])
				ta[id] = ta[id+len]; 
		}
		len >>= 1;
		__syncthreads();
	}
	if(id == 0)
		ans[0] = ta[id];
}

void cal(int *ans,int *toans,int *dev_a)
{
	get_Max<<<N,N>>>(toans,dev_a);
	int *out =(int*)malloc(sizeof(int )*N);
	cudaMemcpy(out,toans,sizeof(int)*N,cudaMemcpyDeviceToHost);
	printf("The first time:\n");
	for(int i = 0;i < (Size + N -1) / N;i++)
		printf("%d ",out[i]);
	printf("\n");

	cout << "the second time" <<endl;
	int *tans = (int*)malloc(sizeof(int));
	get_ans<<<1,(Size + N -1) / N>>>(ans,toans,(Size + N -1) / N);
	cudaMemcpy(tans,ans,sizeof(int),cudaMemcpyDeviceToHost);
	printf("%d\n",tans[0]);
}

int main()
{
	int *a,*dev_a;
	int *ans,*tans,*toans;
	freopen("read.txt","r",stdin);

	cudaMalloc((void**)&(dev_a),sizeof(int)*Size);
	cudaMalloc((void**)&(toans),sizeof(int)*N);
	cudaMalloc((void**)&(ans),sizeof(int));
	a = (int*)malloc(sizeof(int) * Size);
	tans = (int*)malloc(sizeof(int));

	cudaMemset(toans,0,sizeof(toans));
	cudaMemset(ans,0,sizeof(ans));
	memset(a,0,sizeof(a));
	for(int i = 0;i < Size;i++)
		scanf("%d ",&a[i]);
	//for(int i = 0;i < Size;i++)
	//	printf("%d ",a[i]);
	//printf("\n");

    cudaMemcpy(dev_a,a,sizeof(int)*Size,cudaMemcpyHostToDevice);
	cal(ans,toans,dev_a);
	return 0;
}
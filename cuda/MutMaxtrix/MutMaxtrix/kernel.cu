
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
const int block_size = 16;
__global__ void cal(int *a, size_t la, int *b,size_t lb,int *c,size_t lc,int n)
{
	__shared__ int matA[block_size][block_size];
	__shared__ int matB[block_size][block_size];
	const int tidc = threadIdx.x;  
	const int tidr = threadIdx.y;  
	const int bidc = blockIdx.x * block_size;  
	const int bidr = blockIdx.y * block_size;  
	int result = 0;
	for(int i = 0;i < n;i += block_size )
	{
		matA[tidr][tidc] = a[(tidr + bidr) * la +  tidc  + i];
		matB[tidr][tidc] = b[(tidr + i) * lb + tidc + bidc];
		syncthreads();
		for(int j = 0;j < block_size;j++)
		{
			result += matA[tidr][j] * matB[j][tidc];
		}
		syncthreads();	
	}
	c[(tidr + bidr) * lc +  tidc + bidc]  = result;
}

void print(int *a,int ldx,int ldy)
{
	for(int i = 0;i < ldx;i ++)
	{
		for(int j = 0;j < ldy;j++)
		{
			printf("%d ",a[i * ldy + j]);
		}
		printf("\n");
	}
}

void Get_Rand(int *a ,int n,int *b)
{
	srand(NULL);
	for(int i = 0;i < n * n;i++)
	{
		a[i] = rand()% n;
		b[i] = rand()% n;
	}
	/*printf("matA:\n");
	print(a,n,n);
	printf("matB:\n");
	print(b,n,n);*/
}

__global__ void cal1(int *a ,int la,int *b,int lb,int *c,int lc,int n)
{
	extern __shared__ int share[];
	int id = blockIdx.x;
	int tid = threadIdx.x;
	//for(int i = 0;i < la;i++)
	if(tid >= la) return ;
	share[tid] = a[id * la + tid];
	__syncthreads();

	for(int i = 0;i < la;i++)
	{
		c[id*lc + tid] += share[i] * b[i * lb + tid];
	}
}

void Get_ans(int *a,int *b,int la,int lb,int lc)
{
	int *c;
	c = (int*)malloc(sizeof(int) * la * lc);
	memset(c,0,sizeof(int)*la*lc);
	for(int i = 0;i < la;i++)
	{
		for(int j = 0;j < lc;j++)
		{
			for(int k = 0;k < lb;k++)
			{
				c[i*lc+j] += a[i*lb+k] * b[k*lc+j];
			}
		}
	}
	printf("dev_C\n");
	print(c,la,lc);
}

int lda = 4,ldb = 2;
int main()
{
	freopen("out.txt","w",stdout);
	int n = 100;
	int *a,*b,*c;
	int *dev_a,*dev_b,*dev_c;
	a = (int*)malloc(sizeof(int) * n * n);
	b = (int*)malloc(sizeof(int) * n * n);
	c = (int*)malloc(sizeof(int) * n * n);
	Get_Rand(a,n,b);
	Get_ans(a,b,n,n,n);
	
	//print(a,n,n);
	size_t pitch_a,pitch_b,pitch_c;
	cudaMallocPitch((void**)&dev_a,&pitch_a,sizeof(int)*n,n);
	cudaMallocPitch((void**)&dev_b,&pitch_b,sizeof(int)*n,n);
	cudaMallocPitch((void**)&dev_c,&pitch_c,sizeof(int)*n,n);
	cudaMemcpy2D(dev_a,pitch_a,a,sizeof(int)*n,sizeof(int) * n,n,cudaMemcpyHostToDevice);
	cudaMemcpy2D(dev_b,pitch_b,b,sizeof(int)*n,sizeof(int) * n,n,cudaMemcpyHostToDevice);
	int tx = (n + block_size -1) / block_size;
	cout << "pitch"<< pitch_a <<endl;
	cal1<<<n,block_size,block_size>>>(dev_a, pitch_a /sizeof(int),dev_b,pitch_b / sizeof(int),dev_c,pitch_c/sizeof(int),n);
	cudaMemcpy2D(c,sizeof(int)*n,dev_c,pitch_c,sizeof(int)*n,n,cudaMemcpyDeviceToHost);
	printf("matC\n");
	print(c,n,n);
	return 0;
}


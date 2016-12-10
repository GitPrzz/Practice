/*
cuda归并排序
由于合并的时候要并行。。。 所以并没有找到比较合适的并行方法。。
1.将所以数据弄入核函数,每个数对应一个线程,然后再枚举size进行归并
2.每个线程代表一个区间,然后枚举size,通过blockIdx可以知道当前的区间信息,然后串行合并。。
//都不如cpu的效率。。。
*/

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int N;
const int M = 256;
using namespace std;
void print(int *a)
{
	for(int i = 0;i < N;i++)
		cout <<a[i] <<" ";
	cout <<endl;
}
__device__ int Min(int a,int b)
{
	return a < b ? a : b;
}

//每个数对应一个线程
__global__ void cal(int *a,int *t,int len)
{
	int id = threadIdx.x + blockDim.x * blockIdx.x;
	if(id >= len) return ;
	int size = 2;
	while(size  < len * 2)
	{
		if(id % size == 0)
		{
			int st1 = id,ed1 = st1 + size/2; ed1 = Min(ed1,len);
			int st2 = ed1,ed2 = st2 + size/2; ed2 = Min(ed2,len);
			int pos = st1;
			while(st1 < ed1 && st2 < ed2)
			{
				if(a[st1] > a[st2])t[pos++] = a[st2++];
				else  t[pos++] = a[st1++];
			}
			while(st1 < ed1) t[pos ++] = a[st1++];
			while(st2 < ed2) t[pos++] = a[st2 ++];
		}
		__syncthreads();
		a[id] = t[id];
		size <<= 1;
	}
}
//每个区间对应一个线程
__global__ void cal_1(int *a,int *t,int Size,int len)
{
	int id = blockIdx.x;
	if(id >= len ) return ;
	int st1 = id*Size,ed1 = st1 + Size/2; ed1 = Min(ed1,len);
	int st2 = ed1,ed2 = st2 + Size/2; ed2 = Min(ed2,len);
	int pos = st1;
	while(st1 < ed1 && st2 < ed2)
	{
		if(a[st1] > a[st2])t[pos++] = a[st2++];
		else  t[pos++] = a[st1++];
	}
	while(st1 < ed1) t[pos ++] = a[st1++];
	while(st2 < ed2) t[pos++] = a[st2 ++];
	for(int i = st1;i < ed2 ;i ++)
		a[i] = t[i];
}


void debug(int *dev_t)
{
	int *b = (int *)malloc(sizeof(int) * N);
	cudaMemcpy(b,dev_t,sizeof(int)*N,cudaMemcpyDeviceToHost);
	print(b);
}
void Merge1(int *dev_a,int *dev_b)
{
	int size = 2;
	while(size < 2 * N)
	{
		cal_1<<<(N+size-1)/size,1>>>(dev_a,dev_b,size,N);
		//debug(dev_b);
		size <<= 1;
	}
}



//CPU部分
void mergearray(int a[], int first, int mid, int last, int temp[])  
{  
	mid = min(mid,N-1),last = min(last,N-1);
	int i = first, j = mid + 1 ;
	int m = mid,   n = last, k = 0;  
	while (i <= m && j <= n)  
	{  
		if (a[i] <= a[j])  temp[k++] = a[i++];  
		else  temp[k++] = a[j++];  
	}  
	while (i <= m)  temp[k++] = a[i++];  
	while (j <= n)  temp[k++] = a[j++];  
	for (i = 0; i < k; i++)   a[first + i] = temp[i];  
}  
void mergesort(int a[],int temp[])  
{  
	int size = 2;
	while(size < 2 * N)
	{
		for(int i = 0; i * size < N ;i++) mergearray(a,i*size,i*size+size/2-1,i*size + size-1,temp);
		size <<= 1;
	}
}  

void merge(int *a)
{
	int *p = (int *)malloc(sizeof(int) * N);
	mergesort(a, p);
}

void Merge(int *dev_a,int *dev_b)
{
	cout << N <<endl;
	cal<<<(N + M -1)/M,M>>>(dev_a,dev_b,N);
}

void cuda_time_cal1(int *dev_a,int *dev_b)
{	
	float time;
	cudaEvent_t s,t;
	cudaEventCreate(&s);
	cudaEventCreate(&t);
	cudaEventRecord(s,0);
	Merge(dev_a,dev_b);
	cudaEventRecord(t,0);
	cudaEventSynchronize(t);
	cudaEventElapsedTime(&time,s,t);
	printf("GPU1 Cost of time:%.5f ms\n",time);
	cudaEventDestroy(s);
	cudaEventDestroy(t);
}

void cuda_time_cal2(int *dev_a,int *dev_b)
{	
	float time;
	cudaEvent_t s,t;
	cudaEventCreate(&s);
	cudaEventCreate(&t);
	cudaEventRecord(s,0);
	Merge1(dev_a,dev_b);
	cudaEventRecord(t,0);
	cudaEventSynchronize(t);
	cudaEventElapsedTime(&time,s,t);
	printf("GPU2 Cost of time:%.5f ms\n",time);
	cudaEventDestroy(s);
	cudaEventDestroy(t);
}

void cpu_time_cal(int *a)
{	
	LARGE_INTEGER t1,t2,tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	merge(a);
	QueryPerformanceCounter(&t2);
	printf("Use Time:%f\n",(t2.QuadPart - t1.QuadPart)*1000.0/tc.QuadPart);
}

int main()
{
	int *a,*dev_a,*dev_b;
	int *b;
	cout << "请输入大小："<<endl;
	cin >> N;
	a = (int *) malloc(sizeof(int) * N);
	b = (int *) malloc(sizeof(int) * N);
	cudaMalloc((void**)&dev_a,sizeof(int) *N );
	cudaMalloc((void**)&dev_b,sizeof(int) *N );
	srand(time(NULL));
	for(int i = 0;i < N ;i++)
		a[i] = rand()%N;
	//print(a);

	cudaMemcpy(dev_a,a,sizeof(int)*N,cudaMemcpyHostToDevice);
	cuda_time_cal1(dev_a,dev_b);
	cudaMemcpy(b,dev_a,sizeof(int)*N,cudaMemcpyDeviceToHost);
	//print(b);

	cudaMemcpy(dev_a,a,sizeof(int)*N,cudaMemcpyHostToDevice);
	cuda_time_cal2(dev_a,dev_b);
	cudaMemcpy(b,dev_a,sizeof(int)*N,cudaMemcpyDeviceToHost);
	//print(b);

	return 0;
}

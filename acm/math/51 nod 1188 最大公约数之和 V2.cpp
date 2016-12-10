/*
51 nod 1188 最大公约数之和 V2

[1,i]中与i的 GCD(x,i)=t的个数可以看成 GCD(x/t,i/t)=1 ;即与i/t互质的个数。欧拉函数phi
但是我们要求的两两互质的情况,如果考虑枚举 最大公约数的值。那么[1,i]有phi[i]个,同理[1,i-1]中
有phi[i-1]个,所以求出欧拉函数后累加起来。
//超时,主要是枚举的时候 O(n),而求测试数据量T很大。

然后求找了下,发现可以预处理出所有的结果。然后直接进行O(1)的查询即可
也是先求出phi，然后看成 j=i*k，那么ans[j] += (phi(k)*i+phi(i)*k)即枚举j可能的所有情况。

hhh-2016/05/31 22:19:58
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
typedef long long ll;
using namespace std;
const int maxn = 5000050;
const ll mod = 1e9+7;
ll tans[maxn];
ll phi[maxn];

void read(int &ans){
	char last=' ',ch=getchar();
	while(ch<'0' || ch>'9')last=ch,ch=getchar();
	while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	if(last=='-')ans=-ans;
}

void Init()
{
    for(int i=1;i<maxn;i++) phi[i]=i;
    for(int i=2;i<maxn;i++)
        if(phi[i]==i)
            for(int j=i;j<maxn;j+=i)
                phi[j]=phi[j]/i*(i-1);
    //欧拉函数
    for(int i = 2;i < maxn;i++)
        tans[i] = phi[i];

    for(int i = 2;i*i<= (maxn-50);i++)
    {
        tans[i*i] +=  phi[i] * i;
        for(int k = i+1;k*i< maxn; k++)        // j = i*k
        {
            tans[k*i] += (k*phi[i] + i*phi[k]);
        }
    }
    for(int i = 1;i < maxn;i++)
        tans[i] += tans[i-1];
}

int main()
{
    Init();
    int T,n;
    T = 0;
    read(T);
    while(T--)
    {
        n = 0;
        read(n);
        printf("%I64d\n",tans[n]);
    }
    return 0;
}

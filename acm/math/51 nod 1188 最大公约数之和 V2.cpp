/*
51 nod 1188 ���Լ��֮�� V2

[1,i]����i�� GCD(x,i)=t�ĸ������Կ��� GCD(x/t,i/t)=1 ;����i/t���ʵĸ�����ŷ������phi
��������Ҫ����������ʵ����,�������ö�� ���Լ����ֵ����ô[1,i]��phi[i]��,ͬ��[1,i-1]��
��phi[i-1]��,�������ŷ���������ۼ�������
//��ʱ,��Ҫ��ö�ٵ�ʱ�� O(n),�������������T�ܴ�

Ȼ����������,���ֿ���Ԥ��������еĽ����Ȼ��ֱ�ӽ���O(1)�Ĳ�ѯ����
Ҳ�������phi��Ȼ�󿴳� j=i*k����ôans[j] += (phi(k)*i+phi(i)*k)��ö��j���ܵ����������

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
    //ŷ������
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

/*
hdu 5656 CA Loves GCD(n����ѡk�������Լ����)

����n����,ÿ����ѡk����������GCD,�����в��ظ�����ĺ�

��ʼ���˺ü��ζ�TLE,�䡣
1.����������ǿ�����dp�����,dp[i][j]��ʾǰi������GCDΪj�ĸ������
2.���������������i�ı����ĸ���lan[i],��ô���ĳ�ȡ������2^lan[i]-1
���Դ�������Լ��Ϊi�ķ�����

hhh-2016-04-02 22:14:36
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int maxn = 1050;
int mm = 1000;
ll bin[maxn];
const ll mod = 100000007;
vector<int >vec;
ll fa[maxn];
ll lan[maxn];
int main()
{
    int T,x,n;
    bin[0] = 1;
    for(int i = 1; i <= mm; i++)
    {
        bin[i] = bin[i-1]<<1;
        bin[i] %= mod;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(lan,0,sizeof(lan));
        memset(fa,0,sizeof(fa));
        for(int i = 0; i < n; i++)
        {
            scanf("%d",&x);
            lan[x]++;
        }
        for(int i = 1; i <= mm; i++)
        {
            ll t = 0;
            for(int j = i; j<=mm; j+=i)
                t += lan[j];
            fa[i] = bin[t]-1;
        }
        ll ans = 0;
        for(int k = mm; k; k--)
        {
            for(int t = k+k; t <=mm; t+=k)
                fa[k] = (fa[k]-fa[t]+mod)%mod;
            ans=(ans+k*fa[k]%mod)%mod;
        }
        printf("%I64d\n",ans%mod);
    }
    return 0;
}

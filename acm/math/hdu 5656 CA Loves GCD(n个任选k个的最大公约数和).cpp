/*
hdu 5656 CA Loves GCD(n个任选k个的最大公约数和)

给你n个数,每次任选k个数出来求GCD,求所有不重复情况的和

开始试了好几次都TLE,卒。
1.给出的题解是可以用dp来解决,dp[i][j]表示前i个数的GCD为j的个数情况
2.求出给出数中所有i的倍数的个数lan[i],那么它的抽取方案数2^lan[i]-1
可以处理出最大公约数为i的方案数

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

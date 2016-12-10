/*
hdu 5656 CA Loves GCD(n个任选k个的最大公约数和)2

给你n个数,每次任选k个数出来求GCD,求所有不重复情况的和

开始试了好几次都TLE,卒。
1.给出的题解是可以用dp来解决,dp[i][j]表示前i个数的GCD为j的个数情况
2.求出给出数中所有i的倍数的个数lan[i],那么它的抽取方案数2^lan[i]-1
可以处理出最大公约数为i的方案数

hhh-2016-04-03 14:29:30
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 1e8+7;
const int maxn = 1005;
int mm = 1000;
int gc[maxn][maxn];
ll dp[maxn][maxn];
int a[maxn];
int gcd(int a,int b)
{
    while(a%b)
    {
        int t = a%b;
        a = b;
        b = t;
    }
    return b;
}

int main()
{
    int n,m;
    int t;
    for(int i = 1; i <= mm; i++)
    {
        for(int j = i; j <= mm; j++)
            gc[i][j] =gc[j][i]= gcd(i,j);
    }
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        for(int i = 1; i <= n; i++)
        {

            for(int j = 1; j <= mm; j++)
            {
                dp[i][j] = (dp[i][j]+dp[i-1][j])%mod;
                dp[i][gc[a[i]][j]] =(dp[i][gc[a[i]][j]]+dp[i-1][j])%mod;
            }
            dp[i][a[i]]++;
        }
        ll ans = 0;
        for(int i = 1; i <= mm; i++)
        {
            ans = (ans+(ll)i*dp[n][i]%mod)%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

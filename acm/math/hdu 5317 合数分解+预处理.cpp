/*
hdu 5317 合数分解+预处理

problem:
查找区间[l,r]中 gcd(F[a[i]],F[a[j]])的最大值. F[x]为x的分解出的质因子种类数

solve:
可以先计算一下,1e6时质因子最多有7个. 所以可以dp[maxn][7]先预处理出质因子个数的前缀和.
然后查找 1~7谁出现了2次及以上

hhh-2016-08-21 10:38:45
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  ch[0]
#define rson  ch[1]
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 1000000;
const int INF = 1e9+10;


int prime[maxn+1];

void getPrime()
{
    memset(prime,0,sizeof(prime));
    for(int i = 2;i <= maxn;i++)
    {
        if(!prime[i]) prime[++prime[0]] = i;
        for(int j = 1;j <= prime[0] && prime[j] <= maxn/i;j++)
        {
            prime[prime[j]*i] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}

int getFactor(int x)
{
    int t = x;
    int fant = 0;
    for(int i = 1;prime[i] <= t/prime[i];i++)
    {
        if(t % prime[i] == 0)
        {
            fant ++;
            while(t % prime[i] == 0)
                t /= prime[i];
        }
    }
    if(t != 1)
        fant ++;
    return fant;
}

int dp[maxn+1][7];

int main()
{
    getPrime();
    for(int i = 0;i <= 7;i++)
        dp[0][i] = 0;
    for(int i = 1;i <= maxn;i++)
    {
        int t = getFactor(i);
        for(int j = 0;j < 7;j++)
        {
            if(t == j+1)
                dp[i][j] = dp[i-1][j] + 1;
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    int T;
    int a,b;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&a,&b);
        int tMax = 0;
        for(int i = 6;i >= 0;i--)
        {
            if(dp[b][i] - dp[a-1][i] > 1)
            {
                tMax =i;
                break;
            }
        }
        printf("%d\n",tMax+1);
    }
}

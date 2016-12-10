/*
poj3264 简单RMQ or 线段树
求解区间最大最小值的差
hhh-2016-02-02 19:44:29
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;
const int maxn = 50050;
int dp[maxn][20];
int dp1[maxn][20];
int tmap[maxn];
int mm[maxn];
void iniRMQ(int n)
{
    for(int i = 1; i <= n; i++)
    {
        dp[i][0] = tmap[i];
        dp1[i][0] = tmap[i];
    }
    for(int j = 1; j <= mm[n]; j++)
    {
        for(int i = 1; i+(1<<j)-1 <= n; i++)
        {
            dp[i][j] = max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
            dp1[i][j] = min(dp1[i][j-1],dp1[i+(1<<(j-1))][j-1]);
        }
    }
}

int RMQ(int x,int y)
{
    int k = mm[y-x+1];
    return max(dp[x][k],dp[y-(1<<k)+1][k])-min(dp1[x][k],dp1[y-(1<<k)+1][k]);
}

int main()
{
    int a,b,n,k;
    mm[0] = -1;
    for(int i = 1; i < 50050; i++)
    {
        mm[i] = (i&(i-1)) == 0 ? mm[i-1]+1:mm[i-1];
    }
    while(scanf("%d%d",&n,&k) != EOF)
    {
        for(int i = 1; i <= n; i++)
            scanf("%d",&tmap[i]);
        iniRMQ(n);
        while(k--)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",RMQ(a,b));
        }
    }
    return 0;
}

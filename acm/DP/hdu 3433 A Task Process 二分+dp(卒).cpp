/*
hdu 3433 A Task Process 二分+dp(卒)

dp方面毕竟若，着实没有想出来状态转移方程
主要是数据特别小,可以考虑二分答案然后通过判断来解决
如果知道了能够使用的时间limi.假设dp[i][j]表示前i个人完成j个A任务时最多能完成多少
个B任务
转移方程：
dp[i][j] = (dp[i-1][j-k] + (limi-k*a[i])*b[i],dp[i][j])

hhh-2016-04-10 21:02:38
*/
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
using namespace std;
const int mod = 1e9+7;
const int maxn = 205;
int a[maxn],b[maxn];
int x,y,n;
int dp[maxn][maxn];
bool cal(int limi)
{
    //dp[i][j] 前i个人完成j个A任务的情况下,最多完成多少个B
    memset(dp,-1,sizeof(dp));
    for(int i =0; i <= x && i*a[1] <= limi; i++)
    {
        dp[1][i] = (limi-i*a[1])/b[1];
    }

    for(int i = 2; i <= n; i++)
    {
        for(int j = 0; j <= x; j++)
        {
            for(int k = 0; k*a[i] <= limi && k <= j; k++)
            {
                if(dp[i-1][j-k] >= 0)
                    dp[i][j] = max(dp[i][j],dp[i-1][j-k]+(limi-k*a[i])/b[i]);
                //如果不是同一个工人,那么工作进而同时进行
            }
        }
    }
    return dp[n][x] >= y;
}

int main()
{
    int T;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&x,&y);
        int ma = 0;
        for(int i =1 ; i <= n; i++)
        {
            scanf("%d%d",&a[i],&b[i]);
            ma = max(ma,a[i]);
        }
        int l = 0,r = ma*x;
        int ans = 0;
        while(l <= r)
        {
            int mid = (l+r)>>1;

            if(cal(mid))
            {
                ans = mid;
                r = mid-1;
            }
            else
                l = mid + 1;
        }
        printf("Case %d: %d\n",cas++,ans);
    }
    return 0;
}

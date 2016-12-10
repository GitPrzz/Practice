/*
poj 2019 二维RMQ
前段时间不知道poj怎么了，现在补上
二维RMQ简单，求解区间最大最小值的差
hhh-2016-02-02 19:25:50
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
const int maxn = 255;
int dp[maxn][maxn][8][8];
int dp1[maxn][maxn][8][8];
int tmap[maxn][maxn];
int mm[maxn];
void iniRMQ(int n,int m)
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
        {
            dp[i][j][0][0] = tmap[i][j];
            dp1[i][j][0][0] = tmap[i][j];
        }
    for(int ti = 0; ti <= mm[n]; ti++)
        for(int tj = 0; tj <= mm[m]; tj++)
            if(ti+tj)
                for(int i = 1; i+(1<<ti)-1 <= n; i++)
                    for(int j = 1; j+(1<<tj)-1 <= m; j++)
                    {
                        if(ti)
                        {
                            dp[i][j][ti][tj] =
                                max(dp[i][j][ti-1][tj],dp[i+(1<<(ti-1))][j][ti-1][tj]);
                            dp1[i][j][ti][tj] =
                                min(dp1[i][j][ti-1][tj],dp1[i+(1<<(ti-1))][j][ti-1][tj]);

                        }
                        else
                        {
                            dp[i][j][ti][tj] =
                                max(dp[i][j][ti][tj-1],dp[i][j+(1<<(tj-1))][ti][tj-1]);
                            dp1[i][j][ti][tj] =
                                min(dp1[i][j][ti][tj-1],dp1[i][j+(1<<(tj-1))][ti][tj-1]);
                        }
                    }
}

int RMQ(int x1,int y1,int x2,int y2)
{
    int k1 = mm[x2-x1+1];
    int k2 = mm[y2-y1+1];
    x2 = x2 - (1<<k1) +1;
    y2 = y2 - (1<<k2) +1;
    return
        max(max(dp[x1][y1][k1][k2],dp[x1][y2][k1][k2]),
            max(dp[x2][y1][k1][k2],dp[x2][y2][k1][k2])) -
        min(min(dp1[x1][y1][k1][k2],dp1[x1][y2][k1][k2]),
            min(dp1[x2][y1][k1][k2],dp1[x2][y2][k1][k2]));
}

int main()
{
    int a,b,n,m,k;
    mm[0] = -1;
    for(int i = 1;i < 255;i++)
    {
        mm[i] = (i&(i-1)) == 0 ? mm[i-1]+1:mm[i-1];
    }
    while(scanf("%d%d%d",&n,&m,&k) != EOF)
    {
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                scanf("%d",&tmap[i][j]);
            }
        iniRMQ(n,n);
        while(k--)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",RMQ(a,b,a+m-1,b+m-1));
        }
    }
}

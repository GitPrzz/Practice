/*
HDU 5543 动态规划

给你一根长为m的长木板和一些小木棒，每一根小木棒有它的长度和价值，
这些小木棒要放在长木板上并且每一根小木棒的重心要在长木板上（即可以露出一半的长），
问最大价值是多少。

感觉有点像01背包的问题，只是有放半段的情况，于是用dp[i][j][k]保存前i个物品
在长度为j,有k个半段放着的最优解

感觉应该是没什么问题的，但是一直WR，最后看别人都说把l*2来避免奇数

for(int j = l; j >= (a[i]+1)/2; j--)
但感觉这样也没什么问题啊,当是奇数时留大于一半的位置

hhh-2016-03-07 23:06:09
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 2005*2;

ll dp[maxn][3];
int a[maxn];
ll v[maxn];

int main()
{
    int T,n,l;
    int cas = 1;
    scanf("%d",&T);
    while( T--)
    {
        scanf("%d%d",&n,&l);
        l *= 2;
        ll ans = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%I64d",&a[i],&v[i]);
            ans = max(v[i],ans);
            a[i] *= 2;
        }


        memset(dp,0,sizeof(dp));
        for(int i = 1; i <= n; i++)
        {
            for(int j = l; j >= a[i]/2; j--)
            {
                for(int k = 0; k <= 2; k++)
                {
                    if(k > 0)
                        dp[j][k] = max(dp[j][k],(ll)dp[j-a[i]/2][k-1]+v[i]);
                    if(j >= a[i])
                        dp[j][k] = max(dp[j][k],(ll)dp[j-a[i]][k]+v[i]);
                   ans = max(ans,dp[j][k]);
                }
            }
        }
        printf("Case #%d: %I64d\n",cas++,ans);
    }
    return 0;
}

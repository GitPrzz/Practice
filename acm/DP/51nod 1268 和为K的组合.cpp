/*
51nod 1268 和为K的组合

problem:
给你n个数，求能否从中选出若干个，使他们的和为K

solve:
总共只有20个数,所有考虑状态压缩解决.

hhh-2016/09/03-13:04:47
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 20010;
const double PI = acos(-1.0);
int a[maxn];
int dp[1<<20];
int vis[1<<20];
int flag;
int n,t;
void dfs(int state)
{
    if(flag)
        return ;
    if(state == (1<<n)-1)
        return ;

    for(int i = 0;i < n && !flag;i++)
    {
        if( !((1 << i) & state)  )
        {
            dp[state | (1<<i)] = dp[state] + a[i];
            if(vis[state | (1 << i)])
            continue;
            vis[state | (1 << i)] = 1;
            if(dp[state | (1<<i)] == t)
            {
                flag = 1;
                return ;
            }
            dfs(state | (1<<i));
        }
    }
    return;
}

int main()
{
     while(scanfi(n) != EOF)
     {
         scanfi(t);
         memset(vis,0,sizeof(dp));
         memset(dp,0,sizeof(dp));
         for(int i = 0;i < n;i++){
            scanfi(a[i]);
         }
         flag = 0;
         dfs(0);
         if(flag)
            printf("Yes\n");
         else
            printf("No\n");
     }
     return 0;
}

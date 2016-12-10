/*
hdu 4352 数位dp + 状态压缩

problem:
求[L,R]之间有多少个数,把它们看成字符串,其LIS == k.

solve:
很明显的数位dp,所以考虑怎么保存状态. k <= 10,所以可以用二进制来模拟lis的操作保存状态.
dp[i][j][k]表示 到第i位,lis状态为j,所求为k的情况.

hhh-2016-08-26 20:06:21
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
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 1004;

ll a,b;
int k;
ll dp[70][1<<10][11];
int t[70],tot;

int make_in(int x,int z)
{
    for(int i = x;i <= 10;i++)
    {
        if( (1 << i) & z)
        {
            z ^= (1 << i);
            z |= (1 << x);
            return z;
        }
    }
    return (z |= (1<<x));
}

int make_sum(int x)
{
    int num = 0;
    for(int i = 0;i <= 9;i++)
    {
        if((1 << i) & x)
            num ++;
    }
    return num;
}

ll dfs(ll len,int state,bool flag,bool first)
{
    ll ans = 0;
    if(len < 0)
        return make_sum(state) == k;

    int n = flag ? t[len]:9;
    if(!flag && dp[len][state][k] != -1)
        return dp[len][state][k];
    for(int i = 0;i <= n;i++)
    {
        ans += dfs(len-1,(first&&!i)? 0:make_in(i,state),flag && i == n,first && i == 0);
    }

    if(!flag)
        dp[len][state][k] = ans;
    return ans;
}

ll cal(ll cur)
{
    tot = 0;
    while(cur)
    {
        t[tot ++] = cur%10;
        cur /= 10;
    }
    return dfs(tot-1,0,1,1);
}

int main()
{
//    freopen("in.txt","r",stdin);
    int T,cas= 1;
    scanfi(T);
    memset(dp,-1,sizeof(dp));
    while(T--)
    {
        scanfl(a),scanfl(b),scanfi(k);
//        cout << cal(a-1) << " " << cal(b) <<endl;
        printf("Case #%d: %I64d\n",cas++,cal(b) - cal(a-1));
    }
    return 0;
}

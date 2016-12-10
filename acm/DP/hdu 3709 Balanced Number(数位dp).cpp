/*
hdu 3709 Balanced Number(数位dp)

problem:
求[a,b]平衡数的个数.(以这个数的某一位为支点,另外两边的数字大小乘以力矩).

solve:
可以枚举支点位置,然后数位dp计算力矩和为0的个数

hhh-2016-08-24 19:54:09
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
#define mod 1000003
using namespace std;
const int maxn = 100010;
ll dp[20][20][2005];
int t[20];
ll dfs(int len,int o,int all,int flag)
{
    if(len < 0)
        return all == 0;
    if(all < 0)
        return 0;
    if(dp[len][o][all] != -1 && !flag)
        return dp[len][o][all];
    int n = flag ? t[len]:9;
    ll ans = 0;
    for(int i = 0;i <= n;i++)
    {
        int ta = all;
        ta += (len - o) * i;
        ans += dfs(len-1,o,ta, flag && i == n);
    }
    if(!flag)
        dp[len][o][all] = ans;
    return ans;
}


ll cal(ll b)
{

    int tot = 0;
    while(b)
    {
        int p = b % 10;
        t[tot++] = p;
        b /= 10;
    }
    ll ans = 0;
    for(int i = 0; i <tot; i++)
        ans += dfs(tot-1,i,0,1);
//    cout <<ans <<endl;
    return ans-(ll)(tot-1);
}

int main()
{
    int T;
    ll a,b;
//    freopen("in.txt","r",stdin);
    scanfi(T);
    memset(dp,-1,sizeof(dp));
    while(T--)
    {
        scanfl(a),scanfl(b);
//        cout << a <<" " <<b <<endl;
        printf("%I64d\n",cal(b) - cal(a-1));
    }
}

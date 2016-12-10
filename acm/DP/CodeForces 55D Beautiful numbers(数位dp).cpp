/*
CodeForces 55D Beautiful numbers(数位dp)

problem:
问[l,r]之间有多少个能被它所包含的非零数整除

solve:
如果能这些数整除,则能被他们的最小公倍数整除. 1~9的最小公倍数为2520,所以在过程中维护lcm和这个数对2520的取余
而且可以处理出1~9的所有lcm,离散化处理.

hhh-2016-08-25 16:56:23
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
const ll mod = 2520;
const int maxn = 100010;
int tot,t[maxn];
ll dp[20][3000][50];
int bin[3000];
int cnt = 0;
int lcm(int a,int b)
{
    if(!a && !b)
        return 0;
    if(!a)  return b;
    if(!b)  return a;
    int ta=a,tb=b;
    while(a % b != 0)
    {
        int p = a % b;
        a = b;
        b = p;
    }
    return ta/b*tb;
}

int fin(int pos)
{
    int l = 0,r = cnt-1;
    while(l < r)
    {
        int mid = (l+r) >> 1;
        if(bin[mid] > pos)
        {
            r = mid -1;
        }
        else if(bin[mid] == pos)
        {
            return mid;
        }
        else
            l = mid + 1;
    }
}

ll dfs(int len,int nex,int div,int flag)
{
    if(len < 0 && div == 0)
        return 0;
    if(len < 0)
        return nex % div == 0;
    int tp = bin[div];
    if(dp[len][nex][tp] != -1 && !flag)
        return dp[len][nex][tp] ;
    ll ans = 0;
    int n = flag ? t[len] : 9;
    for(int i = 0; i <= n; i++)
    {
        int lc;
        lc = lcm(div,i);
//        cout << lc <<" " << i <<endl;
        int ta = (nex*10+i) % mod;
        ans += dfs(len-1,ta,lc,flag && i == n);
    }
//    cout << ans<<" "<<div<<endl;
    if(!flag)
        dp[len][nex][tp] = ans;
    return ans;
}

ll cal(ll a)
{
    tot = 0;
    while(a)
    {
        int p = a%10LL;
        t[tot++] = p;
        a /= 10LL;
    }
    ll ans = 0;
    ans += dfs(tot-1,0,0,1);
    return ans;
}
ll a,b;
int main()
{
    int T;
    cnt = 0;
    bin[cnt++] = 0;
    for(int i = 1;i <= mod;i++)
    {
        if(mod % i == 0)
           bin[i] = cnt++;
    }
//    freopen("in.txt","r",stdin);
    memset(dp,-1,sizeof(dp));
    scanfi(T);

    while(T--)
    {
        scanfl(a),scanfl(b);
        printf("%I64d\n",cal(b) - cal(a-1));
    }
}

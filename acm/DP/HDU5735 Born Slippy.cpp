/*
HDU5735 : Born Slippy

给定一棵n个节点的带点权树,根节点为1.对每个节点i,选出一个序列v1,v2,…,vm,满足v1=i,且vi是vi−1的祖先(1<i≤m),
定义f(i)为所有选取方案中   w[v1]+∑(w[vi] opt w[vi−1])的最大值,
其中opt是给定的位运算(可能是and,or,xor,一组case中给出的运算是相同的).
求 sum(i*f(i))%mod

最好就是能够在一次树的遍历中解决，然后想到如果走到了i节点，记录了其祖先的w值，然后枚举2^16次方找出最大值
dp[i] = max(dp[i],dp[j] + w[i] opt w[j])
那么 2^16*n 超时  卒- -

官方题解是使用的一个二维数组来进行优化：
如果走到了u点，w[u]可以看成前8位A 和 后8位B。
f[x][y]表示 一个w[i]的前8位x 一个w[j]的后8位为y时 w[i]后8位与w[j]后8位的计算的最大值
那么通过 枚举x来查找 枚举y来维护f数组(2^8)

具体解释：
https://async.icpc-camp.org/d/493-2016-multi-university-training-contest-2

hhh-2016-08-05 15:50:05
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <set>
#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std;
typedef long long ll;
const int maxn=65540;
const int INF=0x3f3f3f3f;
const int mod = 1e9+7;
int tot;
ll val[maxn];
ll f[256][256];
ll t[maxn][256];
int head[maxn];
ll ans= 0 ;
int vis[maxn];
struct node
{
    int from,to,next;
}edge[maxn<<1];

void add_edge(int u,int v)
{
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot ++ ;
}

char s[5];

ll cal(ll a,ll b)
{
    if(s[0] == 'A')
        return a&b;
    else if(s[0] == 'X')
        return a^b;
    else if(s[0] == 'O')
        return a|b;
}

ll Max(ll a,ll b)
{
    if(a < b)return b;
    else return a;
}

void dfs(int u)
{
    int A = val[u] >> 8;
    int B = val[u]&255;
    ll dp = 0 ;
    for(int i = 0;i < 256;i++)                      //通过枚举x就能找出前面出现的所有情况
    {
        if(vis[i])
            dp = Max(dp,f[i][B] + (cal(A,i) <<8));
    }
    ans = (ans + (ll)u*(dp+val[u])%mod)%mod;
    vis[A]++;
    for(int i =0 ;i < 256;i++)                      //预先处理出后面所有可能出现的情况
    {
        t[u][i] = f[A][i];
        f[A][i] = Max(f[A][i],cal(i,B) + dp);
    }
    for(int i = head[u];~i;i = edge[i].next)
    {
        dfs(edge[i].to);
    }
    vis[A]--;
    for(int i =0 ;i < 256;i++)
    {
        f[A][i]=t[u][i];
    }
}

int main()
{
    int T;
    int n,a;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        tot = 0;
        scanf("%d%s",&n,s);
        memset(head,-1,sizeof(head));
        memset(f,0,sizeof(f));
        for(int i = 1;i <= n;i++)
            scanf("%I64d",&val[i]);

        for(int i = 2;i <= n;i++)
        {
            scanf("%d",&a);
            add_edge(a,i);
        }
        ans = 0;
        dfs(1);
        printf("%I64d\n",ans);
    }
    return 0 ;
}

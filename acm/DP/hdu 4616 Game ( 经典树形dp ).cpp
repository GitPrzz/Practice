/*
hdu 4616 Game ( 经典树形dp )
树形dp 可以从任意点开始 ? 根节点是神马
记忆化搜索

想的是用普通的树形dp,通过dp[now][tra]保存在now点时被抓了tra次的情况.
但是弄完一直有问题
后来发现，这种方案无法确定答案，假设 a-b-c。   从a到b和从c到b的状态不一样,所以以保存点的记忆化搜索会有问题

于是用now来表示边的状态，像这样无论从哪个点开始状态都是唯一的。
而且在搜索中逗比地把tra的状态变了，但是这样还是过了很多数据(很烦)，导致一直改。。。

hhh-2016-08-04 20:42:49
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
using namespace std;
typedef long long ll;
const int maxn=50000+10;
const int INF=0x3f3f3f3f;
const int mod = 250000+10;
int tot;
int val[maxn];
int trap[maxn];
int head[maxn];
int dp[maxn*2][4];
int limit;
struct edge
{
    int from,to,next;
} edge[maxn << 2];

void ini()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(dp,-1,sizeof(dp));
}

void add_edge(int u,int v)
{
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int dfs(int now,int tra)
{
    //cout <<now <<" "<<tra <<endl;
    if(tra == limit)
        return 0;
    if(dp[now][tra] != -1)
        return dp[now][tra];
    int u = edge[now].from;
    int v = edge[now].to;

    int tp = tra+trap[v];
    int value = val[v];
    for(int i = head[v]; ~i ; i = edge[i].next)
    {
        if(edge[i].to != u){
           // cout << "node:"<<v <<" to:"<<edge[i].to<< " limit:"<<tra <<" value:" <<value <<endl;
            value = max(value,dfs(i,tp)+val[v]);
            //cout << "node:"<<v <<" to:"<<edge[i].to<< " limit:"<<tra <<" value:" <<value <<endl;
        }
    }
    return (dp[now][tra] = value );
}


int main()
{
    int T,n;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d%d",&n,&limit);
        //cout << limit << endl;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d",&val[i],&trap[i]);
            // cout << val[i] <<" " << trap[i] <<endl;
        }
        int a,b;
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);
            // cout << a <<" " << b <<endl;
        }
        int ans = 0;
       // cout << tot <<endl;
        for(int i = 0; i < tot; i++)
        {
            //if(i == 5)
            ans = max(ans,dfs(i,trap[edge[i].from])+val[edge[i].from]);
            //cout << ans <<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}

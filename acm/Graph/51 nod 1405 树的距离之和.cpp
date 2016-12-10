/*
51 nod 1405 树的距离之和

problem:
给定一棵无根树，假设它有n个节点，节点编号从1到n, 对于每个i求所有点到i的和。

solve:
假设已经知道了所有点到u的和, 对于它右儿子v的和,可以发现增加了Size[左子树]条uv边.减少了Size[v]条uv边
所以先求出所有点到1的和,然后可以推出其它所有点

hhh-2016/09/13-20:15:59
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
const int maxn = 100110;

template<class T> void read(T&num)
{
    char CH;
    bool F=false;
    for(CH=getchar(); CH<'0'||CH>'9'; F= CH=='-',CH=getchar());
    for(num=0; CH>='0'&&CH<='9'; num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p)
{
    if(!p)
    {
        puts("0");
        return;
    }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}

ll ans[maxn];
struct node
{
    int to,next;
}edge[maxn <<2];

int tot,n;
int head[maxn];
int Size[maxn];
ll f[maxn];
void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u],head[u] = tot ++;
}

void dfs(int u,ll len,int pre)
{
    f[u] = len;
    Size[u] = 1;
    for(int i = head[u]; i != -1;i = edge[i].next )
    {
        int v = edge[i].to;
        if(v == pre)
            continue;
        dfs(v,len+1,u);
        Size[u] += Size[v];
    }
}

void solve(int u,ll tans,int pre)
{
    ans[u] = tans;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)
            continue;
        ll t = n-Size[v]*2;
        solve(v, (ll)tans + t,u);
    }
}

void init()
{
    tot = 0;
    clr(head,-1);
}

int main()
{
    int u,v;
    while(scanfi(n) != EOF)
    {
        init();
        for(int i = 1;i < n;i++)
        {
            scanfi(u),scanfi(v);
            add_edge(u,v);
            add_edge(v,u);
        }
        dfs(1,0,-1);
        ll ta = 0;
        for(int i =1;i <= n;i++)
          ta += f[i];
        solve(1,ta,-1);
        for(int i = 1;i <= n;i++)
        {
            print(ans[i]);
        }
    }
}

/*
51 nod 1456 小K的技术(强连通 + 并查集)

problem:
给你n个城市和m次操作. 每次a,b表示两个城市a->b之间应该连通. 而添加的管道是单向的,求最少需要多少的
管道才能满足要求.

solve:
在一个联通块里面,可以发现最糟糕的情况就是没有环,那么n-1条就能够满足条件.
但是如果存在环,这样的话n个点需要围成一个圈,所以需要n条管道.

所以可以用tarjan算法来判断一下强连通就好了,只要存在强连通分支,则说明当前联通块需要n个管道.
然后用并查集来记录每个联通块中点的数量.
- - 一直WR. 结果发现如果联通块a和联通块b被一个单向边连接. 我在搜索a的时候并不能到达b,判断出现了一些问题,
这里注意一下就好了

hhh-2016/09/08-21:11:22
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
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
const ll mod = 1000000007;
const int maxn = 300050;
const double PI = acos(-1.0);
const int limit = 33;
int pre[maxn];
int cnt[maxn];
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

int fin(int x)
{
    if(pre[x] == x) return x;
    return pre[x] = fin(pre[x]);
}

void unio(int a,int b)
{
    int ta= fin(a);
    int tb = fin(b);
    if(ta == tb)
        return ;
    pre[tb] = ta;
    cnt[ta] += cnt[tb];
}

int tot = 0;
int index,top,scc;
int head[maxn];
int low[maxn],dfn[maxn],Stack[maxn],Belong[maxn],num[maxn];
bool Instack[maxn];
ll ans[maxn];
struct node
{
    int u,v,nex;
} edge[maxn];

void add_edge(int u,int v)
{
    edge[tot].u = u,edge[tot].v = v,edge[tot].nex = head[u],head[u] = tot++;
}

void init()
{
    tot = 0;
    for(int i = 1; i <= maxn-50; i++)
    {
        ans[i] = 0;
        head[i] = -1,pre[i] = i;
        num[i] = dfn[i] = 0;
        Instack[i] = false;
        cnt[i] = 1;
    }
    index = top = scc = 0;
}
int flag;
//ll cnt;
void Tarjan(int u)
{
    int v;
//    if(!dfn[u])
//        cnt ++ ;
    low[u] = dfn[u] = ++index;
    Stack[top++] = u;
    Instack[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].nex)
    {
        v = edge[i].v;
        if(! dfn[v])
        {
            Tarjan(v);
            if(low[u] > low[v])
                low[u] = low[v];
        }
        else if(Instack[v] && low[u] > dfn[v])
            low[u] = dfn[v];
    }
    if(low[u] == dfn[u])
    {
        scc ++ ;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = scc;
            num[scc] ++ ;
            if(num[scc] > 1)
                flag = 1;
        }
        while(v != u);
    }
}


int main()
{
//    freopen("in.txt","r",stdin);
    int n,m;
    int u,v;

    while(scanfi(n) != EOF)
    {
        scanfi(m);
        init();
        for(int i = 1; i <= m; i++)
        {
            read(u),read(v);
            add_edge(u,v);
            unio(u,v);
        }
        for(int i = 1; i <= n; i++)
        {
            if(!dfn[i])
            {
                flag = 0;
                Tarjan(i);
                int anc = fin(i);
                if(ans[anc] == cnt[anc])
                    continue;
                if(flag)
                    ans[anc] = cnt[anc];
                else
                    ans[anc] = cnt[anc]-1;
            }
        }
        ll toans = 0;
        for(int i = 1;i <= n;i++)
            toans += ans[i];
        printf("%I64d\n",toans);
    }
    return 0;
}
/*
4 6
1 2
1 4
2 3
2 4
3 2
3 4



*/

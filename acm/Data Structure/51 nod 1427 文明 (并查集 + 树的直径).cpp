/*
51 nod 1427 文明 (并查集 + 树的直径)

problem:
给你n个城市,m条双向边连接,然后是q个查询
1 x: 城市x所在的区域的最长道路
2 x y:将两个城市的所在区域连接,要求维护最长路最短.

solve:
一个区域的最长路就相当于树的直径.因为两个城市之间最多只有一条路径.
合并的话,如果要求最短，那么相当于将两条直径的中点相连. 所以已知A,B的直径可计算出新的直径的值
(注意还要与A,B的直径进行下比较).
先处理出每个区域的树的直径.然后可给每个区域打上标记,用并查集合并维护一下区域的树的直径.

hhh-2016/09/27-17:21:09
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <math.h>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 3e5 + 100;
const int inf = 0x3f3f3f3f;
const ll mod = 1000000007;
const double eps = 1e-7;
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

struct node
{
    int v,next;
} edge[maxn << 1];
ll Max;
int tot,pos;
int head[maxn];
int vis[maxn];
//int ans[i];
int pre[maxn];
struct Node
{
    ll dis;
    int pre;
} pnode[maxn];
void init(int n)
{
    memset(head,-1,sizeof(head));
    tot = 0;
    for(int i = 1; i <= n; i++)
    {
        vis[i] = 0;
        pnode[i].pre = i;
        pnode[i].dis = 1;
    }
}
void add_edge(int u,int v)
{
    edge[tot].v = v,edge[tot].next = head[u],head[u] = tot ++;
}

void dfs(int u,int fa,ll len,int anc)
{
    vis[u] = 1;
    pnode[u].pre = anc;
    if(len > Max)
    {
        Max = len;
        pos = u;
    }

    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].v;
        if(v == fa)
            continue;
        dfs(v,u,len + 1LL,anc);
    }
}


void cal(int now)
{
    int from;
    pos = 0,Max =0 ;
    dfs(now,-1,0,now);
    from = pos;
    pos = 0,Max = 0;
    dfs(from,-1,0,now);
    pnode[now].dis = Max;
}


int fin(int u)
{
    if(pnode[u].pre != u)
        return pnode[u].pre = fin(pnode[u].pre);
    return u;
}

void unio(int u,int v)
{
    int ta = fin(u);
    int tb = fin(v);

    if(ta == tb)
        return ;
    if(ta > tb)
        swap(ta,tb);
    pnode[ta].pre =tb;
    ll tMax = 0;
    tMax = max(pnode[ta].dis,pnode[tb].dis);
    tMax = max(tMax,(pnode[ta].dis+1LL)/2LL+(pnode[tb].dis + 1LL)/2LL + 1LL);
    pnode[tb].dis = tMax;
    pnode[ta].dis= tMax;
}

int main()
{
    int n,m,q;
    int u,v,ob;
    read(n),read(m),read(q);
    init(n);
    for(int i = 1; i <= m; i++)
    {
        read(u),read(v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i = 1;i <= n;i++)
    {
        if(!vis[i])
            cal(i);
    }
    for(int i = 1; i <= q; i++)
    {
        read(ob);
        if(ob == 1)
        {
            read(u);
            int ta = fin(u);
            print(pnode[ta].dis);
        }
        else
        {
            read(u),read(v);
            unio(u,v);
        }
    }
    return 0;
}

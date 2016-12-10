/*
hdu 4514 并查集+树形dp

problem:
给你一个图,如果其中有环,则输出YES. 否则输出其中最长链的长度

solve:
通过并查集可以判断是否有环. 树形dp计算经过当前节点最长链的长度.

hhh-2016-08-24 21:02:37
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
int fa[maxn];
int head[maxn];
int dp[maxn];
int tot ;
void ini()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(fa,-1,sizeof(fa));
    memset(dp,-1,sizeof(dp));
}
struct node
{
    int to,w,next;
} edge[maxn*20];
void add_edge(int u,int v,int w)
{
    edge[tot].to = v,edge[tot].w = w,edge[tot].next = head[u],head[u] = tot ++;
}

int fin(int x)
{
    if(fa[x] == -1) return x;
    return fa[x] = fin(fa[x]);
}
int tans = 0;

int dfs(int now,int far)
{
    int tnex = 0;
    for(int i = head[now]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == far)
            continue;
        int re = dfs(v,now);
        tans = max(tans,tnex+re +edge[i].w);
        tnex = max(tnex,re + edge[i].w);
    }
    return dp[now] = tnex;
}

int main()
{
    int n,m;
    int u,v,w;
//    freopen("in.txt","r",stdin);
    while(scanfi(n) != EOF)
    {
        scanfi(m);
        ini();
        int flag =0 ;
        for(int i = 1; i <= m; i++)
        {
            scanfi(u),scanfi(v),scanfi(w);
            add_edge(u,v,w);
            add_edge(v,u,w);
            int ta = fin(u);
            int tb = fin(v);
            if(ta == tb)
                flag = 1;
            else
                fa[ta] = tb;
        }
        tans = 0;
        if(flag)
            printf("YES\n");
        else
        {
            for(int i =1; i <= n; i++)
            {
                if(dp[i] == -1)
                {
                    dfs(i,-1);
//                    cout <<tans << endl;
                }
            }
            printf("%d\n",tans);
        }
    }
    return 0;
}

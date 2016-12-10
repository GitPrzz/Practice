/*
hdu 5727 二分图+环排列

problem:
要用ｎ个阳石和ｎ个阴石来串一个项链（环状），规定阳石旁边只能是阴石，阴石旁只能是阳石，现在有ｍ对特殊阴阳石，
这些阴阳石相邻会使得阳石出故障（照样可以用），问串这个项链，至少有几个故障的阳石。

solve:
最开始一看题就感觉应该是二分匹配,发现往环的阴石中添加阳石每个位置要考虑左右两边的情况
所以可以枚举阴石的所有情况.然后对每个空位和所有阳石之间建图。即这里可以放阳石就置为1,然后跑个最大匹配得出cnt
那么n-cnt就是当前情况最少的故障数

枚举这个是用的系统自带的next_permutation,但是一直超时.后来看别人题解才发现环排列只需要(n-1)!.所以可以固定一个
位置的值,枚举剩下的即可

hhh-2016-08-16 11:07:51
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <stdlib.h>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 11;
const int inf = 10000;
struct node
{
    int to,next;
} edge[maxn*maxn];
int tot;
int tmap[maxn][maxn];
int head[maxn];

void add(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u];
    head[u] = tot++;
}
int link[maxn],vis[maxn];
bool dfs (int u)
{
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!vis[v])
        {
            vis[v] = 1;
            if (link[v] == -1 || dfs (link[v]))
            {
                link[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int n,m;
int ans = inf;

int cal()
{
    int res = 0;
    memset(link,-1,sizeof(link));
    for(int i = 1; i <= n; i++)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i))
            res ++;
    }
    return n-res;
}
int po[maxn*2];

int main()
{
    while(scanf("%d%d",&n,&m) != EOF)
    {

        memset(tmap,0,sizeof(tmap));
        int a,b;
        for(int i =1; i <= m; i++)
        {
            scanf("%d%d",&a,&b);
            tmap[a][b] = 1;
        }
        if(!n || !m)
        {
            printf("0\n");
            continue;
        }
        for(int i = 1; i <= n; i++)po[i] = i;
        ans = inf;
        do
        {
            tot = 0;
            memset(head,-1,sizeof(head));
            for(int i =1; i <= n; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    int pre = i-1,next = i;
                    if(!pre) pre = n;
                    if(!tmap[j][po[pre]] && !tmap[j][po[next]])
                        add(j,i);
                }
            }
            ans = min(ans,cal());
            if(!ans)
                break;
        }
        while(next_permutation(po+2,po+n+1));
        printf("%d\n",ans);
    }
    return 0;
}

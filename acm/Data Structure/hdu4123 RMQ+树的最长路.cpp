/*
hdu4123
给你n个点，被n-1条边连着，求出以他们每个点为起点的最长路（不可重复走），
然后是m个查询，找出它们的最长连续串max-min<q
树的最长路 + RMQ
hhh-2016-01-31 03:04:55
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;

const int maxn = 50005;

ll dp1[maxn][20];
ll dp2[maxn][20];
int mm[maxn+5];
ll sum[maxn];
int tot;
int head[maxn];

ll min(ll a,ll b)
{
    return a < b ? a:b;
}

ll max(ll a,ll b)
{
    return a > b ? a:b;
}

struct node
{
    int to,next;
    ll w;
} edge[maxn*2];

void addedge(int u,int v,int w)
{
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}

void iniRMQ(int n,ll c[])
{
    mm[0] = -1;
    for(int i = 1; i <= n; i++)
    {
        mm[i] = ((i&(i-1)) == 0)? mm[i-1]+1:mm[i-1];
        dp1[i][0]=dp2[i][0]= c[i];
    }
    for(int j = 1; j <= mm[n]; j++)
    {
        for(int i = 1; i+(1<<j)-1 <= n; i++)
        {
            dp1[i][j] = min(dp1[i][j-1],dp1[i+(1<<(j-1))][j-1]);
            dp2[i][j] = max(dp2[i][j-1],dp2[i+(1<<(j-1))][j-1]);
        }
    }
}

ll RMQ(int x,int y)
{
    int k = mm[y-x+1];
    return (ll)max(dp2[x][k],dp2[y-(1<<k)+1][k])-(ll)min(dp1[x][k],dp1[y-(1<<k)+1][k]);
}
int id;
ll tall;

void dfs(int u,int pre,ll cnt)    //先找出最远点
{
    if(cnt >= tall)
    {
        id = u;
        tall = cnt;
    }
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        if(edge[i].to == pre) continue;
        dfs(edge[i].to,u,edge[i].w+cnt);
    }
}

void cal(int u,int pre,ll cnt)
{
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)
            continue;
        sum[v] = max(sum[v],cnt+edge[i].w);
        cal(v,u,cnt+edge[i].w);
    }
}

int main()
{
    int m,n,k;
    while(scanf("%d%d",&n,&m) && n && m)
    {
        int u,v,val;
        tot = 0;
        memset(head,-1,sizeof(head));
        memset(sum,0,sizeof(sum));
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d%d",&u,&v,&val);
            addedge(u,v,val);
            addedge(v,u,val);
        }
        tall = 0;
        dfs(1,0,0);
        cal(id,0,0);
        int t = 1;
        for(int i = 1;i <= n;i++)
            if(sum[i] > sum[t]) t = i;
//        printf("%d %d\n",id,t);
        cal(t,0,0);
//        for(int i = 1;i <= n;i++)
//            printf("%d ",sum[i]);
//        cout << endl;
        iniRMQ(n,sum);
        while(m--)
        {
            scanf("%d",&k);
            int ans = 0;
            int td = 1;
            for(int i = 1;i <= n;i++)
            {
                while(td <= i && RMQ(td,i) > k) td++;
                ans = max(ans,i-td+1);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}

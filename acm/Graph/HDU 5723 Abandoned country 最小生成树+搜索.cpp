/*
HDU 5723 Abandoned country 最小生成树+搜索

problem:
给你n个点和m条边，让你求最少花费多少可以将所有点连通并求出任意两点的花费期望

solve:
第一个直接求最小生成树。主要是不懂它这个期望到底要求什么。看题解说的是深搜求出每条路用过
的次数来得到总花费。然后除以可能发生的次数

by——hhh
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#define lson  ch[r][0]
#define rson  ch[r][1]
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
int vis[maxn];
int f[maxn];
vector<pair<int,int>> q[maxn];
struct Edge
{
    int u,v,w;
} edge[1000010];

int tot;

void add(int u,int v,int val)
{
    edge[tot].u = u,edge[tot].v = v,edge[tot++].w = val;
}

bool cmp(Edge a,Edge b)
{
    return a.w < b.w;
}

int fin(int x)
{
    if(f[x] == -1) return x;
    return f[x] = fin(f[x]);
}

ll cal(int n)
{
    memset(f,-1,sizeof(f));
    sort(edge,edge+tot,cmp);
    ll cnt = 0,ans = 0;
    for(int i = 0; i < tot; i++)
    {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;
        int t1 = fin(u),t2 = fin(v);
        if(t1 != t2)
        {
            ans = (ll)(ans + w);
            f[t1] = t2;
            cnt++;
            q[u].push_back(make_pair(v,w));
            q[v].push_back(make_pair(u,w));

        }
        if(cnt == n-1)
            break;
    }
    // cout << cnt <<endl;
    return ans;
}
int n;
double ans;
ll dfs(int now)
{
    vis[now] = 1;
    ll t = 0,ta = 0;
    for(int i = 0; i < q[now].size(); i++)
    {
        ll v = q[now][i].first;
        ll w = q[now][i].second;
        if(!vis[v])
        {
            t = dfs(v);
            ta += t;
            ans = ans+1.0*t*(n-t)*w;
        }
    }
    return ta+1;
}

int main()
{
    int T,a,c,b;
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        int m;
        ll tans;
        tot = 0,ans = 0;
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&m);

        for(int i =0; i <= n; i++)
            q[i].clear();
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
        }
        if(!n || !m)
        {
            printf("0 0.00\n");
            continue;
        }
        tans = cal(n);
        dfs(1);
        double t = (1.0*n*(n-1)/2);
//        cout <<ans <<" " <<t<<endl;
        printf("%I64d %.2f\n",tans,ans/t);
    }
    return 0;
}

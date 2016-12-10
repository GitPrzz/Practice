/*
hdu 5016 点分治(2014 ACM/ICPC Asia Regional Xi'an Online)

problem:
有n个城市,有的城市有集市. 城市会选择离他最近,编号最小的集市.  如果再建一个集市,那么最多有多少个城市会来这

solve:
如果 城市v的人要到新的集市u 那么dis(u,v) < dis(v,z).(z为原先离v最近的集市)
所以可以先用最短路求出所有城市的最近集市的距离和编号.
如果用dis表示到根节点的距离,那么 dis[u] + dis[v] < spfa(v,z) ---->  dis[u] < dis[v]-spfa(v,z)
所以就成了：求对u而言满足这个公式的点的个数.

hhh-2016-08-24 16:17:48
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
int head[maxn];
int n,k,s[maxn],f[maxn],root,is[maxn];
int Size,tot,u,v,w;
bool vis[maxn];
ll ans[maxn];
ll finans = 0;
ll val;
struct node
{
    int to,w;
    int next;
} edge[maxn << 2];

void ini()
{
    clr(head,-1);
    clr(s,0),clr(ans,0);
    tot = 0;
}


void add_edge(int u,int v,int w)
{
    edge[tot].to = v,edge[tot].w = w,edge[tot].next = head[u],head[u] = tot++;
}
pair<int,int> tp[maxn];

void spfa()
{
    memset(vis,0,sizeof(vis));
    queue<int>q;
    for(int i =1; i <= n; i++)
    {
        if(is[i])
        {
            tp[i] = make_pair(0,i);
            vis[i] = 1;
            q.push(i);
        }
        else
        {
            tp[i] = make_pair(inf,i);
        }
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for(int i = head[u]; ~i ; i = edge[i].next)
        {
            int v = edge[i].to;
            if(tp[v].first > tp[u].first + edge[i].w)
            {
                tp[v].first = tp[u].first + edge[i].w;
                tp[v].second = tp[u].second;
                if(!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

void get_root(int now,int fa)
{
    int v;
    s[now] = 1,f[now] = 0;
    for(int i = head[now]; ~i; i = edge[i].next)
    {
        if((v=edge[i].to) == fa || vis[v])
            continue;
        get_root(v,now);
        s[now] += s[v];
        f[now] = max(f[now],s[v]);
    }
    f[now] = max(f[now],Size-s[now]);
    if(f[now] < f[root]) root = now;
}
int num;
int seq[maxn];
int d[maxn];
void dfs(int now,int fa)
{
    int v;
    seq[num++] = now;
    s[now] = 1;

    for(int i = head[now]; ~i; i = edge[i].next)
    {
//        cout << edge[i].to << " " <<vis[edge[i].to]<<" " << fa <<endl;
        if( (v=edge[i].to) == fa || vis[v])
            continue;
        d[v] = d[now] + edge[i].w;
        dfs(v,now);
        s[now] += s[v];
    }
}
pair<int,int>t[maxn];
void cal(int now,int ob)
{
    num = 0;
    d[now] = ob;
    dfs(now,0);
//    cout <<"root:" << now <<endl;
    for(int i=0; i < num; i++)
    {
//        cout << tp[seq[i]].first-d[seq[i]] << " ";
        t[i] = make_pair(tp[seq[i]].first-d[seq[i]],tp[seq[i]].second);
    }
//    cout <<endl;
//    for(int i = 0;i < num ;i++)
//    {
//        cout << d[seq[i]] << " ";
//    }
//    cout <<endl;
    sort(t,t+num);

    for(int i = 0; i < num; i++)
    {
        if(is[seq[i]])
            continue;
        pair<int,int> temp = make_pair(d[seq[i]],seq[i]);
        int pos = lower_bound(t,t+num,temp)-t;
//        cout << num <<" " <<pos <<endl;
        if(!ob)
        ans[seq[i]] += (ll)(num - pos);
        else
            ans[seq[i]] += (ll)(pos - num);
    }
}

void make_ans(int now,int cnt)
{
    int v ;
    f[0] = Size = cnt;
    get_root(now,root = 0);

    cal(root,0);
    vis[root] = 1;
    for(int i = head[root]; ~i ; i = edge[i].next)
    {
        if( vis[v = edge[i].to] )
            continue;
        cal(v,edge[i].w);
        make_ans(v,s[v]);
    }
}

int main()
{
//    freopen("in.txt","r",stdin);
    while( scanfi(n) != EOF)
    {
        ini();
        finans = 0;
        for(int i = 1; i < n; i++)
        {
            scanfi(u),scanfi(v),scanfi(w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        for(int i =1; i<= n; i++)
            scanfi(is[i]);
        spfa();
//        for(int i = 1;i <= n;i++)
//        {
//            printf("%d %d\n",tp[i].first,tp[i].second);
//        }
        memset(vis,0,sizeof(vis));
        make_ans(1,n);
        for(int i = 1;i <=n;i++)
        {
            finans = max(finans,ans[i]);
        }
//        cout <<"ans";
        printf("%I64d\n",finans);
    }
    return 0;
}

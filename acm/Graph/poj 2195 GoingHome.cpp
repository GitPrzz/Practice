/*
poj 2195 GoingHome

给你一个小地图,上面有一些小人和一些房子,一个房子能同时保存所有的小人。求最小的花费是这些小
人全部进入房子中。

将所有的小人和房子看成点。然后给所有的小人一个超级源点，所有的房子一个超级汇点.求 源点到
汇点的最小费用。  花费为小人到房子的距离。

hhh-2016-06-05 10:11:30
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
const int maxn = 50050;
typedef long long ll;
const ll mod = 10;
const int INF = 0x3f3f3f3f;
struct node
{
    int to,next;
    int cap,flow;
    int cost;
} edge[maxn];

int head[maxn],dis[maxn];
int pre[maxn],tot;
int vis[maxn];
int N;

void ini()
{
    N = 0;
    tot = 0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,int cap,int cost)
{
    edge[tot].to = v;
    edge[tot].cap = cap;
    edge[tot].flow = 0;
    edge[tot].next = head[u];
    edge[tot].cost = cost;
    head[u] = tot ++ ;

    edge[tot].to = u;
    edge[tot].cost = -cost;
    edge[tot].cap = 0;
    edge[tot].flow = 0;
    edge[tot].next = head[v];
    head[v] = tot ++ ;
}


bool spfa(int s,int t)
{
    queue<int>q;
    for(int i = 0; i <= N; i++)
    {
        vis[i] = false,pre[i] = -1;
        dis[i] = INF;
    }
    dis[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i!= -1; i = edge[i].next)
        {
            int v = edge[i].to;
            if(edge[i].cap > edge[i].flow && dis[v] > dis[u] + edge[i].cost)
            {
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    if(pre[t] == -1)
        return false;
    else
        return true;
}

int Maxflow(int s,int t,int &cost)
{
    int flow = 0;
    cost = 0;
    while(spfa(s,t))
    {
        int Min = INF;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            if(Min > edge[i].cap - edge[i].flow)
                Min = edge[i].cap - edge[i].flow;
        }
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to])
        {
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost*Min;
        }
        flow += Min;
    }
    return flow;
}

struct Node
{
    int x,y;
    int id;
};

Node Man[maxn];
Node House[maxn];
int num1,num2;
char str[maxn];
int main()
{
    int n,m;
    int ans;
    while(scanf("%d%d",&n,&m) != EOF && n && m)
    {
        ini();
        num1 = num2 = 0;
        for(int i =0 ;i < n;i++)
        {
            scanf("%s",str);
            for(int j = 0;j < m;j++)
            {
                if(str[j] == 'm')
                {
                    Man[num1].x = i;
                    Man[num1].y = j;
                    Man[num1].id = ++N;
                    num1 ++;
                }
                if(str[j] == 'H')
                {
                    House[num2].x = i;
                    House[num2].y = j;
                    House[num2].id = ++ N;
                    num2++;
                }
            }
        }
        int s = 0;
        int t = ++N;
        for(int i = 0;i < num1;i++)
            addedge(s,Man[i].id,1,0);


        for(int i = 0;i < num2;i++)
            addedge(House[i].id,t,1,0);
        for(int i = 0;i < num1;i++)
        {
            for(int j = 0;j < num2;j++)
            {
                int cs = abs(Man[i].x-House[j].x)+abs(Man[i].y-House[j].y);
                addedge(Man[i].id,House[j].id,1,cs);
            }
        }
        Maxflow(s,t,ans);
        printf("%d\n",ans);
    }
    return 0;
}

/*
poj2516 Minimum Cost

��N����Ӧ�̣�M���꣬K����Ʒ��ÿ����Ӧ�̶�ÿ����Ʒ�ĵĹ�Ӧ����֪��ÿ�����ÿ����Ʒ��
��������֪���Ӳ�ͬ�Ĺ�Ӧ�����Ͳ�ͬ�Ļ��ﵽ��ͬ�ĵ���������Ҫ��ͬ�Ļ��ѣ�����֪�ӹ�Ӧ��
�͵�k�ֻ���ĵ�λ������ĳ����������ĵ�λ���ѡ�

����Դ��ͻ��,Ȼ���ÿһ�ֻ�����һ�η�������ͨ������������ܹ��ж��Ƿ��ܹ���������,Ȼ��
������ú͡�
�ʼ�õ����ڽ���������ʱ,������ˢ��ͼ�ܷ�ʱ�䡣Ȼ��ȥŪ�˸��ڽӾ����AC

hhh-2016-06-05 13:16:21
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
const int maxn=200;
const int INF=0x3fffffff;
int cap[maxn][maxn];
int flow[maxn][maxn];
int cost[maxn][maxn];


int N;
int f;
int c;
int s,t;

bool vis[maxn];
int que[maxn];
int pre[maxn];
int dist[maxn];
bool SPFA()
{
    int Front=0,rear=0;
    for(int u=0; u<=N; u++)
    {
        if(u==s)
        {
            que[rear++]=u;
            dist[u]=0;
            vis[u]=true;
        }
        else
        {
            dist[u]=INF;
            vis[u]=false;
        }
    }
    while(Front!=rear)
    {
        int u=que[Front++];
        vis[u]=false;
        if(Front>=maxn)Front=0;
        for(int v=0; v<=N; v++)
        {
            if(cap[u][v]>flow[u][v]&&dist[v]>dist[u]+cost[u][v])
            {
                dist[v]=dist[u]+cost[u][v];
                pre[v]=u;
                if(!vis[v])
                {
                    vis[v]=true;
                    que[rear++]=v;
                    if(rear>=maxn)rear=0;
                }
            }
        }
    }
    if(dist[t]>=INF)return false;
    return true;
}

void minCostMaxflow()
{
    memset(flow,0,sizeof(flow));
    c=f=0;
    while(SPFA())
    {
        int Min=INF;
        for(int u=t; u!=s; u=pre[u])
            Min=min(Min,cap[pre[u]][u]-flow[pre[u]][u]);
        for(int u=t; u!=s; u=pre[u])
        {
            flow[pre[u]][u]+=Min;
            flow[u][pre[u]]-=Min;
        }
        c+=dist[t]*Min;
        f+=Min;
    }
}

struct Node
{
    int x,y;
    int id;
};

int sup[maxn][maxn];
int store[maxn][maxn];
int alsup[maxn],alstore[maxn];
int n,m,k;
int main()
{
    while(scanf("%d%d%d",&n,&m,&k) != EOF && n && m && k)
    {
        s = 0;
        t = n + m + 1;
        N = t;
        memset(cost,0,sizeof(cost ));
        memset(cap,0,sizeof(cap));
        for(int i =0 ; i < n; i++)
        {
            for(int j = 0; j < k; j++)
                scanf("%d",&sup[i][j]);
        }
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < k; j++)
                scanf("%d",&store[i][j]);
        }
        for(int t = 0; t <k; t++)
        {
            alsup[t] = 0;
            for(int i = 0; i < n; i++)
                alsup[t] += sup[i][t];
        }
        int tans = 0;
        int flag = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = n + 1; j<= m+n; j++)
                cap[i][j] = INF;
        }
        for(int now = 0; now < k; now++)
        {
            for(int i = 1; i <= n; i++)
                cap[s][i] = sup[i-1][now];
            for(int i = 1; i <= m; i++)
                cap[i+n][t] = store[i-1][now];
            for(int i = 1; i <= n; i++)
            {
                for(int j = 1; j <= m; j++)
                {
                    scanf("%d",&cost[i][j+n]);
                    cost[j+n][i] = -cost[i][j+n];
                }
            }
            minCostMaxflow();
            if(flag)
                continue;
           // cout << f << endl;
            if(f != alsup[now] )
                flag = 1;
            else
                tans += c;
        }
        if(flag)
            printf("-1\n");
        else
            printf("%d\n",tans);
    }
    return 0;
}

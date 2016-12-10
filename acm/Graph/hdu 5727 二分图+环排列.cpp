/*
hdu 5727 ����ͼ+������

problem:
Ҫ�ã����ʯ�ͣ����ʯ����һ����������״�����涨��ʯ�Ա�ֻ������ʯ����ʯ��ֻ������ʯ�������У����������ʯ��
��Щ����ʯ���ڻ�ʹ����ʯ�����ϣ����������ã����ʴ���������������м������ϵ���ʯ��

solve:
�ʼһ����͸о�Ӧ���Ƕ���ƥ��,������������ʯ�������ʯÿ��λ��Ҫ�����������ߵ����
���Կ���ö����ʯ���������.Ȼ���ÿ����λ��������ʯ֮�佨ͼ����������Է���ʯ����Ϊ1,Ȼ���ܸ����ƥ��ó�cnt
��ôn-cnt���ǵ�ǰ������ٵĹ�����

ö��������õ�ϵͳ�Դ���next_permutation,����һֱ��ʱ.�������������ŷ��ֻ�����ֻ��Ҫ(n-1)!.���Կ��Թ̶�һ��
λ�õ�ֵ,ö��ʣ�µļ���

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

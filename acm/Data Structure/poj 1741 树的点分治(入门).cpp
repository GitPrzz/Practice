/*
poj 1741 ���ĵ����(����)

problem:
��һ�ñߴ�Ȩ����������֮��ľ���С�ڵ���K�ĵ���ж��ٸ�

solve:
����˼·,�Ե�ǰ������������Ϊ���ڵ�,Ȼ���ҳ����е㵽���ڵ�ľ���. Ȼ����ܼ�����ж��ٵĵĺ�
<= k. �������������п�������ͬһ������,�����ں�������м�ȥ,���ܼ��������ǰ���ڵ�����ж�.
��ͬ���ķ����������������,������ȥ����.
������Ϊ������������Ľڵ�����С,�Ӷ�����Ч��.
(�������)
hhh-2016-08-22 20:00:18
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
#define inf 0x3FFFFFFFFFFFFFFFLL
using namespace std;
const int maxn = 100010;

struct node
{
    int to,w;
    node() {};
    node(int v,int _w):to(v),w(_w) {};
};

vector<node> q[maxn];
int n,k,s[maxn],f[maxn],root,d[maxn],ans,limit;
int Size;
bool vis[maxn];
vector<int> ta;

void get_root(int now,int fa)
{
    int v;
    s[now] = 1,f[now] = 0;
    for(int i = 0;i < q[now].size();i++)
    {
        if( (v=q[now][i].to) == fa || vis[v])
            continue;
        get_root(v,now);
        s[now] += s[v];
        f[now] = max(f[now],s[v]);
    }
    f[now] = max(f[now],Size - s[now]);
    if(f[now] < f[root]) root = now;
}

void dfs(int now,int fa)
{
    int v;
    ta.push_back(d[now]);
    s[now] = 1;
    for(int i = 0;i < q[now].size();i++)
    {
        if( (v=q[now][i].to) == fa || vis[v])
            continue;
        d[v] = d[now] + q[now][i].w;
        dfs(v,now);
        s[now] += s[v];
    }
}

int cal(int now,int begi)
{
    ta.clear(),d[now] = begi;
    dfs(now,0);
    sort(ta.begin(),ta.end());
    int cnt = 0;
    for(int l = 0,r=ta.size()-1;l<r;)
    {
        if(ta[l] + ta[r] <= limit) cnt += (r-l++);
        else r --;
    }
    return cnt;
}

void work(int now)
{
    int v;
    ans += cal(now,0);
    vis[now] = 1;
    for(int i = 0;i < q[now].size(); i++)
    {
        if(!vis[v = q[now][i].to])
        {
            ans -= cal(v,q[now][i].w);
            f[0] = Size = s[v];
            get_root(v,root = 0);
            work(root);
        }
    }
}

int main()
{
    while(scanf("%d%d",&n,&limit) == 2)
    {
        if(!n && !limit)
            break;
        for(int i = 0;i <= n;i++) q[i].clear();
        memset(vis,0,sizeof(vis));

        int a,b,c;
        for(int i = 1;i < n;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            q[a].push_back(node(b,c));
            q[b].push_back(node(a,c));
        }
        f[0] = Size = n;
        get_root(1,root = 0);
        ans = 0;
        work(root);
        printf("%d\n",ans);
    }
    return 0;
}

/*
hdu 4812 DTree (点分治)

problem:
求最小的点对使 u->v的点权的乘积%mod=limit.

solve:
每次求过当前树根节点的情况. 每次可以计算出 一点到当前根节点的情况temp,所以只需要找出其它子树中是否有limit/temp
因为有取余,所以先预处理出所有的逆元.

hhh-2016-08-23 10:52:26
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
#define mod 1000003
using namespace std;
const int maxn = 100010;
ll val[maxn],d[maxn],limit;
int head[maxn];
int n,k,s[maxn],f[maxn],root;
int Size,tot;
bool vis[maxn];
vector<ll> ta;

struct node
{
    int to,w,next;
}edge[maxn<<2];

void add_edge(int u,int v)
{
    edge[tot].to=v,edge[tot].next=head[u],head[u]=tot++;
}

void get_root(int now,int fa)
{
    int v;
    s[now] = 1,f[now] = 0;
    for(int i = head[now];~i;i = edge[i].next)
    {
        if( (v=edge[i].to) == fa || vis[v])
            continue;
        get_root(v,now);
        s[now] += s[v];
        f[now] = max(f[now],s[v]);
    }
    f[now] = max(f[now],Size - s[now]);
    if(f[now] < f[root]) root = now;
}
int id[maxn];
int idnum;
void dfs(int now,int fa)
{
    int v;
    ta.push_back(d[now]);
    id[idnum++] = now;
    s[now] = 1;
    for(int i = head[now];~i;i = edge[i].next)
    {
        if( (v=edge[i].to) == fa || vis[v])
            continue;
        d[v] =  (d[now] * val[v])%mod;
        dfs(v,now);
        s[now] += s[v];
    }
}
int flag[mod + 10];
int mp[mod + 10];
int cur = 0;
ll ni[mod+10];
int ans[2];
void to_ans(int a, int b)
{

    if (a > b) swap(a,b);
    if (ans[0] == -1 || ans[0] > a) ans[0] = a, ans[1] = b;
    else if (ans[0] == a && ans[1] > b) ans[1] = b;
//    cout <<"a:"<<ans[0] << " b:" <<ans[1] <<endl;
}

void work(int now,int cnt)
{
    f[0] = Size = cnt;
    get_root(now,root = 0);
    int v;
    vis[root] = 1;
    for(int i = head[root];~i;i = edge[i].next)
    {
        if(!vis[v = edge[i].to])
        {
            ta.clear(),d[v] = val[v],idnum = 0;
            dfs(v,0);

            for(int j = 0; j < ta.size();j++)
            {
                if(val[root]*ta[j] % mod == limit && root != id[j])
                    to_ans(root,id[j]);
                ll t = (ll)limit*ni[val[root]*ta[j]%mod]%mod;
                if(flag[t] != cur)
                    continue;
                if(mp[t] == id[j])
                    continue;
                to_ans(mp[t],id[j]);
            }
            for(int j = 0; j < ta.size(); j++)
            {
                int t = ta[j];
                if(flag[t] != cur || mp[t] > id[j]) mp[t] = id[j],flag[t] = cur;
            }
        }
    }
    cur ++;
    for(int i = head[root];~i;i = edge[i].next)
    {
        if(vis[edge[i].to])
            continue;
        work(edge[i].to,s[edge[i].to]);
    }
}

ll egcd(ll a,ll b, ll &x, ll &y)
{
    ll temp,tempx;
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    temp = egcd(b,a % b, x, y);
    tempx = x;
    x = y;
    y = tempx - a / b * y;
    return temp;
}

int main()
{

    ll y;
    for (int i = 0; i < mod; i++)
    {
        egcd(i*1ll, mod*1ll, ni[i], y);
        ni[i] %= mod, ni[i] = (ni[i]+mod)%mod;
    }
    while(scanf("%d%I64d",&n,&limit)!=EOF)
    {
        if(!n && !limit)
            break;
        clr(vis,0),clr(flag,0);
        clr(head,-1),tot = 0;
        ans[0] = ans[1] = -1;
        int a,b;
        for(int i = 1; i <= n; i++)
        {
            scanf("%I64d",&val[i]);
        }
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);
        }
        cur = 1;
        work(1,n);
        if(ans[0] == -1)
            printf("No solution\n");
        else
            printf("%d %d\n",ans[0],ans[1]);
    }
    return 0;
}

hdu 4670 Cube number on a tree（点分治）

problem:
在一棵树上，求多少条路径的点权值积为立方数

solve:
和普通的求积为k的点对数很像.因为权值有10^15,所以用质因子来记录每个树的权值. 然后就是状态保存,因为当你知道当前子树的一条链时
,需要查找其它子树(同一根)是否有链与其对应使积为立方数. 质因子总共有30位,所以可以用一个longlong来记录状态,用map保存
(递归所有重心,每次计算当前重心的所有情况)

hhh-2016-08-24 09:42:56
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
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3FFFFFFFFFFFFFFFLL
#define mod 1000003
using namespace std;
const ll xo = (1LL << 61)-1;
const int maxn = 50010;
int head[maxn];
int n,k,s[maxn],f[maxn],root;
int Size,tot;
bool vis[maxn];
ll factor[maxn][31],d[maxn][31],fac[31];
int facnt;
int id[maxn];
ll val;
struct node
{
    int to;
    int next;
} edge[maxn << 2];

void ini()
{
    clr(factor,0);
    clr(head,-1),clr(vis,0);
    clr(s,0);
    tot = 0;
}


void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u],head[u] = tot++;
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
map<ll,ll> mp;
ll make_hash(ll q[])
{
    ll t = 0;

    for(int i = 0; i < facnt; i++)
    {
        t = t*3LL + q[i];
    }

    return t;
}

void dfs(int now,int fa)
{
    int v;
    id[num++] = now;
    s[now] = 1;

    for(int i = head[now]; ~i; i = edge[i].next)
    {
        if( (v=edge[i].to) == fa || vis[v])
            continue;
        for(int j = 0; j < facnt; j++)
        {
            d[v][j] = (factor[v][j]+d[now][j])%3;
        }
        dfs(v,now);
        s[now] += s[v];
    }
}
ll ans = 0;
ll tp[31];
void Debug(ll t)
{
    for(int i = 30; i >= 0; i--)
    {
        if(t & (1 << i))
            printf("1");
        else
            printf("0");
    }
    cout << endl;
}
void make_ans(int now,int cnt)
{
    int v ;
    f[0] = Size = cnt;
    get_root(now,root = 0);
    vis[root] = 1;
    mp.clear();
    ll ts = make_hash(factor[root]);
    if(ts == 0)
        ans ++;

    for(int i = head[root]; ~i; i = edge[i].next)
    {
        if(vis[v = edge[i].to])
            continue;
        num = 0;
        for(int j = 0; j < facnt; j++)
            d[v][j] = factor[v][j];
        dfs(v,root);


        for(int j = 0; j < num; j++)
        {
            for(int t = 0; t < facnt; t++)
            {
                tp[t] = (d[id[j]][t] + factor[root][t])%3;
            }
            ll ta = make_hash(tp);

            if(ta == 0)
            {
                ans ++;
            }

            ta  = 0;
            for(int t = 0; t < facnt; t++)
                ta = ta*3LL + (3LL-tp[t])%3;
            if(mp[ta] > 0)
            {
                ans += mp[ta];
            }
        }
        for(int j = 0; j < num; j++)
        {
            ll ta = make_hash(d[id[j]]);
            if(mp[ta] == -1)
                mp[ta] = 0;
            mp[ta] ++;
        }
    }
    for(int i = head[root]; ~i; i = edge[i].next)
    {
        if(vis[v = edge[i].to])
            continue;
        make_ans(v,s[v]);
    }
}
void make_fac(int u,ll cur)
{
    ll t = cur;
    for(int i = 0; i < facnt; i++)
    {
        while(t % fac[i] == 0)
        {
            t /= fac[i];
            factor[u][i]++;
        }
        factor[u][i] %= 3;
    }
}

int main()
{
    int n,u,v;
//    freopen("in.txt","r",stdin);
    while( scanfi(n) != EOF)
    {
        ini();
        scanfi(facnt);
        for(int i = 0; i < facnt; i++)
            scanfl(fac[i]);
        for(int i = 1; i<= n; i++)
        {
            scanfl(val);
            make_fac(i,val);

        }
        for(int i = 1; i < n; i++)
        {
            scanfi(u),scanfi(v);
            add_edge(u,v);
            add_edge(v,u);
        }
        ans =0;
        make_ans(1,n);
        printf("%I64d\n",ans);
    }
    return 0;
}

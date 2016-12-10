/*
hdu 5893 (树链剖分+合并)

problem:
1.update:将a->b的边权设置为c
2.query:求a->b的连续边权的个数
222333 -> 2    22112->3

solve：
主要是查询的意思不是很懂. how many different kinds of continuous same cost
以为不同还要分长度,数值大小什么的。 于是没怎么想
结果后来发现是求区间中有多少个连续的子区间 - -. 感觉很僵
update直接用一个标记解决
query的时候, 维护区间左右端点的值以合并区间,合并的时候注意维护子区间的数量
而且树链剖分时 在合并链的时候也要进行判断什么的.
update的u == v的时候最好判断一下, 否则查询son[u] -> v会有问题
我们只有一个重链,可能有很多的轻链,query的 u == v时就是轻链合并的情况.
总体都是线段树的思路

hhh-2016-09-19 22:36:11
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 200100;
const int inf = 0x3f3f3f3f;
int head[maxn],tot,pos,son[maxn];
int top[maxn],fp[maxn],fa[maxn],dep[maxn],num[maxn],p[maxn];
int n;
int a[maxn];
struct Edge
{
    int to,next;
    int w;
} edge[maxn<<2];

void ini()
{
    tot = 0,pos = 1;
    clr(head,-1),clr(son,-1);
    clr(a,0);
}

void add_edge(int u,int v,int w)
{
    edge[tot].to = v,edge[tot].next = head[u],edge[tot].w = w,head[u] = tot++;
}

void dfs1(int u,int pre,int d)
{
//    cout << u << " " <<pre <<" " <<d <<endl;
    dep[u] = d;
    fa[u] = pre,num[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v != pre)
        {
            a[v] = edge[i].w;
            dfs1(v,u,d+1);
            num[u] += num[v];
            if(son[u] == -1 || num[v] > num[son[u]])
                son[u] = v;
        }
    }
}

void getpos(int u,int sp)
{
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1)return ;
    getpos(son[u],sp);
    for(int i = head[u]; ~i ; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
            getpos(v,v);
    }
}

struct node
{
    int l,r,mid;
    int ls,rs,same;
    ll num ;
} tree[maxn << 2];

void push_up(int i)
{

    if(tree[lson].rs == tree[rson].ls )
    {
        tree[i].num = tree[lson].num + tree[rson].num -1;
    }
    else
        tree[i].num =tree[lson].num + tree[rson].num;
    tree[i].ls = tree[lson].ls;
    tree[i].rs = tree[rson].rs;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].mid=(l+r) >>1;
    tree[i].same = inf;
    tree[i].num = tree[i].ls = tree[i].rs = 0;
    if(l == r)
    {
        tree[i].ls = tree[i].rs = a[fp[l]];
        tree[i].num = 1;
//        cout << fp[l]  <<" " << a[fp[l]] <<endl;
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
    push_up(i);
}
void make_same(int i,int val)
{
    tree[i].same = val;
    tree[i].num = 1;
    tree[i].ls = tree[i].rs = val;
}
void push_down(int i)
{
    if(tree[i].same != inf)
    {
        make_same(lson,tree[i].same);
        make_same(rson,tree[i].same);
        tree[i].same = inf;
    }
}


void update_area(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].same = val;
        tree[i].num = 1;
        tree[i].ls = tree[i].rs = val;
        return ;
    }
    push_down(i);
    int mid = tree[i].mid;
    if(l <= mid)
        update_area(lson,l,r,val);
    if(r > mid)
        update_area(rson,l,r,val);
    push_up(i);
}

ll query(int i,int l,int r,int &tls,int &trs)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tree[i].l == l)
            tls = tree[i].ls;
        if(tree[i].r == r)
            trs = tree[i].rs;
        return tree[i].num ;
    }
    push_down(i);
    int mid = tree[i].mid ;
    ll ans = 0;
    if(r <= mid)
        ans = query(lson,l,r,tls,trs);
    else if(l > mid)
        ans = query(rson,l,r,tls,trs);
    else
    {
        int tls1,tls2,trs1,trs2;
        ll t1 = query(lson,l,mid,tls1,trs1);
        ll t2 = query(rson,mid+1,r,tls2,trs2);
        ans = t1 + t2;
        if(tree[lson].rs == tree[rson].ls)
        {
            ans --;
        }
        tls = tls1,trs = trs2;
    }
    push_up(i);
    return ans;
}

void update_same(int u,int v,int val)
{
    int f1 = top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        update_area(1,p[f1],p[u],val);
        u = fa[f1],f1 = top[u];
    }
    if(u == v)
    return ;
    if(dep[u] > dep[v]) swap(u,v);
    update_area(1,p[son[u]],p[v],val);
}

ll query_dif(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    int ls1,rs1,ls2,rs2;
    ls1 = rs1 = ls2 = rs2 = inf;
    int tls1,trs1,tls2,trs2;
    int fi1 = 1,fi2 = 1;
    ll ans = 0;
    while(f1 != f2)
    {
        if(dep[f1] > dep[f2])
        {
            ans += query(1,p[f1],p[u],tls1,trs1);
            if(trs1 == ls1)
                ans--;
            ls1 = tls1;
            if(fi1)
            {
                rs1 = trs1;
                fi1 = 0;
            }
            u = fa[f1],f1 = top[u];
        }
        else
        {
            ans += query(1,p[f2],p[v],tls2,trs2);
            if(trs2 == ls2)
                ans--;
            ls2 = tls2;
            if(fi2)
            {
                rs2 = trs2;
                fi2 = 0;
            }
            v = fa[f2],f2 = top[v];
        }
    }
    if(u == v)
    {
        if(tls1 == tls2)
        ans --;
        return ans;
    }
    if(dep[u] > dep[v])
    {
        ans += query(1,p[son[v]],p[u],tls1,trs1);
        if(trs1 == ls1)
            ans--;
        if(tls1 == ls2)
            ans --;
    }
    else
    {
        ans += query(1,p[son[u]],p[v],tls2,trs2);
        if(trs2 == ls2)
            ans--;
        if(tls2 == ls1)
            ans--;
    }
    return ans;
}
char str[10];
int main()
{
//    freopen("in.txt","r",stdin);
    int a,b,c;
    int m,u,v,w;
    while(scanf("%d%d",&n,&m) != EOF)
    {
        ini();
        for(int i =1; i <n; i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        dfs1(1,0,0);
        getpos(1,1);
        build(1,1,pos-1);
//        cout << pos -1 <<endl;
        for(int i = 1; i <= m; i++)
        {
            scanf("%s",str);
            scanf("%d%d",&a,&b);
            if(str[0] == 'C')
            {
                scanf("%d",&c);
                update_same(a,b,c);
            }
            else
            {
                if(a == b)
                    printf("0\n");
                else
                    printf("%I64d\n",query_dif(a,b));
            }
        }
    }
    return 0;
}

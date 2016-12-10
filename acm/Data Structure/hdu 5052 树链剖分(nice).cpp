/*
hdu 5052 树链剖分(nice)

problem:
给你一个树,每次找出u->v上面的最大差值(较小值必需在较大值前面).找出后在给路径所有点加上w

solve:
首先是线段树维护差值的问题,在这里错了很久- -. 按照以前的写习惯了,并没想区间合并时候的问题...
树链剖分查找的时候,每次只能查找一条链,所以在这里也要合并(右边链Max - 左边链Min).
而且u->v的话,因为u到(u,v)的lca的节点号是逆序的(根节点较小),所以线段树要维护 左到右and右到左的差值

hhh-2016-08-22 10:53:40
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
#define inf 0x3FFFFFFFFFFFFFFFLL
using namespace std;
const int maxn = 200100;
int head[maxn],tot,pos,son[maxn];
int top[maxn],fp[maxn],fa[maxn],dep[maxn],num[maxn],p[maxn];
int n;
ll a[maxn];

ll MAX(ll a,ll b)
{
    return a>b?a:b;
}
ll MIN(ll a,ll b)
{
    return a>b?b:a;
}
struct Edge
{
    int to,next;
} edge[maxn<<2];

void ini()
{
    tot = 0,pos = 1;
    clr(head,-1),clr(son,-1);
}

void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u],head[u] = tot++;
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
    ll Max,Min;
    ll lans,rans;
    ll add;
} tree[maxn << 2];

void push_up(int i)
{
    tree[i].Max = MAX(tree[lson].Max,tree[rson].Max);
    tree[i].Min = MIN(tree[lson].Min,tree[rson].Min);
    tree[i].rans = MAX(tree[rson].Max - tree[lson].Min,MAX(tree[lson].rans,tree[rson].rans));
    tree[i].lans = MAX(tree[lson].Max - tree[rson].Min,MAX(tree[lson].lans,tree[rson].lans));
    if(tree[i].lans < 0) tree[i].lans = 0;
    if(tree[i].rans < 0) tree[i].rans = 0;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].mid=(l+r) >>1;
    tree[i].add = 0;
    tree[i].Max = 0,tree[i].Min = inf;
    tree[i].lans = 0,tree[i].rans = 0;
    if(l == r)
    {
        tree[i].Max = tree[i].Min = a[fp[l]];
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
    push_up(i);
}
void update(int i,ll d)
{
    tree[i].Max += d,tree[i].Min += d;
    tree[i].add += d;
}

void push_down(int i)
{
    if(tree[i].add)
    {
        update(lson,tree[i].add),update(rson,tree[i].add);
        tree[i].add = 0;
    }
}

void update_area(int i,int l,int r,ll val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        update(i,val);
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


ll query(int i,int l,int r,int flag,ll& MaxPrice,ll& MinPrice)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        MinPrice = tree[i].Min;
        MaxPrice = tree[i].Max;
        if(flag)
        {

            return tree[i].rans;
        }
        else
        {
            return tree[i].lans;
        }
    }
    push_down(i);
    int mid = tree[i].mid;
    if(r <= mid)
        return MAX(0LL,query(lson,l,r,flag,MaxPrice,MinPrice));
    else if(l > mid)
        return MAX(0LL,query(rson,l,r,flag,MaxPrice,MinPrice));
    else
    {
        ll ta = 0;
        ll max1,max2,min1,min2;
        ll ans = MAX(query(lson,l,mid,flag,max1,min1),query(rson,mid+1,r,flag,max2,min2));
        if(flag)
            ta = max2 - min1;
        else
            ta = max1 - min2;
        MaxPrice = MAX(max1,max2);
        MinPrice = MIN(min1,min2);
        ta = MAX(ta,0LL);
        return MAX(ans,ta);
    }
    push_up(i);
}

void make_add(int u,int v,ll val)
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
    if(dep[u] > dep[v])
        swap(u,v);
    update_area(1,p[u],p[v],val);
    return ;
}

ll make_query(int u,int v)
{
    ll tmin,tmax,tMin,tMax;
    ll cmin,cmax,cMin,cMax;
    tMin = tmin = tree[1].Max;
    tMax = tmax =  0;
    ll cnt = 0;
    int f1 = top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] > dep[f2])
        {
//            cout << p[f1] <<" "<<p[u] <<endl;
            cnt = MAX(cnt,query(1,p[f1],p[u],0,cmax,cmin));
            cnt = MAX(cnt,cmax - tmin);
            cnt = MAX(cnt,tMax - cmin);
            tmin = MIN(cmin,tmin);
            tmax = MAX(cmax,tmax);
            u = fa[f1],f1 = top[u];
            //  tmax = max(tmax,cmax);
        }
        else
        {
//             cout << p[f2] <<" "<<p[v] <<endl;
            cnt = MAX(cnt,query(1,p[f2],p[v],1,cMax,cMin));
            cnt = MAX(cnt,tMax - cMin);
            cnt = MAX(cnt,cMax-tmin);
            tMax = MAX(tMax,cMax);
            tMin = MIN(tMin,cMin);
            v = fa[f2],f2 = top[v];
            // tMin = min(tMin,cMin);
        }
    }
    if(dep[u] > dep[v])
    {
        cnt =MAX(cnt,query(1,p[v],p[u],0,cmax,cmin));
        cnt =MAX(cnt,cmax-tmin);
        tmin = MIN(tmin,cmin);
        cnt = MAX(cnt,tMax-tmin);
    }
    else
    {
        cnt =MAX(cnt,query(1,p[u],p[v],1,cMax,cMin));
//        cout <<"max" <<cMax <<" " <<"min" <<cMin <<endl;
        cnt = MAX(cnt,tMax-cMin);
        tMax = MAX(tMax,cMax);
        cnt = MAX(cnt,tMax-tmin);
    }
    return cnt;
}

/*
5
3 1 1 1
1 2 2 3
3
1 1 500000000
2 1 1
3 1 1
*/
int main()
{
//    freopen("in.txt","r",stdin);
    int T;
    int m,u,v;
    ll w;
    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
            scanf("%I64d",&a[i]);
        for(int i =1; i <n; i++)
        {
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
        }
        dfs1(1,0,0);
        getpos(1,1);
        build(1,1,pos-1);
        scanf("%d",&m);
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d%I64d",&u,&v,&w);
            printf("%I64d\n",make_query(u,v));
            make_add(u,v,w);
        }
    }
    return 0;
}

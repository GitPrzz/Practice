/*
hdu 5458 Stability(树链剖分+并查集)

problem:
给你一个无向图(可能有重边or环). 1.删除a,b之间的边    2.查询a,b的必要边(即删除后a b无法连通)

solve:
最开始想的是建图的时候一直维持一棵树. 如果u,v上面出现环,那么u->v整个链上都可以置为0.因为它们任意两点之间都不可能有必要边
但是后面操作中会删除边,所以不知道树的形状,会导致后面的查询出现问题.

后来考虑倒着操作,先弄出最后操作完的图.本来还担心最后会被切成多个不相连图, 但是
题目：we guarantee the graph would always be connected  保证了操作完后必然是 树或者有环图.
如果是有环图的话可以用过上面的思路转换成树的,最后就成了树链上的操作,所以树链剖分就能做

将所有边记录下来,然后将1操作删除的边除去. 如果最后是有环图(并查集判断)的话,将重复的边记录下,然后建树.
而重复的边会导致 u->v链上面两两没有必要边,于是将置为0.

得出了最后这个树,接着就是倒着操作了
1操作:在u->v上加边 ----> 将u->v整个链上都可以置为0
2操作:查询u->v上的必要边

hhh-2016-08-26 11:06:45
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
#include <set>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3f3f3f3f
using namespace std;
const int maxn = 40010;
const int maxm = 2e5 + 1000;
int head[maxn],tot,pos,son[maxn];
int top[maxn],fp[maxn],fa[maxn],dep[maxn],num[maxn],p[maxn];
int par[maxn];
int n,m,q;
struct Edge
{
    int to,next;
} edge[maxm << 1];
int fin_par(int x)
{
    if(par[x] == -1) return x;
    return par[x] = fin_par(par[x]);
}
void ini()
{
    clr(par,-1);
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
    int same;
    int val;
    int l,r,mid;
} tree[maxn << 2];

void push_up(int i)
{
    tree[i].val = tree[lson].val + tree[rson].val;
}

void build(int i,int l,int r)
{
    tree[i].same = -1;
    tree[i].l = l,tree[i].r = r;
    tree[i].mid=(l+r) >>1;

    if(l == r)
    {
        if(fp[l] == 1)
            tree[i].val = 0;
        else
            tree[i].val = 1;
//        cout << fp[l]<<":" << tree[i].val <<endl;
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].same != -1)
    {
        tree[lson].same = tree[i].same;
        tree[rson].same = tree[i].same;
        tree[lson].val = tree[rson].val = 0;
        tree[i].same = -1;
    }
}

void update_area(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].val= 0;
        tree[i].same=  0;
        return ;
    }
    push_down(i);
    if(l <= tree[i].mid)
        update_area(lson,l,r);
    if(r > tree[i].mid)
        update_area(rson,l,r);
    push_up(i);
    return ;
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].val;
    int tcnt = 0;
    push_down(i);
    if(l <= tree[i].mid)
        tcnt += query(lson,l,r);
    if(r > tree[i].mid)
        tcnt += query(rson,l,r);
    push_up(i);
    return tcnt;
}

void make_update(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])swap(f1,f2),swap(u,v);
        update_area(1,p[f1],p[u]);
        u = fa[f1] , f1 =top[u];
    }
    if(u == v)
        return ;
    if(dep[u] > dep[v])  swap(u,v);
    update_area(1,p[son[u]],p[v]);
}

int make_query(int u,int v)
{
    int ans = 0;
    int f1= top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        ans += query(1,p[f1],p[u]);
//        cout << p[f1] <<" " <<p[u] <<" "<<ans << endl;
        u = fa[f1] , f1 = top[u];
    }
    if(u == v)
        return ans;
    if(dep[u] > dep[v]) swap(u,v);
    ans += query(1,p[son[u]],p[v]);
//    cout << p[u]+1 <<" " <<p[v] <<" "<<ans << endl;
    return ans ;
}

int l[maxm],r[maxm],op[maxm];
int ans[maxm];
struct Point
{
    int l,r;
    Point() {}
    Point(int x,int y):l(x),r(y) {}
    bool operator <(const Point &a)const
    {
        if(l != a.l)
            return l < a.l;
        else
            return r < a.r;
    }
};
multiset<Point> vec;
multiset<Point> another;
multiset<Point>::iterator it;
int main()
{
//    freopen("in.txt","r",stdin);
    int T,u,v,cas = 1;
    scanfi(T);
    while(T--)
    {
        ini();
        vec.clear(),another.clear();
        scanfi(n),scanfi(m),scanfi(q);
        for(int i = 1; i <= m; i++)
        {
            scanfi(u),scanfi(v);
            if(u > v) swap(u,v);
            vec.insert(Point(u,v));
        }
        for(int i = 1; i <= q; i++)
        {
            scanf("%d%d%d",&op[i],&l[i],&r[i]);
            if(op[i] == 1)
            {
                if(l[i] > r[i]) swap(l[i],r[i]);
                vec.erase(vec.lower_bound(Point(l[i],r[i])));
            }
        }
//        cout << vec.size() <<endl;
        for( it = vec.begin(); it != vec.end(); it++)
        {
            Point t = *it;
            u = t.l,v = t.r;
            int tu = fin_par(u),tv = fin_par(v);
//            cout << u <<" " << v << " " << tu << " "  <<tv <<endl;
            if(tu == tv)
            {
                another.insert(Point(u,v));
                continue;
            }
            par[tu] = tv;
            add_edge(u,v);
            add_edge(v,u);
        }
//        cout << another.size() <<endl;
        dfs1(1,0,0);
        getpos(1,1);
        build(1,1,pos-1);
        printf("Case #%d:\n",cas++);
        for( it = another.begin(); it != another.end(); it++)
        {
            Point t = *it;
            u = t.l,v = t.r;
            make_update(u,v);
        }
        int ob = 0;
        for(int i = q; i > 0; i--)
        {
            u = l[i],v = r[i];
//            cout << op[i]<<" "<< u << " " << v <<endl;

            if(op[i] == 2)
            {
                ans[ob++] = make_query(u,v);
            }
            else
            {
                make_update(u,v);
            }
        }
        for(int i = ob-1;i >=0;i--)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}

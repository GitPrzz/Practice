/*
hdu 4897 树链剖分(重轻链)

problem:
给你一棵树,初始每条边为白色,然后是三种操作
1.将u->v链上面的所有边的颜色翻转 (例：white -> black)
  这个在线段树上很好处理,用个翻转标记,然后记录数量即可
2.将u->v链上面所有邻接的边翻转(边上只有一个点在链上面)
3.询问u->v上面有多少黑色的边

solve:
对于1,3操作树链剖分很好解决。但是在操作2上面就GG了.所以去参考了很多博客 - -,很久才明白大致思路

就操作2而言,主要可以看成在一条重链上面的 和 跨越了很多重轻链的那种.
主要是轻链两端连接的是重链,所以在操作2的时候可以考虑直接在每个点上面打标记(除了有的叶子节点,重链基本上
覆盖了所有的点).
所以轻链的颜色就是：  左端点rev2^右端点rev2^边的颜色(边的颜色线段树很好维护的)
如果重链分成很多条边来用也可以实现,但是无疑到达lca的效率为很低,所有需要考虑其他方法

然后就是维护重链上面的颜色,如果u,v在一条重链的中间部分,打标记可以维护对轻链的影响。所以只需要考虑对两端重链
的影响,于是把与两端相邻的边用操作1翻转就好了.在操作2下一条重链最多只需要更新左右两个端点,但是却有很多条
轻链。 所以重链可以直接更新,轻链则需要标记来维护了。

因为没有判断,有时线段树会出现l>r导致RE了很久- -
hhh-2016-08-18 21:18:55
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
    int rev1,rev2;
    int num;
} tree[maxn << 2];

void push_up(int i)
{
    tree[i].num = tree[lson].num + tree[rson].num;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].mid=(l+r) >>1;
    tree[i].rev1 = tree[i].rev2 = 0;
    tree[i].num = 0;
    if(l == r)
    {
//        cout << fp[l] <<" " <<val[fp[l]]<<endl;
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
}

void push_down(int i)
{
    if(tree[i].rev1)
    {
        tree[i].rev1 = 0;
        tree[lson].rev1 ^= 1,tree[lson].num = tree[lson].r-tree[lson].l+1-tree[lson].num;
        tree[rson].rev1 ^= 1,tree[rson].num = tree[rson].r-tree[rson].l+1-tree[rson].num;;
    }
    if(tree[i].rev2)
    {
        tree[i].rev2 = 0;
        tree[lson].rev2 ^= 1;
        tree[rson].rev2 ^= 1;
    }
}


void update_area(int i,int l,int r,int flag)
{
//    cout <<"l:"<< l <<" r:"<<r <<" min:"<< tree[i].Min<<endl;
    if(l > r)
        return ;
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(flag == 1)
        {
            tree[i].num = tree[i].r-tree[i].l+1-tree[i].num;
            tree[i].rev1 ^= 1;
        }
        else
            tree[i].rev2 ^= 1;
        return ;
    }
    push_down(i);
    int mid = tree[i].mid;
    if(r <= mid)
        update_area(lson,l,r,flag);
    else if(l > mid)
        update_area(rson,l,r,flag);
    else
    {
        update_area(lson,l,mid,flag);
        update_area(rson,mid+1,r,flag);
    }
    push_up(i);
}

int query(int i,int l,int r,int flag)
{
    if(l > r)
        return 0;
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(flag == 1)
            return tree[i].num;
        else
            return tree[i].rev2;
    }
    push_down(i);
    int mid = tree[i].mid;
    if(r <= mid)
        return query(lson,l,r,flag);
    else if(l > mid)
        return query(rson,l,r,flag);
    else
        return query(lson,l,mid,flag)+query(rson,mid+1,r,flag);
    push_up(i);
}

void update_rev1(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        update_area(1,p[f1],p[u],1);
        u = fa[f1],f1 = top[u];
    }
    if(dep[u] > dep[v]) swap(u,v);
    update_area(1,p[son[u]],p[v],1);
}

void update_rev2(int u,int v)
{
    int f1 = top[u],f2 = top[v];
//    cout << u << " " <<v<<endl;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        update_area(1,p[f1],p[u],2);
        int par = fa[f1];
        if(son[par] == f1) update_area(1,p[f1],p[f1],1);
        if(son[u] != -1)  update_area(1,p[son[u]],p[son[u]],1);
        u = fa[f1],f1 = top[u];
    }
    if(dep[u] > dep[v]) swap(u,v);

    update_area(1,p[u],p[v],2);
    int par = fa[u];
//    cout <<par <<" "<< son[v] <<endl;
    if(son[par] == u && par > 0) update_area(1,p[u],p[u],1);
    if(son[v] != -1)  update_area(1,p[son[v]],p[son[v]],1);
}

int Find(int u,int v)
{
//    cout <<"*********************************************************"<<endl;
    int f1 = top[u],f2 = top[v];
    int ans = 0;
//    cout << u << " " <<v<<endl;

    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        ans += query(1,p[f1]+1,p[u],1);
//        cout <<ans <<" " <<f1 <<" " <<u <<endl;
        ans += query(1,p[fa[top[u]]],p[fa[top[u]]],2)^query(1,p[top[u]],p[top[u]],2)
               ^query(1,p[top[u]],p[top[u]],1);
//        cout <<ans<<" "<<fa[f1]<<" "<<u <<endl;
        u = fa[f1],f1 = top[u];
    }
    if(dep[u] > dep[v]) swap(u,v);
//    cout << query(1,p[u]+1,p[v],1) <<endl;
    return ans+query(1,p[u]+1,p[v],1);
}

int main()
{
//    freopen("in.txt","r",stdin);
    int T,cas = 1,op;
    int a,b;
    int m,u,v;
    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d",&n);
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
            scanf("%d%d%d",&op,&a,&b);
//            cout << op <<" " <<a <<" " <<b<<endl;
            if(op == 1)
            {
                if(a == b)
                    continue;
                update_rev1(a,b);
            }
            else if(op == 2)
            {
                update_rev2(a,b);
            }
            else if(op == 3)
            {
                printf("%d\n",Find(a,b));
            }
        }
    }
    return 0;
}

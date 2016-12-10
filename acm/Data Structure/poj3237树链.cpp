/*
poj3237 树琏部分
感觉是树链+线段树比较不错的题目，主要是线段树掌握不怎么好导致一直有问题。
查询最大值 + 修改边 + 区间置反
先处理出树链，然后再上值
push_up 和 push_down函数
hhh-2016-2-2 3:46:58
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;

const int maxn = 100010;

struct node
{
    int to,next;
} edge[maxn*2];

int head[maxn];
int top[maxn];  //链的顶端节点
int far[maxn];  //父亲
int dep[maxn];  //深度
int num[maxn];  //表示以x为根的子树的节点数
int p[maxn];    //p[u]表示边u所在的位置
int fp[maxn];   //与p相对应
int son[maxn];  //重儿子
int tot,pos;
void addedge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot ++;
}

void dfs(int u,int fa,int d)          //先处理出重儿子、dep、far、num
{
    dep[u] = d;
    far[u] = fa;
    num[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v != fa)
        {
            dfs(v,u,d+1);
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
    if(son[u] == -1) return ;
    getpos(son[u],sp);
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v != far[u] && v != son[u])
            getpos(v,v);
    }
}

struct Node
{
    int l,r;
    int flag;
    int Max,Min;
} segtree[maxn*3];

void build(int i,int l,int r)
{
    segtree[i].l = l;
    segtree[i].r = r;
    segtree[i].Max = 0;
    segtree[i].Min = 0;
    segtree[i].flag = 0;
    if(l == r)
        return ;
    int mid = (l+r)/2;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}

void push_up(int i)
{
    segtree[i].Max = max(segtree[i<<1].Max,segtree[(i<<1)|1].Max);
    segtree[i].Min = min(segtree[i<<1].Min,segtree[(i<<1)|1].Min);
}

void push_down(int i)
{
    if(segtree[i].l == segtree[i].r)
        return ;
    if(segtree[i].flag)
    {
        segtree[i<<1].Max = -segtree[i<<1].Max;
        segtree[i<<1].Min = -segtree[i<<1].Min;
        swap(segtree[i<<1].Max,segtree[i<<1].Min);
        segtree[i<<1].flag ^= 1;

        segtree[(i<<1)|1].Max = -segtree[(i<<1)|1].Max;
        segtree[(i<<1)|1].Min = -segtree[(i<<1)|1].Min;
        segtree[(i<<1)|1].flag ^= 1;
        swap(segtree[(i<<1)|1].Max,segtree[(i<<1)|1].Min);

        segtree[i].flag = 0;
    }
}

void update(int i,int k,int val)
{
    if(segtree[i].l == k && segtree[i].r == k)
    {
        segtree[i].Max = val;
        segtree[i].Min = val;
        segtree[i].flag = 0;
        return ;
    }
    push_down(i);
    int mid = (segtree[i].l+segtree[i].r)>>1;
    if(k <= mid) update(i<<1,k,val);
    else update((i<<1)|1,k,val);
    push_up(i);
}

void negat(int i,int l,int r)
{
    if((segtree[i].l == l && segtree[i].r == r))
    {
        segtree[i].Max = -segtree[i].Max;
        segtree[i].Min = -segtree[i].Min;
        swap(segtree[i].Max,segtree[i].Min);
        segtree[i].flag ^= 1;
        return;
    }
    push_down(i);
    int mid = (segtree[i].l+segtree[i].r)>>1;
    if(r <= mid) negat(i<<1,l,r);
    else if(l > mid) negat((i<<1)|1,l,r);
    else
    {
        negat(i<<1,l,mid);
        negat((i<<1)|1,mid+1,r);
    }
    push_up(i);
}

int query(int i,int l,int r)
{
    if(segtree[i].l == l && segtree[i].r == r)
    {
        return segtree[i].Max;
    }
    push_down(i);
    int mid = (segtree[i].l+segtree[i].r)>>1;
    if(r <= mid) return query(i<<1,l,r);
    else if(l > mid) return query((i<<1)|1,l,r);
    else return max(query(i<<1,l,mid),query((i<<1)|1,mid+1,r));
    push_up(i);
}

int fin(int l,int r)
{
    int f1 = top[l];
    int f2 = top[r];
    int tt = -100000000;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2);
            swap(l,r);
        }
        tt = max(query(1,p[f1],p[l]),tt);
        l = far[f1];
        f1 = top[l];
    }
    if(l == r)
        return tt;
    if(dep[l] > dep[r]) swap(l,r);
    return max(tt,query(1,p[son[l]],p[r]));
}

void change(int l,int r)
{
    int f1 = top[l];
    int f2 = top[r];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2);
            swap(l,r);
        }
        negat(1,p[f1],p[l]);
        l = far[f1];
        f1 = top[l];
    }
    if(l == r) return ;
    if(dep[l] > dep[r]) swap(l,r);
    negat(1,p[son[l]],p[r]);
}

void ini()
{
    tot = 0;
    pos = 1;
    memset(head,-1,sizeof(head));
    memset(son,-1,sizeof(son));
}

int me[maxn][2];
int va[maxn];

int main()
{
    int T;
    int n;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        ini();
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d%d",&me[i][0],&me[i][1],&va[i]);
            addedge(me[i][0],me[i][1]);
            addedge(me[i][1],me[i][0]);
        }

        dfs(1,0,0);
        getpos(1,1);
        build(1,1,n);
        for(int i = 1; i < n; i++)
        {
            if(dep[me[i][0]] > dep[me[i][1]])
                swap(me[i][0],me[i][1]);
            update(1,p[me[i][1]],va[i]);
        }
        char ch[10];
        while(scanf("%s",ch) == 1)
        {
            ;
            if(ch[0] == 'D') break;
            int u,v;
            scanf("%d%d",&u,&v);
            if(ch[0] == 'Q')
                printf("%d\n",fin(u,v));
            else if(ch[0] == 'N')
                change(u,v);
            else
                update(1,p[me[u][1]],v);
        }
    }
    return 0;
}

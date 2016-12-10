/*
hdu 5274 树链剖分

problem:
给你有一个树，然后有两个操作
1.修改第x个节点的值为y
2.查询x~y路径上哪一个数出现了奇数次

solve:
由于题目保证只可能有一个数出现奇数次那么求 u->v这条链上所有点权的异或值即可
以前用 线段树+lca解决的. 这次是直接用的树链剖分,感觉思路都差不多的. 用一个数组映射当前
节点在线段树上的位置,所以
1:操作可以直接单点更新解决.
2:直接查询链上面的异或值就行. 感觉就是让u,v递推到达最小公共祖先,在过程中查询每一条重链or轻链,再将答案和并起来.
总体上和普通线段树很像

hhh-2016-08-18 15:32:24
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
} edge[maxn<<1];

void ini()
{
    tot = 0,pos = 1;
    clr(head,-1),clr(son,-1);
//    clr(val,0);
}

void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u],head[u] = tot++;
}

void dfs1(int u,int pre,int d)
{
    dep[u] = d;
    fa[u] = pre,num[u] = 1;
//    cout << "node:" << u<<endl;
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
    ll Min;
} tree[maxn << 2];
void push_up(int i)
{
    tree[i].Min = tree[lson].Min^tree[rson].Min;
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Min = inf;
    tree[i].mid=(l+r) >>1;
    if(l == r)
    {
//        cout << fp[l] <<" " <<val[fp[l]]<<endl;
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
}

void update(int i,int k,int val)
{
    if(tree[i].l == k && tree[i].r == k)
    {
//        cout << fp[k] <<" " <<val<<endl;
        tree[i].Min = val;
        return;
    }
    int mid = tree[i].mid;
    if(k <= mid) update(lson,k,val);
    else update(rson,k,val);
    push_up(i);
//    cout << tree[i].l <<" " <<tree[i].r <<" " <<tree[i].Min<<endl;
}
ll query(int i,int l,int r)
{
//    cout <<"l:"<< l <<" r:"<<r <<" min:"<< tree[i].Min<<endl;
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].Min;
    int mid = tree[i].mid;
    if(r <= mid)
        return query(lson,l,r);
    else if(l > mid)
        return query(rson,l,r);
    else
    {
        return query(lson,l,mid)^query(rson,mid+1,r);
    }
}
ll fin(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    ll tmp = 0;
//     cout <<u <<" " <<v <<endl;
//   cout <<f1 <<" " <<f2 <<endl;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        tmp = tmp^query(1,p[f1],p[u]);
        u = fa[f1],f1 = top[u];
    }
    if(u == v) return tmp;
    if(dep[u] > dep[v]) swap(u,v);
//    cout << son[u] << " " <<v <<endl;
    return (tmp^query(1,p[u],p[v]));
}

//int a[maxn];

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
       scanf("%d%d",&n,&m);
       for(int i =1;i <n;i++)
       {
           scanf("%d%d",&u,&v);
           add_edge(u,v);
           add_edge(v,u);
       }
       dfs1(1,0,0);
       getpos(1,1);
       build(1,1,pos-1);
       for(int i =1;i <= n;i++)
       {
           scanf("%d",&a);
           update(1,p[i],a+1);
       }
       for(int i = 1;i <= m;i++)
       {
           scanf("%d%d%d",&op,&a,&b);
           if(op == 0)
           {
               update(1,p[a],b+1);
           }
           else
           {
               int t = fin(a,b);
//               cout<<"t:"<<t<<endl;
               if(!t)
                printf("-1\n");
               else
                printf("%d\n",t-1);
           }
       }
    }
    return 0;
}

/*
hdu4729 树链剖分+二分

problem:
给你n个点,然你求两个点之间的最大流.而且你有一定的钱,可以进行两种操作
1.在任意连个点之间建立一个单位1的流,费用A
2.将原先的流扩大1个单位,费用B

solve:
在最初始的图上面u，v之间的流flow即u->v边上的最小值
①如果A<=B,那么我们可以直接在两个目标点u,v之间建边.所以答案为 flow+k/A
②如果A>B
 可以先建一条边然后不停地扩展 (flow-A)/B+1
 or不停地给最小的边扩展,使u->v的最小值变大. 可以二分找到这个值
最开始是二分(1,10000)结果超时QAQ. 后来发现可以先求出(flow-A)/B+1，那么二分的时候就是((flow-A)/B+1,10000)

hhh-2016-08-18 11:39:23
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
int val[maxn];
int n;
struct Edge
{
    int to,next,w;
} edge[maxn<<1];

void ini()
{
    tot = 0,pos = 1;
    clr(head,-1),clr(son,-1);
//    clr(val,0);
}

void add_edge(int u,int v,int w)
{
    edge[tot].w = w,edge[tot].to = v,edge[tot].next = head[u],head[u] = tot++;
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
            val[v] = edge[i].w;
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
    tree[i].Min = min(tree[lson].Min,tree[rson].Min);
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Min = inf;
    tree[i].mid=(l+r) >>1;
    if(l == r)
    {
        tree[i].Min = val[fp[l]];
//        cout << fp[l] <<" " <<val[fp[l]]<<endl;
        return;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
    push_up(i);
}

void update(int i,int k,int val)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].Min = val;
        return;
    }
    int mid = tree[i].mid;
    if(k <= mid) update(lson,k,val);
    else update(rson,mid,val);
    push_up(i);
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
        return min(query(lson,l,mid),query(rson,mid+1,r));
    }
}
ll find_flow(int u,int v)
{
    int f1 = top[u],f2 = top[v];
    ll tmp = inf;
//    cout <<f1 <<" " <<f2 <<endl;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        tmp = min(tmp,query(1,p[f1],p[u]));
        u = fa[f1],f1 = top[u];
    }
    if(u == v) return tmp;
    if(dep[u] > dep[v]) swap(u,v);
//    cout << son[u] << " " <<v <<endl;
    return min(tmp,query(1,p[son[u]],p[v]));
}
int allnum = 0;
bool can_do(int i,int l,int r,int mid)
{
    if(tree[i].l >= l && tree[i].r <= r && tree[i].Min >= mid)
    {
        return true;
    }
    if(tree[i].l == tree[i].r)
    {
//        cout << tree[i].Min <<" " <<mid<<endl;
        if(tree[i].Min >= mid)
            return true;
        allnum -= (mid-tree[i].Min);
        if(allnum>= 0) return true;
        return false;
    }
    if(r <= tree[i].mid)
        return can_do(lson,l,r,mid);
    else if(l > tree[i].mid)
        return can_do(rson,l,r,mid);
    else
        return can_do(lson,l,tree[i].mid,mid)&&can_do(rson,tree[i].mid+1,r,mid);
}

bool find_flag(int u,int v,int mid)
{
    int f1 = top[u],f2 = top[v];
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1,f2),swap(u,v);
        }
        if(!can_do(1,p[f1],p[u],mid))
            return false;
        u = fa[f1],f1 = top[u];
    }
    if(u == v) return true;
    if(dep[u] > dep[v]) swap(u,v);
    return can_do(1,p[son[u]],p[v],mid);
}

int a[maxn];


int main()
{
//    freopen("in.txt","r",stdin);
    int T,cas = 1;
    int x,y,k,a,b;
    int m,u,v,w;
   scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d%d",&n,&m);
//        cout << n <<" " <<m <<endl;
        for(int i =1; i < n; i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        dfs1(1,0,0);
        getpos(1,1);
        build(1,0,pos-1);
//        char op[10];
        printf("Case #%d:\n",cas++);
        for(int i = 1;i <= m;i++)
        {
            scanf("%d%d%d%d%d",&x,&y,&k,&a,&b);
            ll flow = find_flow(x,y);
//           cout <<"flow:"<<flow <<endl;
            if(k < min(a,b))
            {
                printf("%I64d\n",flow);
            }
            else if(a <= b)
            {
                printf("%I64d\n",flow+(ll)k/a);
            }
            else
            {
                ll ans = flow;
                if(k > a)
                    ans += (k-a)/b+1;
                int l = ans,r = 10000;
                while(l <= r)
                {
                    int mid = (l+r)>>1;
                    allnum = k/b;
                    if(find_flag(x,y,mid))
                    {
                        ans = mid,l = mid + 1;
                    }
                    else
                        r = mid - 1;
                }
                printf("%I64d\n",ans);
            }
        }
    }
    return 0;
}

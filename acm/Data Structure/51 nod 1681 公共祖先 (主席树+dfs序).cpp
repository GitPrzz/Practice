/*
51 nod 1681 公共祖先 (主席树+dfs序)

problem:
给你两棵树, 两个节点之间的值定义为在两个棵树中有多少一直是它们的公共祖先
求任意两个点的亲密度的总和

solve:
问题可以转换成每个点能够成为多少次公共祖先. 如果lca一直是a,b的公共祖先, 那么
a,b一定在lca的子树中.    所以找出两棵树中lca点的子树中的相同点的个数,就能计算出多少对点
在两棵树中都有lca这个公共祖先.

先处理出a树的dfs序,然后用其作为b树中dfs序的值. 在a树中，如果u在lca的子树中,那么它的序号
大于dfa[lca]小于等于eda[lca],即进出值. 所以在b树的lca的子树中找出序号在[dfa[lca],eda[lca]]
之间的个数(可以主席树维护), 就是lca子树所含相同点的个数.


hhh-2016/09/16-11:36:14
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
#include <set>
#include <map>
//#define lson  i<<1
//#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 100010;
const double PI = acos(-1.0);

template<class T> void read(T&num)
{
    char CH;
    bool F=false;
    for(CH=getchar(); CH<'0'||CH>'9'; F= CH=='-',CH=getchar());
    for(num=0; CH>='0'&&CH<='9'; num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p)
{
    if(!p)
    {
        puts("0");
        return;
    }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}


struct Edge
{
    int to,next;
};
Edge edge[maxn*2];
int tot,head[maxn];
int in[maxn];
int cnt;
void ini()
{
    tot = 0;
    cnt = 0;
    memset(in,0,sizeof(in));
    memset(head,-1,sizeof(head));
}
void add_edge(int u,int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}
int dfa[maxn],dfb[maxn],ta[maxn],tb[maxn];
int eda[maxn],edb[maxn];
void dfs(int u,int pre,int flag)
{
    if(!flag) dfa[u] = ++ cnt, ta[u] = cnt;
    else dfb[u] = ++ cnt, tb[cnt] = ta[u];
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)continue;
        dfs(v,u,flag);
    }
    if(!flag) eda[u] = cnt;
    else edb[u] = cnt;
}

int toa;
int lson[maxn * 30],rson[maxn * 30] ;
ll c[maxn * 30];

int build(int l,int r)
{
    int root = toa ++ ;
    c[root] = 0;
    if(l != r)
    {
        int mid = (l+r) >> 1;
        build(l,mid);
        build(mid+ 1,r);
    }
    return root ;
}
int n;
int update(int root,int pos,ll val)
{
    int newroot = toa ++ ,tmp = newroot;
    c[newroot ] = c[root] + val;
    int l = 1,r = n;

    while(l < r)
    {
        int mid = (l+r) >> 1;
        if(pos <= mid)
        {
            lson[newroot] = toa ++ ,rson[newroot] = rson[root];
            newroot = lson[newroot],root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = toa ++ ,lson[newroot] = lson[root];
            newroot = rson[newroot] ,root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

ll query(int root1,int root2,int la,int ra,int l,int r)
{
    if(l >= la && r <= ra)
    {
        return c[root2] - c[root1];
    }
    int mid = (l + r) >> 1;
    ll ans = 0;
    if(la <= mid)
    {
        ans += query(lson[root1],lson[root2],la,ra,l,mid);
    }
    if(ra > mid)
    {
        ans += query(rson[root1],rson[root2],la,ra,mid+1,r);
    }
    return ans;
}

void cal(int flag)
{
    int u,v;
    ini();
    for(int i = 1; i < n; i++)
    {
        read(u),read(v);
        add_edge(u,v);
        add_edge(v,u);
        in[v] ++ ;
    }
    for(int i = 1; i <= n;i++)
    {
        if(!in[i])
        {
            dfs(i,-1,flag);
            break;
        }
    }
}
int T[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    read(n);
    toa = 0;
    cal(0);
    cal(1);
    T[0] = build(1,n);
    for(int i = 1;i <= n;i++)
    {
        T[i] = update(T[i-1],tb[i],1);
    }
    ll ans = 0;
    for(int i = 1;i <= n;i++)
    {
        int l = dfb[i],r = edb[i];
        ll t = query(T[l],T[r],dfa[i],eda[i],1,n);
        ans += 1LL*t*(t-1)/2;
    }
    printf("%I64d\n",ans);
    return 0;
}

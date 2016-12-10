/*
51 nod 1766 ���ϵ���Զ���(�߶���+lca)

problem:
n���㱻n-1�������ӳ���һ����������a~b��c~d�������䣬��ʾ��ı������������������ڸ�ѡһ��֮���
�����룬������Ҫ���max��dis(i,j) |a<=i<=b,c<=j<=d��

solve:
�ʼ����������ʷ�,�������������[a,b]. ��������...
�����˵������Զ���кϲ�������.  ����[a,b]����Զ��ta,tb��[b+1,c]����Զ��tc,td���ĸ����о�����Զ
�ľ���[a,c]����Զ��..  ֤����û����ô����- -

������߶����Ͳ��Ļ�����Ҫ����������֮��ľ���.  ������st������lca�����,Ԥ������ܵõ�O(1)��.
Ȼ������߶����ϲ�ʱ������.

http://blog.csdn.net/rzo_kqp_orz/article/details/52280811

hhh-2016/09/15-21:16:26
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
#define lson  i<<1
#define rson  i<<1|1
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
const int MAXN = 100010;
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

int rmq[2*MAXN];
struct ST
{
    int mm[2*MAXN];
    int dp[2*MAXN][20];
    void init(int n)
    {
        mm[0] = -1;
        for(int i = 1; i <= n; i++)
        {
            mm[i] = ((i&(i-1)) == 0)?mm[i-1]+1:mm[i-1];
            dp[i][0] = i;
        }
        for(int j = 1; j <= mm[n]; j++)
            for(int i = 1; i + (1<<j) - 1 <= n; i++)
                dp[i][j] = rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j-1]]?dp[i][j-1]:dp[i+(1<<(j-1))][j-1];
    }
    int query(int a,int b)
    {
        if(a > b)swap(a,b);
        int k = mm[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]]?dp[a][k]:dp[b-(1<<k)+1][k];
    }
};

struct Edge
{
    int to,next;
    ll w;
};
Edge edge[MAXN*2];
int tot,head[MAXN];

int F[MAXN*2];
int P[MAXN];
int cnt;
ll dis[MAXN];
ST st;
void ini()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
void add_edge(int u,int v,ll w)
{
    edge[tot].to = v;
    edge[tot].w = w;
    edge[tot].next = head[u];
    head[u] = tot++;
}
void dfs(int u,int pre,int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for(int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)continue;
        dis[v] = dis[u] + edge[i].w;
        dfs(v,u,dep+1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}
void LCA_init(int root,int node_num)
{
    cnt = 0;
    dfs(root,root,0);
    st.init(2*node_num-1);
}
int query_lca(int u,int v)
{
    return F[st.query(P[u],P[v])];
}

ll distan(int a,int b)
{
    int lca = query_lca(a,b);
    return dis[a]+dis[b]-dis[lca]-dis[lca];
}

struct node
{
    int l,r;
    int s,t;
    ll len;
} tree[MAXN << 2];

void cal(int i,int a,int b)
{
    ll len = distan(a,b);
    if(tree[i].len < len)
    {
        tree[i].len = len;
        tree[i].s = a;
        tree[i].t = b;
    }
}

void push_up(int i)
{
    cal(i,tree[lson].s,tree[rson].s);
    cal(i,tree[lson].s,tree[rson].t);
    cal(i,tree[lson].t,tree[rson].s);
    cal(i,tree[lson].t,tree[rson].t);

    cal(i,tree[lson].s,tree[lson].t);
    cal(i,tree[rson].s,tree[rson].t);
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].len = 0;
    tree[i].s = tree[i].t = 0;
    if(l == r)
    {
        tree[i].s = tree[i].t = l;
        tree[i].len = 0;
        return;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}
int from,to;
void solve(int a,int b,ll &len)
{
    if(distan(a,b) > len)
    {
        len = distan(a,b);
        from = a,to = b;
    }
}

void query(int i,int l,int r,int &ta,int &tb)
{
    ta = tb = -1;
    if(tree[i].l >= l && tree[i].r <= r)
    {
        ta = tree[i].s ;
        tb = tree[i].t;

        return ;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    int ls,lt,rs,rt;
    ls = lt = rs = rt= -1;
    if(r <= mid)
        query(lson,l,r,ta,tb);
    else if(l > mid)
        query(rson,l,r,ta,tb);
    else
    {
        ll tans = -1;
        query(lson,l,mid,ls,lt);
        query(rson,mid+1,r,rs,rt);
        solve(ls,rt,tans);
        solve(ls,rs,tans);
        solve(lt,rt,tans);
        solve(lt,rs,tans);
        solve(ls,lt,tans);
        solve(rs,rt,tans);
        ta = from ,tb = to;
    }
    push_up(i);
}

int main()
{
//    freopen("in.txt","r",stdin);
    int n;
    int u,v,w;
    read(n);
    ini();
    for(int i = 1; i < n; i++)
    {
        read(u),read(v),read(w);
        add_edge(u,v,w);
        add_edge(v,u,w);

    }
    dis[1] = 0;
    LCA_init(1,n);
    build(1,1,n);

    int a,b,m;
    int max1,min1,max2,min2;

    read(m);
    for(int i = 1; i <= m; i++)
    {
        ll ans = 0;
        read(u),read(v);
        read(a),read(b);
        query(1,u,v,max1,min1);
        query(1,a,b,max2,min2);
//            cout << max1 << max2 << min1<<min2 <<endl;
        ans = max(ans,distan(max1,max2));
        ans = max(ans,distan(max1,min2));
        ans = max(ans,distan(min1,max2));
        ans = max(ans,distan(min1,min2));
        printf("%I64d\n",ans);
    }
    return 0;
}

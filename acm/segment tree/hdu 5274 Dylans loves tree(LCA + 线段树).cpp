/*
hdu 5274 Dylans loves tree(LCA + 线段树)

problem：
给你有一个树，然后有两个操作
1.修改第x个节点的值为y
2.查询x~y路径上哪一个数出现了奇数次

solve：
最开始想的就是通过异或求，但是不知道应该怎么保存 各个数各自出现了多少次
后来发现别人都是用的异或和来求，如果xor[x]表示x到根节点所有的异或和，由于题目保证只可能有一个数出现奇数次
那么
 xor[a]^xor[b]^xor[lca(a,b)]
就等于求的那个（出现偶数次的都被抵消了）

然后就是怎么修改值了，如果修改了一个节点的值只会对以这个节点为根的树造成影响。所以可以通过dfs序转换到
线段树上进行区间修改

hhh-2016-08-09 15:12:07
*/
#pragma comment(linker,"/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <set>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn=100000 + 500;
const int INF=0x3f3f3f3f;
const int mod = 1e9+7;
int n,tot,cnt;
int head[maxn],rmq[maxn << 1];
int flag[maxn];
int vis[maxn],xo[maxn];
int P[maxn],val[maxn];
int F[maxn<<1];
int Size[maxn];
int pos[maxn],sid;

struct Edge
{
    int to,next;
} edge[maxn << 1];


void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next=head[u],head[u] = tot++;
}

struct ST
{
    int m[maxn << 1];
    int dp[maxn << 1][20];
    void ini(int n)
    {
        m[0] = -1;
        for(int i = 1; i <= n; i++)
        {
            m[i] = ((i&(i-1)) == 0)? m[i-1]+1:m[i-1];
            dp[i][0] = i;
        }
        for(int j = 1; j <= m[n]; j++)
        {
            for(int i = 1; i+(1<<j)-1 <= n; i++)
                dp[i][j] = rmq[dp[i][j-1]] < rmq[dp[i+(1<<(j-1))][j-1]] ?
                           dp[i][j-1] : dp[i+(1 << (j-1))][j-1];
        }
    }
    int query(int a,int b)
    {
        if(a > b)
            swap(a,b);
        int k = m[b-a+1];
        return rmq[dp[a][k]] <= rmq[dp[b-(1<<k)+1][k]] ?
               dp[a][k]:dp[b-(1<<k)+1][k];
    }
};

ST st;

void dfs(int u,int pre,int dep,int Xor)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    Size[u] = 1;
    pos[u] = ++sid;
    Xor ^= val[u];
    xo[sid] = Xor;
    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)
            continue;
        dfs(v,u,dep+1,Xor);
        Size[u] += Size[v];
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
}


int query_lca(int a,int b)
{
    return F[st.query(P[a],P[b])];
}
void ini()
{
    memset(flag,0,sizeof(flag));
    memset(head,-1,sizeof(head));
    tot =0;
    cnt = sid = 0;
}

struct node
{
    int l,r;
    int val ;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn << 2];

void push_up(int i)
{
    //tree[i].lca = query_lca(tree[lson].lca,tree[rson].lca);
//    cout << tree[lson].lca << " " <<tree[rson].lca <<endl;
//    cout << tree[i].l<< " " << tree[i].r << " "  <<tree[i].lca <<endl;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].val = 0;
    if(l == r)
    {
//        cout << tree[i].l<< " " << tree[i].r << " "  <<tree[i].lca <<endl;
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].val)
    {
        tree[lson].val ^= tree[i].val;
        tree[rson].val ^= tree[i].val;
        tree[i].val = 0;
    }
}

void update(int i,int l,int r,int val)
{
    if(tree[i].l >= l && r >= tree[i].r )
    {
        tree[i].val ^= val;
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,val);
    if(r > mid)
        update(rson,l,r,val);
    push_up(i);
}

int query(int i,int k)
{
    if(tree[i].l == tree[i].r )
    {
        xo[tree[i].l] ^= tree[i].val;
        tree[i].val = 0;
        return xo[tree[i].l];
    }
    int mid = tree[i].mid();
    push_down(i);
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}

int main()
{
    int n,m,k;
    int a,b,c;
//freopen("in.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        ini();

        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);

            flag[b] = 1;
        }
        int root= 1;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&val[i]),val[i]++;
            if(!flag[i])
                root = i;
        }
        dfs(root,root,0,0);
        st.ini(2*n-1);
        build(1,1,sid+1);
       // cout << sid <<endl;
        int op;
        // printf("1 2 %d\n",query_lca(1,2));
        for(int i = 1; i <= m; i++)
        {
            scanf("%d",&op);
            scanf("%d%d",&a,&b);
            if(op == 1)
            {
                int lca = query_lca(a,b);
                int ta = query(1,pos[a]);
                int tb = query(1,pos[b]);
                if((ta ^ tb ^ val[lca]) == 0)
                    printf("-1\n");
                else
                    printf("%d\n",(ta ^ tb ^ val[lca])-1);
            }
            else
            {
                int from = pos[a];
                b ++ ;
                update(1,from,from+Size[a]-1,val[a]^b);
                val[a] = b;
            }
        }
    }
    return 0;
}

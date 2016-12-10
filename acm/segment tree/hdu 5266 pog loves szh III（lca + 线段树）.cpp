/*
hdu 5266 pog loves szh III��lca + �߶�����

problem��
����һ������Ȼ���ѯ�ڵ�l~r����С��������

solve��
����������㷨����ѯ��ʱ�����ֱ��O(1)ʵ�֣�Ȼ���ѯ�ڵ�l~r����С�������ȸо�����������ֵ
���ҿ��Է��� ���֪��a~b��c~d����С�������ȣ���ôa~d��lca ����a~b��lca��c~d��lca����С��������
���Կ������߶��������ѯ����

hhh-2016-08-08 16:58:09
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
const int maxn=300000 + 500;
const int INF=0x3f3f3f3f;
const int mod = 1e9+7;
int n,tot,cnt;
int head[maxn],rmq[maxn];
int flag[maxn];
int vis[maxn];
int P[maxn];
int F[maxn<<1];

struct Edge
{
    int from,to,next;
} edge[maxn << 1];

int fin(int x)
{
    if(F[x] == -1) return x;
    return F[x] = fin(F[x]);
}

void unio(int a,int b)
{
    int ta=  fin(a);
    int tb= fin(b);
    if(ta != tb)
        F[ta] = tb;
}

void add_edge(int u,int v)
{
    edge[tot].from = u,edge[tot].to = v,edge[tot].next=head[u],head[u] = tot++;
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

void dfs(int u,int pre,int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;

    for(int i = head[u]; ~i; i = edge[i].next)
    {
        int v = edge[i].to;
        if(v == pre)
            continue;
        dfs(v,u,dep+1);
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
    cnt = 0;
}

struct node
{
    int l,r;
    int lca;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn << 2];

void push_up(int i)
{
    tree[i].lca = query_lca(tree[lson].lca,tree[rson].lca);
//    cout << tree[lson].lca << " " <<tree[rson].lca <<endl;
//    cout << tree[i].l<< " " << tree[i].r << " "  <<tree[i].lca <<endl;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    if(l == r)
    {
        tree[i].lca = l;
//        cout << tree[i].l<< " " << tree[i].r << " "  <<tree[i].lca <<endl;
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].lca;
    }
    int mid = tree[i].mid();
    if(r <= mid)
        return query(lson,l,r);
    else if(l > mid)
        return query(rson,l,r);
    else
        return query_lca(query(lson,l,mid),query(rson,mid+1,r));
    push_up(i);
}

int main()
{
    int n,m,k;
    int a,b,c;
  //  freopen("in.txt","r",stdin);
    while(scanf("%d",&n) != EOF)
    {
        ini();

        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(b,a);
            add_edge(a,b);
            flag[b] = 1;
        }
        dfs(1,1,0);
        st.ini(2*n-1);
        scanf("%d",&m);
        build(1,1,n);
       // printf("1 2 %d\n",query_lca(1,2));
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",query(1,a,b));
//printf("%d\n",query_lca(a,b));
        }
    }
    return 0;
}

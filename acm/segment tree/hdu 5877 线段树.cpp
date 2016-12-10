/*
hdu 5877 �߶���

problem:
����һ��n���ڵ���и���,ÿ���ڵ��м�ֵa[i].   ���ж��ٸ����(u,v)����:u��v��������a[u]*a[v] <= k

solve:
���ҳ�������ĸ��ڵ�.
��ΪҪ��u��v������,�����൱��v�ĸ��׵����ڵ�����е�. ���Կ��������ı�����ʱ����߹����ֵ�����߶�����,���ߵ���i���ڵ�ֵ
����߶�����[1,k/a[i]]�ܹ��ж��ٸ�ֵ����. Ȼ��ݹ����ʱ�ڰ������ɾ��.
���ݺܴ������ٽ���һ����ɢ������.

hhh-2016-09-11 09:22:59
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#define lson  i<<1
#define rson  i<<1|1
#include <map>
#define ll long long

using namespace std;

const int maxn = 200100;

int a[maxn];

struct Node
{
    int l,r;
    int val;
} tree[maxn <<2];

void push_up(int i)
{
    tree[i].val=  tree[lson].val  + tree[rson].val;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].val = 0;
    if(l == r)
    {
        return ;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void update(int i,int k,int va)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        tree[i].val += va;
        return;
    }
    int mid = (tree[i].l + tree[i].r) >> 1;
    if(k <= mid)
        update(lson,k,va);
    else
        update(rson,k,va);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(l > r)
        return 0;
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].val;
    }
    int tans = 0;
    int mid = (tree[i].l + tree[i].r ) >> 1;
    if(l <= mid)
        tans += query(lson,l,r);
    if(r > mid)
        tans += query(rson,l,r);
    return tans;
}

struct node
{
    int next;
    int to;
} edge[maxn];
ll k;
int ta,tot,n;
int head[maxn];
int deep[maxn];
int t[maxn];
void addedge(int from,int to)
{
    edge[tot].to=to;
    edge[tot].next=head[from];
    head[from]=tot++;
}
ll ans = 0;
void dfs(int u,int fa)
{
    int o=lower_bound(t,t+ta,k/a[u])-t;
    ans+=query(1,0,o);

    int tk=lower_bound(t,t+ta,a[u])-t;
    update(1,tk,1);
    for(int i=head[u]; ~i; i=edge[i].next)
    {
        int v=edge[i].to;
        dfs(v,u);
    }
    update(1,tk,-1);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %I64d",&n,&k);
        int cnt=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%I64d",&a[i]);
            t[cnt++]=a[i];
        }
        for(int i=1; i<=n; i++) t[cnt++]=k/a[i];

        sort(t,t+cnt);
        ta=unique(t,t+cnt)-t;

        tot=0;
        memset(head,-1,sizeof(head));
        memset(deep,0,sizeof(deep));

        for(int i=0; i<n-1; i++)
        {
            int u,v;
            scanf("%d %d",&u,&v);
            addedge(u,v);
            deep[v]++;
        }

        ans=0;
        build(1,0,ta);
        for(int i=1; i<=n; i++)
            if(deep[i]==0)
                dfs(i,-1);
        printf("%I64d\n",ans);
    }
    return 0;
}


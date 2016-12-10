/*
hdu 3974 �߶��� ����Ū��������

���⣺ ����һ������50000���ڵ㣬50000������
C x��ʾ��ѯx�ڵ��ֵ��
T x y��ʾ����x�ڵ㼰���ӽڵ��ֵΪy

û�뵽���ǲ��鼯���ܹ����������ɶ�ˮ - -

����T����ÿ�θ��µ�ǰ�ڵ��Լ���������,����dfsһ��,��ÿ���ڵ���б�š� ÿ�θ���
�ͳ��˶� ��ǰ�ڵ��������������ĸ��¡�

hhh-2016-04-22 14:09:04
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const int  maxn = 50010;

struct node
{
    int l,r;
    int val;
    int lazy;
    int mid() {return (l+r) >> 1;}
}tree[maxn<<2];

int tot,cnt;
int rt[maxn];
int st[maxn],ed[maxn];
vector <int > vec[maxn];
void dfs(int cur)
{
    st[cur] = ++cnt;
    for(int i = 0;i < vec[cur].size();i++)
    {
        dfs(vec[cur][i]);
    }
    ed[cur] = cnt;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].val = -1,tree[i].lazy = 0;
    if(l == r)
        return ;
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
}

void push_down(int i)
{
    if(tree[i].lazy)
    {
        tree[lson].val = tree[i].val,tree[lson].lazy = 1;
        tree[rson].val = tree[i].val,tree[rson].lazy = 1;
        tree[i].lazy = 0;
    }
}

void update(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
         tree[i].val = val;
         tree[i].lazy = 1;
         return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,val);
    if(r > mid)
        update(rson,l,r,val);
//    if(r <= mid)
//        update(lson,l,r,val);
//    else if(l > mid)
//        update(rson,l,r,val);
//    else
//    {
//        update(lson,l,mid,val);
//        update(rson,mid+1,r,val);
//    }
    return ;
}

int query(int i,int k)
{
    if(tree[i].l == k && tree[i].r == k)
        return tree[i].val;
    int mid = tree[i].mid();
    push_down(i);
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}

int main()
{
    int T,n,m,x,y;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        cnt = 0;
        scanf("%d",&n);
        printf("Case #%d:\n",cas++);
        for(int i = 1;i <= n;i++)
        {
            vec[i].clear();
        }
        memset(rt,0,sizeof(rt));
        int u,v;
        for(int i = 1;i < n;i++)
        {
            scanf("%d%d",&u,&v);
            vec[v].push_back(u);
            rt[u] = 1;
        }
        int rot;
        for(int i = 1;i <= n;i++)
        {
            if(!rt[i])
            {
                rot = i;
                break;
            }
        }
        dfs(rot);
        build(1,1,cnt);
        char op[10];
        scanf("%d",&m);
        for(int i = 1;i <= m;i++)
        {
            scanf("%s",op);
            if(op[0] == 'C')
            {
                scanf("%d",&x);
                printf("%d\n",query(1,st[x]));
            }
            else if(op[0] == 'T')
            {
                scanf("%d%d",&x,&y);
                update(1,st[x],ed[x],y);
            }
        }
    }
    return 0;
}

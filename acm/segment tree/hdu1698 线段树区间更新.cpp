/*
hdu1698 线段树区间更新
hhh-2016-03-04 20:29:58
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 150050;
const int inf = 0x3f3f3f3f;

struct node
{
    int val,sum;
    int l,r;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].sum = tree[lson].sum + tree[rson].sum;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].val = 0;
    tree[i].sum = 1;
    if(l == r)
    {
        return ;
    }
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].val)
    {
        tree[lson].val = tree[i].val;
        tree[rson].val = tree[i].val;
        tree[lson].sum = tree[i].val*(tree[lson].r-tree[lson].l+1);
        tree[rson].sum = tree[i].val*(tree[rson].r-tree[rson].l+1);
        tree[i].val = 0;
    }
}


void update(int i,int l,int r,int v)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].val = v;
        tree[i].sum = v*(tree[i].r-tree[i].l+1);
        return ;
    }
    push_down(i);
    if(l <= tree[i].mid())
        update(lson,l,r,v);
    if(r > tree[i].mid())
        update(rson,l,r,v);
    push_up(i);
}


int main()
{
    int T,n,q;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%d",&q);
        build(1,1,n);
        for(int i =1; i <= q; i++)
        {
            int l,r,val;
            scanf("%d%d%d",&l,&r,&val);
            update(1,l,r,val);
        }
        printf("Case %d: The total value of the hook is %d.\n",cas++,tree[1].sum);
    }
    return 0;
}

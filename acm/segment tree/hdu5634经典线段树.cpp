/*
BestCoder Round #73 (div.1)
hdu5634	Rikka with Phi
本来最开始用伸展树(主要是线段树不是很熟)的，但是中间有点问题，导致一直是TLE，于是乎
就去写线段树了
感觉对线段树的理解上有很多问题TAT
思路：先打个表在用线段树(平衡树)去解决
主要是有same标记，sum和，欧拉
中间有个机智的做法就是在将一个区间改变成欧拉时，如果中间遇到了区间的same，直接
修改这个标记就好的
hhh-2016-02-25 17:54:59
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 300010;
ll euler[10000010] = {0};
void getEuler()
{
    euler[1] = 1;
    for(ll i =2 ; i <= 10000000; i++)
    {
        if(!euler[i])
        {
            for(ll j = i; j <= 10000000; j += i)
            {
                if(!euler[j])
                    euler[j] = j;
                euler[j] = euler[j]/i*(i-1);
            }
        }
    }
}

struct node
{
    int l,r;
    ll sum,same;
} segtree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    segtree[r].sum = segtree[lson].sum + segtree[rson].sum;
    if(segtree[lson].same == segtree[rson].same)
        segtree[r].same = segtree[lson].same;
    else
        segtree[r].same = 0;
}

void build(int i ,int l,int r)
{
    segtree[i].l = l,segtree[i].r = r;
    segtree[i].sum = segtree[i].same = 0;
    if(l == r)
    {
        scanf("%I64d",&segtree[i].same);
        segtree[i].sum = segtree[i].same;
        return ;
    }
    int mid = (l+r)>>1;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
    push_up(i);
}


void push_down(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    if(segtree[r].same)
    {
        segtree[lson].same = segtree[r].same;
        segtree[rson].same = segtree[r].same;
        segtree[lson].sum = (ll)(segtree[lson].r - segtree[lson].l+1)*segtree[r].same;
        segtree[rson].sum = (ll)(segtree[rson].r - segtree[rson].l+1)*segtree[r].same;
        segtree[r].same = 0;
    }
}

void make_euler(int i,int l,int r)
{
    //区间修改
    if(segtree[i].r <= r && segtree[i].l >= l && segtree[i].same)
    {
        segtree[i].same  = (ll)euler[segtree[i].same];
        segtree[i].sum = segtree[i].same*(ll)(segtree[i].r-segtree[i].l+1);
        return;
    }
    if(l == r) return ;
    int mid = (segtree[i].r +segtree[i].l) >>1;
    push_down(i);
    if(l <= mid)
        make_euler(i<<1,l,r);
    if(r > mid)
        make_euler((i<<1)|1,l,r);
    push_up(i);
}
void make_same(int i,int l,int r,ll c)
{
    if(segtree[i].r <= r && segtree[i].l >= l)
    {
        segtree[i].same = c;
        segtree[i].sum = segtree[i].same*(ll)(segtree[i].r-segtree[i].l+1);
        return;
    }
    int mid = (segtree[i].r +segtree[i].l) >>1;
    push_down(i);
    if(l <= mid)
        make_same(i<<1,l,r,c);
    if(r > mid)
        make_same((i<<1)|1,l,r,c);
    push_up(i);
}

ll get_sum(int i,int l,int r)
{
    int mid = (segtree[i].l + segtree[i].r) >> 1;
    if(segtree[i].l >= l && segtree[i].r <= r)
    {
        return segtree[i].sum;
    }
    push_down(i);
    ll ans = 0;
    if(l <= mid) ans += get_sum(i<<1,l,r);
    if(r > mid) ans += get_sum(i<<1|1,l,r);
    push_up(i);
    return ans;
}

int main()
{
    int T,n,m;
    getEuler();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        build(1,1,n);
        for(int i =1; i <= m; i++)
        {
            int op,l,r;
            ll c;
            scanf("%d",&op);
            if(op == 1)
            {
                scanf("%d%d",&l,&r);
                make_euler(1,l,r);
                //debug();
            }
            else if(op == 2)
            {
                scanf("%d%d%I64d",&l,&r,&c);
                make_same(1,l,r,c);
                // debug();
            }
            else if(op == 3)
            {
                scanf("%d%d",&l,&r);
                printf("%I64d\n",get_sum(1,l,r));
            }
        }
    }
    return 0;
}

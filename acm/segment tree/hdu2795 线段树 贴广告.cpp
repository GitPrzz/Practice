/*
hdu2795 线段树 贴广告
在一个h*w的广告板上贴广告，每次广告的大小为1*wi
要求每次尽可能贴的高，然后靠左，求每次广告在哪一行
h和w都为10^9，但是总共只有200000个广告，每次广告最多站一行，所以h=min(h,q)，
在这样的大小便能使用线段树。每次先检查能够插入，然后在最靠左的位置上加上即可
hhh-2016-02-29 10:42:10
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <vector>
typedef long long ll;
using namespace std;
const int maxn = 200000+5;
ll h,w;
struct node
{
    int l,r;
    ll Min;
} tree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    tree[r].Min = min(tree[lson].Min,tree[rson].Min);
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Min  = 0;
    if(l == r)
    {
        return ;
    }
    int mid = (l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    push_up(i);
}
void push_down(int r)
{

}

void Insert(int i,ll k)
{
    if(tree[i].l == tree[i].r)
    {
        tree[i].Min += (ll)k;
        printf("%d\n",tree[i].l);
        return ;
    }
    push_down(i);
    ll M1 = tree[i<<1].Min;
    //ll M2 = tree[i<<1|1].Min;
    if(w-M1 >= k) Insert(i<<1,k);
    else Insert(i<<1|1,k);
    push_up(i);
}

int main()
{
    ll q;
    while(scanf("%I64d%I64d%I64d",&h,&w,&q)!=EOF)
    {
        h = min(h,q);
        build(1,1,h);
        ll x;
        for(int i =1; i <= q; i++)
        {
            scanf("%I64d",&x);
            if(w-tree[1].Min>=x)
                Insert(1,x);
            else
                printf("-1\n");
        }
    }
    return 0;
}


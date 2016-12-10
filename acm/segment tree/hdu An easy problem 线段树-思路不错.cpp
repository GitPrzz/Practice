/*
hdu An easy problem 线段树-思路不错
给你2个操作，1 x 和  2 y，分别表示乘上x和撤销第y个乘法操作
*/
#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long  double ld;

const int maxn = 100010;
ll q,mod;

struct node
{
    ll l,r;
    ll sum;
} segment[maxn << 2];

void push_up(int i)
{
    segment[i].sum = (segment[i<<1].sum*segment[(i<<1)|1].sum)%mod;
}

void build(ll i,ll l,ll r)
{
    segment[i].l = l;
    segment[i].r = r;
    segment[i].sum = 1;
    if(l == r) return;
    ll mid = (l+r)/2;
    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}

void add(ll i,ll k,ll ad)
{
    if(segment[i].l == k && segment[i].r == k)
    {
        segment[i].sum = ad;
        return;
    }
    ll mid = (segment[i].r + segment[i].l)>>1;
    if(k <= mid)  add(i<<1,k,ad);
    else  add((i<<1)|1,k,ad);
    push_up(i);
}

int main()
{
    int T,cas =1 ;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%I64d",&q,&mod);
        int t = 1,op;
        ll x;
        build(1,1,q);
        printf("Case #%d:\n",cas++);
        for(int i =1; i <= q; i++)
        {
            scanf("%d%I64d",&op,&x);
            if(op == 1)
            {
                add(1,i,x);
                printf("%I64d\n",segment[1].sum);
            }
            else
            {
                add(1,x,1);
                printf("%I64d\n",segment[1].sum);
            }
        }
    }
    return 0;
}

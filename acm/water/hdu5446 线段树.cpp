/*
hdu 5446  ¼òµ¥Ïß¶ÎÊ÷
hhh-2016-02-02 04:13:44
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;

const int maxn = 50005;

struct node
{
    int l,r;
    int Max;
} pnode[maxn*3];

void push_up(int i)
{
    pnode[i].Max = max(pnode[i<<1].Max,pnode[(i<<1)|1].Max);
}

void build(int i,int l,int r)
{

    pnode[i].l = l;
    pnode[i].r = r;
    pnode[i].Max = 0;
    if(l == r)
        return;

    int mid = (l+r)>>1;

    build(i<<1,l,mid);
    build((i<<1)|1,mid+1,r);
}

int query(int i,int l,int r)
{
    if(pnode[i].l == l && pnode[i].r == r)
    {
        return pnode[i].Max;
    }
    int mid = (pnode[i].l+pnode[i].r)/2;
    if(r <= mid) return query(i<<1,l,r);
    else if(l > mid) return query((i<<1)|1,l,r);
    else return max(query(i<<1,l,mid),query((i<<1)|1,mid+1,r));
}

void add(int i,int k,int val)
{
    if(pnode[i].l == k && pnode[i].r == k)
    {
         pnode[i].Max = val;
         return ;
    }
    int mid = (pnode[i].l + pnode[i].r) / 2;
    if(k <= mid) add(i<<1,k,val);
    else add((i<<1)|1,k,val);
    push_up(i);
}


int main()
{
   int T,n;
   scanf("%d",&T);
   while(T--)
   {
       scanf("%d",&n);
       build(1,1,n);
       for(int i = 1;i <= n;i++)
       {
           int x;
           scanf("%d",&x);
           add(1,i,x);
       }
       int m,u,v;
       scanf("%d",&m);
       while(m--)
       {
           scanf("%d%d",&u,&v);
           printf("%d\n",query(1,u,v));
       }
   }
}

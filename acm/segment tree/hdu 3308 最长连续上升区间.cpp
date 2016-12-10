/*
hdu 3308 最长连续上升区间

给你n个数,然后是两个操作：
1.U A B 将第A个数替换成B
2.Q A B 查询[A,B]间的最长连续上升序列长度

看见题就感觉像前面写过的hdu1540最长连续序列,只是它那个序列是固定的
连续递增,只需要维护一下即可
所以在本题中我新增了lval,rval记录区间最左边和最右边的值,然后通过判断
这两个值来进行区间合并。同时用ls,rs,ms分别记录 从区间左端开始,区间
右端开始，整个区间 的最长连续上升序列

然后通过线段树来维护ls,rs,ms的值,然后查询进行一下判断即可

hhh-2016-03-31 19:50:28
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
const int maxn = 200050;

struct node
{
    int l,r;
    int ls,rs,ms;
    int lval,rval;
    int mid()
    {
        return (l+r)>>1;
    }
    int len()
    {
        return (r-l+1);
    }
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].ls = tree[lson].ls,tree[i].lval=tree[lson].lval;
    tree[i].rs = tree[rson].rs,tree[i].rval=tree[rson].rval;
    //如果可以合并(ls,rs可能超过区间的一般)
    if(tree[i].ls == tree[lson].len() && tree[lson].rval < tree[rson].lval)
        tree[i].ls += tree[rson].ls;
    if(tree[i].rs == tree[rson].len() && tree[lson].rval < tree[rson].lval)
        tree[i].rs += tree[lson].rs;
    tree[i].ms = max(tree[lson].ms,tree[rson].ms);
    if(tree[lson].rval < tree[rson].lval)
        tree[i].ms = max(tree[i].ms,tree[lson].rs+tree[rson].ls);
                     //可能跨过了mid界限
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].ls=tree[i].rs=tree[i].ms=0;
    tree[i].lval=tree[i].rval=0;
    if(l == r)
    {
        scanf("%d",&tree[i].lval);
        tree[i].rval = tree[i].lval;
        tree[i].ls=tree[i].rs=tree[i].ms=1;
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void update(int i,int k,int va)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].lval = va;
        tree[i].rval = va;
        return;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        update(lson,k,va);
    else
        update(rson,k,va);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l == l && tree[i].r == r)
    {
        return tree[i].ms;
    }
    int mid = tree[i].mid();
    if(r <= mid)
        return query(lson,l,r);
    else if(l > mid)
        return query(rson,l,r);
    else
    {
        int ans1 = query(lson,l,mid);
        int ans2 = query(rson,mid+1,r);
        if(tree[lson].rval < tree[rson].lval)  //如果可以合并(ls,rs有可能超出查询区间)
            return max(max(ans1,ans2),min(tree[lson].rs,mid-l+1)+min(tree[rson].ls,r-mid));
        else
            return max(ans1,ans2);
    }
}
char op[10];
int x,y;
int T,n,m;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
       scanf("%d%d",&n,&m);
       build(1,0,n-1);

       while(m--)
       {
           scanf("%s",op);
           scanf("%d%d",&x,&y);
           if(op[0] == 'Q')
           {
               printf("%d\n",query(1,x,y));
           }
           else
           {
               update(1,x,y);
           }
       }
    }
    return 0;
}

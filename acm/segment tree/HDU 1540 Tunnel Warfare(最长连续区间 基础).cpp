/*
HDU 1540 Tunnel Warfare(最长连续区间 基础)

给你1-n连续的n个数字,然后执行以下三种操作
1.D x 删除第x个数字
2.R   恢复上一次删除的数字
3.Q x 查询包含x的最长连续区间

主要有ls,rs,ms分别表示当前节点 左端点开始的最长...,右端点...,最长连续区间
然后主要是在push_up和query上面了,要进行一些特殊判断来确定长度是否应该合并

hhh-2016-03-27 16:39:28
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
const int maxn = 50050;
struct node
{
    int l,r;
    int ls,rs,ms;  //左端点,右端点,最大
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];

void push_up(int i)
{
    tree[i].ls = tree[lson].ls;
    tree[i].rs = tree[rson].rs;

    tree[i].ms = max(tree[lson].ms,tree[rson].ms);
    tree[i].ms = max(tree[i].ms,tree[rson].ls+tree[lson].rs);
    //i的ms肯定是lson,rson的ms.或者它们中间相连的长度
    if(tree[i].ls == tree[lson].r-tree[lson].l+1)
        //如果包含左儿子的全部,则与右儿子的ls相连
        tree[i].ls += tree[rson].ls;
    if(tree[i].rs == tree[rson].r-tree[rson].l+1)
        tree[i].rs += tree[lson].rs;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].ls=tree[i].rs=tree[i].ms=0;
    if(l ==r )
    {
        tree[i].ls=tree[i].rs=tree[i].ms=1;
        return ;
    }
    int mid=tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int k,int val)
{
    if(tree[i].l == tree[i].r)
    {
        if(val == 1)
            tree[i].ls=tree[i].rs=tree[i].ms=1;
        else
            tree[i].ls=tree[i].rs=tree[i].ms=0;
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        Insert(lson,k,val);
    else
        Insert(rson,k,val);
    push_up(i);
}

int query(int i,int k)
{
    if(tree[i].l==tree[i].r || tree[i].ms==0 || tree[i].ms==(tree[i].r-tree[i].l+1))
        return tree[i].ms;

    int mid = tree[i].mid();
    if(k <= mid)
    {
        if(k >= tree[lson].r-tree[lson].rs+1)  //如果在rs的范围内,加上右儿子的ls(相连)
            return query(lson,k) + query(rson,mid+1);
        else
            return query(lson,k);
    }
    else
    {
        if(k <= tree[rson].ls+tree[rson].l-1)  //同理
            return query(rson,k)+query(lson,mid);
        else
            return query(rson,k);
    }
}

int qry[maxn];
char op[0];
int main()
{
    int n,x,q;
    int cas =1;
    while(scanf("%d%d",&n,&q) != EOF)
    {
        int tot = 0;
        build(1,1,n);
        for(int i = 1; i <= q; i++)
        {
            scanf("%s",op);
            if(op[0] == 'D')
            {
                scanf("%d",&x);
                qry[tot++] = x;
                Insert(1,x,-1);
            }
            else if(op[0] == 'R')
            {
                x = qry[--tot];
                Insert(1,x,1);
            }
            else
            {
                scanf("%d",&x);
                printf("%d\n",query(1,x));
            }
        }
    }
    return 0;
}

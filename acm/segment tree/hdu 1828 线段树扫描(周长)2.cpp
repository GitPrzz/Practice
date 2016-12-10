/*
hdu 1828 线段树扫描(周长)2

在向上扫描的过程中我们可以计算出平行于x轴的长度
然后在两条线之间我们只需要计算出有多少条竖线便能得带这两条线之间平行于
y轴的长度。
用ls和rs来表示当前节点左右端点是否被覆盖
在处理竖线数量时,注意合并带来的影响,假设lson.rs和rson.ls都存在值的话
说明存在重叠的部分

hhh-2016-03-26 17:58:50
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
const int maxn = 20050;
int a[maxn];
struct node
{
    int l,r;
    int sum,len;
    int num,ls,rs;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];

void push_up(int i)
{
    if(tree[i].sum)
    {
        tree[i].len = (tree[i].r-tree[i].l+1);
        tree[i].ls = tree[i].rs = 1;
        tree[i].num = 1;
    }
    else if(tree[i].l == tree[i].r)
    {
        tree[i].len= 0;
        tree[i].num=tree[i].rs=tree[i].ls=0;
    }
    else
    {
        tree[i].len = tree[lson].len+tree[rson].len;
        tree[i].ls = tree[lson].ls;
        tree[i].rs = tree[rson].rs;
        tree[i].num = tree[lson].num+tree[rson].num;
        tree[i].num -= (tree[lson].rs&tree[rson].ls);
        //减去重叠的部分
    }
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = tree[i].len = 0;
    tree[i].ls = tree[i].rs = tree[i].num = 0;
    if(l == r)
        return ;

    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <=r )
    {
        tree[i].sum += val;
        push_up(i);
        return ;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
}

struct edge
{
    int l,r;
    int va,high,id;
};
edge tx[maxn*2];

bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        int x1,x2,y1,y2;
        int tox = 0,lx=0x3f3f3f3f,rx=0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            lx = min(x1,lx),rx = max(rx,x2);
            tx[tox].l = x1,tx[tox].r = x2,tx[tox].high=y1,tx[tox++].va=1;
            tx[tox].l = x1,tx[tox].r = x2,tx[tox].high=y2,tx[tox++].va=-1;
        }
        sort(tx,tx+tox,cmp);
        int ans=0,prelen = 0;
        build(1,lx,rx-1);
        //tx[tox] = tx[tox+1];
        for(int i = 0; i < tox; i++)
        {
            Insert(1,tx[i].l,tx[i].r-1,tx[i].va);
            ans += abs(tree[1].len-prelen);
            if(i != tox-1)
            ans += (tx[i+1].high-tx[i].high)*tree[1].num*2;
            prelen = tree[1].len;
        }
        cout << ans <<endl;
    }
    return 0;
}

/*
hdu 2871 线段树(各种操作)

New x:从1开始找到一个长度x空白区间来分配内存
Free x:释放x所在连续区间的内存 并输出左右端点
Get x:获得第x个区间的左端点
reset:释放全部的内存

如果对一个区间分配了内存则置为1,空白处全是0
1.对于New操作需要的便是0的最大连续长度 可通过ls,rs,ms来求,先判断区间是否能放下
能则找出它的左端点即可
2.然后是Free,即1的区间。我们可以用from，to来记录一个区间的左右端点，然后通过
push_down下放到单点.所以只需要找出x点对应的节点编号i即可
3.因为求的是第x个区间,所以开始用num求的时候错了好几次。发现可以把区间左端点
标记为1.但是在实现的时候忘记了判断当前位置是否是要更新区间的左端点，卒！
if(tree[i].l == l)
    tree[i].num = 1;
4.对于reset,把区间全部更新为0即可

求单点所在区间左右端点+最长连续区间的运用+求第k个区间

hhh-2016-04-02 17:48:33
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
    int ls,ms,rs;   //记录0的连续区间
    int num,same;
    int from,to;    //记录1的左右端点
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
    tree[i].ls = tree[lson].ls,tree[i].rs= tree[rson].rs;
    if(tree[i].ls == tree[lson].len())
        tree[i].ls += tree[rson].ls;
    if(tree[i].rs == tree[rson].len())
        tree[i].rs += tree[lson].rs;
    tree[i].ms = max(tree[lson].ms,tree[rson].ms);
    tree[i].ms = max(tree[i].ms,tree[lson].rs + tree[rson].ls);

    tree[i].num = tree[lson].num + tree[rson].num;
}

void ini(int i,int val)
{
    tree[i].ls=tree[i].rs=tree[i].ms=val;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].same =tree[i].from = tree[i].to = -1;
    tree[i].num = 0;
    if(l == r)
    {
        ini(i,1);
        return ;
    }
    int mid = (l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].same != -1)
    {
        tree[lson].same = tree[i].same;
        tree[rson].same = tree[i].same;
        tree[lson].from = tree[rson].from = tree[i].from;
        if(tree[i].num != -1)
        {
            tree[lson].num = tree[i].num;
            tree[rson].num = 0;
        }
        tree[lson].to = tree[rson].to = tree[i].to;
        ini(lson,(!tree[i].same)*tree[lson].len());
        ini(rson,(!tree[i].same)*tree[rson].len());
        tree[i].same = -1;
    }

}

void update(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].same = val;
        if(val)
        {
            if(tree[i].l == l)
            tree[i].num = 1;
            tree[i].from = l;
            tree[i].to = r;
            ini(i,0);
        }
        else
        {
            if(tree[i].l == l)
            tree[i].num = 0;
            tree[i].from = tree[i].to = -1;
            ini(i,tree[i].len());
        }
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,val);
    if(r > mid)
        update(rson,l,r,val);
    push_up(i);
    return ;
}

int New(int i,int len)
{
    if(tree[i].l == tree[i].r)
    {
        return tree[i].l;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(tree[lson].ms >= len)
        return New(lson,len);
    else if(tree[lson].rs + tree[rson].ls >= len)
        return mid-tree[lson].rs+1;
    else
        return New(rson,len);
}

int Free(int i,int k)
{
    if(tree[i].l == tree[i].r)
        return i;
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        return Free(lson,k);
    else
        return Free(rson,k);
}

int Get(int i,int k)
{
    if(tree[i].l == tree[i].r)
        return tree[i].l;
    push_down(i);
    if(tree[lson].num >= k)
        return Get(lson,k);
    else
        return Get(rson,k-tree[lson].num);
}

char op[10];

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF)
    {
        build(1,1,n);
        int x;
        while(m--)
        {
            scanf("%s",op);
            if(op[0] == 'N')
            {
                scanf("%d",&x);

                if(tree[1].ms >= x)
                {
                    int l = New(1,x);
                    printf("New at %d\n",l);
                    update(1,l,l+x-1,1);
                }
                else
                    printf("Reject New\n");

            }
            else if(op[0] == 'F')
            {
                scanf("%d",&x);
                int t = Free(1,x);
                if(tree[t].from == -1)
                    printf("Reject Free\n");
                else
                {
                    printf("Free from %d to %d\n",tree[t].from,tree[t].to);
                    update(1,tree[t].from,tree[t].to,0);
                }
            }
            else if(op[0] == 'G')
            {
                scanf("%d",&x);
                if(tree[1].num >= x)
                    printf("Get at %d\n",Get(1,x));
                else
                    printf("Reject Get\n");
            }
            else if(op[0] == 'R')
            {
                update(1,1,n,0);
                printf("Reset Now\n");
            }
        }
        printf("\n");
    }
    return 0;
}

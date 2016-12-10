/*
hdu 1542 线段树扫描(面积)

给你n个矩形,求最终形成的图形的面积大小

数据不一定是正数,所以先对他们进行离散化处理
大致就是每次计算平行于x轴的两条相邻线之间的面积,我们已经知道了两条平行
线之间的高度，于是就转变成在求当前情况下映射到x轴上的线段的长度,这个便能
利用线段树解决了

先把所有平行于x轴的线段按高度排序,然后从下往上,每次在遇到矩形下边时在
[l,r]上加1表示线段覆盖,遇到上边则填上-1消除影响.然后每次计算覆盖长度
再乘上高即可

参考(图文详解)：
http://www.cnblogs.com/scau20110726/archive/2013/04/12/3016765.html

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
const int maxn = 10005;
double hs[maxn];
struct node
{
    int l,r;
    double len;
    int sum;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];

void push_up(int i)
{
    if(tree[i].sum)
    {
        tree[i].len = (hs[tree[i].r+1]-hs[tree[i].l]);
    }
    else if(tree[i].l == tree[i].r)
    {
        tree[i].len= 0;
    }
    else
    {
        tree[i].len = tree[lson].len+tree[rson].len;
    }
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = tree[i].len = 0;
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
    double l,r,high;
    int va;
    edge() {};
    edge(double _l,double _r,double _high,int _va):l(_l),r(_r),high(_high),va(_va)
    {}
};
edge tx[maxn*2];

bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}
int tot,m;
int fin(double x)
{
    int l = 0,r = m-1;
    while(l <= r)
    {
        int mid = (l+r)>>1;
        if(hs[mid] == x)
            return mid;
        else if(hs[mid] < x)
            l = mid+1;
        else
            r = mid-1;
    }
}

int main()
{
    int n;
    int cas =1;
    while(scanf("%d",&n) != EOF && n)
    {
        double x1,x2,y1,y2;
        tot = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            hs[tot] = x1;
            tx[tot++] = edge(x1,x2,y1,1);
            hs[tot] = x2;
            tx[tot++] = edge(x1,x2,y2,-1);
        }
        sort(tx,tx+tot,cmp);
        sort(hs,hs+tot);
        m = 1;
        for(int i = 1;i < tot;i++)
        {
            if(hs[i] != hs[i-1])
                hs[m++] = hs[i];
        }
        build(1,0,m);
        double ans = 0;
        for(int i = 0;i < tot;i++)
        {
            int l = fin(tx[i].l);
            int r = fin(tx[i].r)-1;

            Insert(1,l,r,tx[i].va);
            ans += (tree[1].len)*(tx[i+1].high-tx[i].high);
            //cout << ans <<endl;
        }
        printf("Test case #%d\n",cas++);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}

/*
hdu 4533 线段树(问题转化+)

已知有n个矩形床单,假设水从原点开始蔓延,t秒时(0,0)->(t,t)的范围内会有睡
给你m个询问,x时间床单湿的面积

最开始想的是扫描线,感觉有点像求矩形重复面积的部分。但是想了会发现扫描线是从
下往上递推出来的,但本题需要的是(x,x)这个矩形范围内的面积,并不能通过一次query搞出,卒 Orz

然后就去膜拜大神了TAT
对于一个矩形床单(x1,y1,x2,y2)，如果它被全覆盖面积也就是(x2-x1)*(y2-y1).但如果覆盖一部分也就是
(t-x1)*(t-y1)(t为正方形的边长).
但是覆盖方式有好几种
 1.max(x1,y1)<=t<=min(x2,y2):即正方形的直角的矩形内
 ->s=(t-x1)*(t-y1)=t*t-(x1+y1)*t+x1*y1
 2.min(x2,y2)<=t<=max(x2,y2):假设只与上边相交(如图)
 s=(t-x1)*(t-y1) - (t-x2)*(t-y1) = (-x1-y1+x2+y1)*t+(x1*y1-x2*y1)
      _
 ____|_|_
|    | | |
|    |_| |
|        |
|________|
只与正方形右边相交右边的情况同理....

可以发现上面的面积公式都可以转换成 A*t*t+B*t+C(一个关于t的公式)
就一个位置的t而言,不通的床单都会给他一个不同A,B,C系数,而且是可以加减叠加的
于是就可以利用线段树保存每个t对应的系数,然后依次query计算一下就能解决了
这转化也是给跪哩 ╮(╯_╰)╭

所以我们需要通过判断来确定床单所适合t的范围,如果2就不可能出现与正方形上.右边同时
相交的情况。
又单面相交而言：
图1(x2,y2)        图2(y1,y2)
t1=max(x1,y1)    t2=(min(x2,y2))   ->max(t1,t2)~max(x2,y2)
      _              _
     | |            | |
 ____|_|         ___|_|__
|    |_|        |        |
|      |        |        |
|______|        |        |
                |________|
参考：http://blog.csdn.net/zkfzkfzkfzkfzkfzkfzk/article/details/8738504
hhh-2016-04-03 17:22:44
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
const int mod = 1e8+7;
const int maxn = 200050;
int limi = 200000;

struct node
{
    int l,r;
    ll A,B,C;
    int mid()
    {
        return (l+r)>>1;
    }
    int len()
    {
        return (r-l+1) ;
    }
} tree[maxn<<2];

void update_up(int i)
{

}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].A = tree[i].B = tree[i].C = 0;
    if(l == r)
        return ;
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    update_up(i);
}

void update_down(int i)
{
    tree[lson].A+=tree[i].A,tree[rson].A+=tree[i].A;
    tree[lson].B+=tree[i].B,tree[rson].B+=tree[i].B;
    tree[lson].C+=tree[i].C,tree[rson].C+=tree[i].C;
    tree[i].A = tree[i].B = tree[i].C = 0;
}

void update(int i,int l,int r,ll *va)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].A += va[0],tree[i].B += va[1],tree[i].C += va[2];
        return ;
    }
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,va);
    if(r > mid)
        update(rson,l,r,va);
    update_up(i);
}

ll query(int i,ll k)
{
    if(tree[i].l == tree[i].r)
    {
        return (ll)tree[i].A*k*k+tree[i].B*k+tree[i].C;
    }
    int mid = tree[i].mid();
    update_down(i);
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}
ll Min(ll a,ll b)
{
    return a<b ? a:b;
}

ll Max(ll a,ll b)
{
    return a>b ? a:b;
}
ll v[5];
void cal(ll x1,ll y1,ll x2,ll y2)
{
    int a=Max(x1,y1),b = Min(x2,y2),c = Max(x2,y2);
    v[0]=v[1]=v[2] =0;
    v[2] = (x2-x1)*(y2-y1);
    update(1,c+1,limi,v);                           //被全包围
    v[0] = 1,v[1] = -(x1+y1),v[2] = x1*y1;
    if(b > a)                                       //与正方形 右.上边同时相交的情况
        update(1,a+1,b,v);
    if(x2 < y2)                                      //只与正方形上边相交
    {
        v[0] = 0,v[1]+= (x2+y1),v[2]-= x2*y1;
    }
    else if(x2 > y2)                                 //只与正方形右边相交
    {
        v[0] = 0,v[1]+= (x1+y2),v[2]-=x1*y2;
    }
    if(a > b)    //与不同的边以不同相交 范围不一样
        b = a;
    update(1,b+1,c,v);
}




int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        ll x1,y1,x2,y2;
        build(1,1,limi);
        for(int i = 0; i < n; i++)
        {
            scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
            cal(x1,y1,x2,y2);
        }
        scanf("%d",&m);
        while(m--)
        {
            ll k;
            scanf("%I64d",&k);
            printf("%I64d\n",query(1,k));
        }
    }
    return 0;
}

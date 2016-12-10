/*
poj 1228 稳定凸包

给你n个节点构成一个凸包,问再添加节点是否能够形成新的凸包
比如： 这个点构成正方形可以看成一个不稳定凸包
 ___               ___
|   |     -->     /   |
|___|     -->     \___|

当一条边上有3个或者以上的点时,无论你怎么添加都无法改变的
当逆时针旋转的时候,凸包可以看成 每次只能左转或者直走构成的一个图形
当3个点一条线时,如果添加在凸包外面,那么它必需右转才可能经过那个点

所以我能需要求出凸包然后判断它们是否每条边上都有3个点即可
一个不错的图解：
http://www.cnblogs.com/xdruid/archive/2012/06/20/2555536.html
hhh-2016-05-07 22:17:34
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const int  maxn = 1010;
double PI = 3.1415926;
double eps = 1e-8;

int sgn(double x)
{
    if(fabs(x) < eps) return 0;
    if(x < 0)
        return -1;
    else
        return 1;
}

struct Point
{
    double x,y;
    Point() {}
    Point(double _x,double _y)
    {
        x = _x,y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator ^(const Point &b)const
    {
        return x*b.y-y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};

struct Line
{
    Point s,t;
    Line() {}
    Line(Point _s,Point _t)
    {
        s = _s;
        t = _t;
    }
    pair<int,Point> operator &(const Line&b)const
    {
        Point res = s;
        if( sgn((s-t) ^ (b.s-b.t)) == 0)   //通过叉积判断
        {
            if( sgn((s-b.t) ^ (b.s-b.t)) == 0)
                return make_pair(0,res);
            else
                return make_pair(1,res);
        }
        double ta = ((s-b.s)^(b.s-b.t))/((s-t)^(b.s-b.t));
        res.x += (t.x-s.x)*ta;
        res.y += (t.y-s.y)*ta;
        return make_pair(2,res);
    }
};
Point lis[maxn];
int Stack[maxn],top;

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}
bool cmp(Point a,Point b)
{
    double t = (a-lis[0])^(b-lis[0]);
    if(sgn(t) == 0)
    {
        return dist(a,lis[0]) <= dist(b,lis[0]);
    }
    if(sgn(t) < 0)
        return false;
    else
        return true;
}

bool Cross(Point a,Point b,Point c)
{
   return  (b.y-a.y)*(c.x-b.x) == (c.y-b.y)*(b.x-a.x);
}

void Graham(int n)
{
    Point p;

    int k = 0;
    p = lis[0];
    for(int i = 1; i < n; i++)
    {
        if(p.y > lis[i].y || (p.y == lis[i].y && p.x > lis[i].x))
            p = lis[i],k = i;
    }
    swap(lis[0],lis[k]);
    sort(lis+1,lis+n,cmp);
    if(n == 1)
    {
        top = 1;
        Stack[0] = 0;
        return ;
    }
    if(n == 2)
    {
        Stack[0] = 0,Stack[1] = 1;
        top = 2;
        return;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for(int i = 2; i < n; i++)
    {
        while(top > 1 && sgn((lis[Stack[top-1]]-lis[Stack[top-2]])
                             ^ (lis[i]-lis[Stack[top-2]])) < 0)
            top --;
        Stack[top++] = i;
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    int n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        if(n < 6)
        {
            printf("NO\n");
            continue;
        }
        Graham(n);
        int flag = 1;
        for(int i = 1;i < top-1;i++)
        {
            if(Cross(lis[Stack[i-1]],lis[Stack[i]],lis[Stack[i+1]]) == 0
               && Cross(lis[Stack[i]],lis[Stack[i+1]],lis[Stack[i+2]]) == 0)
            {
                flag = 0;
                break;
            }
        }
        if(flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}


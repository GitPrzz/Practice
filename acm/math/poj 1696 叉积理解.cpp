/*
poj 1696 叉积理解

给你n个点,要求从一个点出发,每次只能 左or直走. 求路径
先找出最做下角的点,然后通过叉积排序判断出离当前点需要旋转最小角度可以到达的点
如果两个点在一条直线上面，则选取距离最近的

hhh-2016-05-06 20:40:31
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

using namespace std;
const int  maxn = 40010;
double eps = 1e-8;
int tot;
int n,m;

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
    int id;
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
Point tp;
Point po[maxn];

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}

bool cmp(Point a,Point b)
{
    double t = (a-tp)^(b-tp);
    if(sgn(t) == 0)
    {
        return dist(a,tp) < dist(b,tp);
    }
    if(sgn(t) < 0)
        return false;
    else
        return true;
}

int main()
{
    int n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        tp.x = 10000,tp.y = 10000;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%lf%lf",&po[i].id,&po[i].x,&po[i].y);
            if(po[i].y < tp.y || (po[i].y == tp.y && po[i].x < tp.x))
            {
                tp = po[i];
            }
        }


        for(int i = 0; i < n; i++)
        {
            sort(po+i,po+n,cmp);
            tp = po[i];
        }
        printf("%d ",n);
        for(int i = 0; i < n; i++)
        {
            printf("%d%c",po[i].id, i == n-1 ? '\n':' ');
        }
    }
    return 0;
}

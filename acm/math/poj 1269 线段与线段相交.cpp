/*
poj 1269 线段与线段相交

可以通过叉积进行判断,然后计算出交点即可.

hhh-2016-05-04 20:48:26
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
const int  maxn = 40010;
double eps = 1e-8;
int tot;
int n,m;
double x1,x2,y1,y2,x3,x4,y3,y4;

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
    Point(int _x,int _y)
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
int tans[maxn];
Line line[maxn];
Point po[maxn];
Point p;
struct pair<int,Point> t;
int main()
{
    int T;
    int flag= 1;
    scanf("%d",&T);
    while(T--)
    {
        if(flag)
        printf("INTERSECTING LINES OUTPUT\n");
        flag = 0;
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        Line l1 = Line(Point(x1,y1),Point(x2,y2));
        Line l2 = Line(Point(x3,y3),Point(x4,y4));
        t = (l1&l2);
        if(t.first == 0)
            printf("LINE\n");
        else if(t.first == 1)
            printf("NONE\n");
        else
        {
            printf("POINT ");
            Point tp = t.second;
            printf("%.2f %.2f\n",tp.x,tp.y);
        }
        if(T==0)
            printf("END OF OUTPUT\n");
    }

    return 0;
}

/*
poj 3304 直线与线段相交

给你n条线段,确定是否存在一条直线，它们的投影到上面时有公共点

如果存在一个这样的直线,那么说明所有的线段能和一条直线相交
对这条直线进行一定的旋转,必定与所有直线的端点中的至少两个相交
所以枚举所有的端点进行判断即可
//注意判断相同点

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
double x1,x2,y1,y2;

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
};
int tans[maxn];
Line line[maxn];
Point po[maxn];
Point p;

bool seg_inter_line(Line l1,Line l2)
{
    return sgn((l2.s-l1.t) ^ (l1.s-l1.t))*sgn((l2.t-l1.t)^(l1.s-l1.t)) <= 0;
}

bool cal(Line tl)
{
    for(int i = 0;i < n;i++)
    {
        if(!seg_inter_line(tl,line[i]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int flag = 0;
        tot = 0;
        if(n < 3)
            flag = 1;
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            po[tot++] = Point(x1,y1);
            po[tot++] = Point(x2,y2);
            line[i] = Line(po[tot-1],po[tot-2]);
        }
        for(int i = 0; i < tot && !flag; i++)
        {
            for(int j = i+1; !flag && j < tot; j++)
            {
                if(po[i].x == po[j].x && po[i].y == po[j].y)
                    continue;
                if(cal(Line(po[i],po[j])))
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            printf("Yes!\n");
        else
            printf("No!\n");
    }
    return 0;
}

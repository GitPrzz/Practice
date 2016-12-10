/*
poj 2653 线段与线段相交

判断当前线段后面的线段是否与它相交即可

hhh-2016-05-04 22:10:50
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
const int  maxn = 200000;
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
    int operator &(const Line&b)const
    {
        if( sgn((s-t) ^ (b.s-b.t)) == 0)   //通过叉积判断
        {
            return 0;
        }
        return 1;
    }
};

bool inter(Line l1,Line l2)
{
    return
        max(l1.s.x,l1.t.x) >= min(l2.s.x,l2.t.x) &&
        max(l2.s.x,l2.t.x) >= min(l1.s.x,l1.t.x) &&
        max(l1.s.y,l1.t.y) >= min(l2.s.y,l2.t.y) &&
        max(l2.s.y,l2.t.y) >= min(l1.s.y,l1.t.y) &&
        sgn((l2.s-l1.s)^(l1.t-l1.s))*sgn((l2.t-l1.s)^(l1.t-l1.s)) <= 0 &&
        sgn((l1.s-l2.s)^(l2.t-l2.s))*sgn((l1.t-l2.s)^(l2.t-l2.s)) <= 0;
}

int tans[maxn];
Line line[maxn];

int main()
{
    while(scanf("%d",&n) && n)
    {
        memset(tans,1,sizeof(tans));

        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            line[i] = Line(Point(x1,y1),Point(x2,y2));
        }
        int num = n;
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                if(inter(line[i],line[j]))
                {
                    tans[i] = 0;
                    num--;
                    break;
                }
            }
        }
        int cur = 0;
        printf("Top sticks: ");
        for(int i = 0; i < n; i++)
        {
            if(tans[i])
            {
                cur++;
                if(num == cur)
                    printf("%d.\n",i+1);
                else
                    printf("%d, ",i+1);
            }
        }
    }
    return 0;
}

/*
hdu 4454 三分+几何

problem:
给你一个起点s,一个圆和一个矩形. 求从s出发,经过圆上面一点再到矩形上一点的距离和的最小值

solve:
因为距离满足凸性,所以三分角度来求最小值

hhh-2016-08-22 16:54:49
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
#define inf 0x3FFFFFFFFFFFFFFFLL
using namespace std;
const int maxn = 200100;
const double eps = 1e-8;
const double PI = acos(-1.0);
int sign(double d)
{
    if(d>eps)return 1;
    else if(d<-eps)return -1;
    else return 0;
}
struct Point
{
    double x,y;
    Point() {};
    Point(double _x,double _y)
    {
        x = _x,y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
    double operator ^(const Point p1)const
    {
        return x*p1.x+y*p1.y;
    }
};

struct Line
{
    Point s,t;
    Line() {};
    Line(Point a,Point b)
    {
        s= a,t = b;
    }
};

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}

Point PtLine(Point p,Line l)
{
    Point ret;
    double t = ((p-l.s)*(l.t-l.s)) / ((l.t-l.s)*(l.t-l.s));
    if(t >=0 && t <= 1)
    {
        ret.x = l.s.x + (l.t.x - l.s.x)*t;
        ret.y = l.s.y + (l.t.y - l.s.y)*t;
    }
    else
    {
        if(dist(p,l.s) < dist(p,l.t))
            ret = l.s;
        else
            ret = l.t;
    }
    return ret;
}

Point from;
Point cir,s,t;

double r;
Line l[5];
double cal(double di)
{
    Point to = Point(cir.x + r*cos(di),cir.y + r*sin(di));
    double tans = dist(from,to);
    double len = 9999999;
    for(int i = 1;i <= 4;i++)
    {
        len = min(len,dist(to,PtLine(to,l[i])));
    }
    return len+tans;
}

int main()
{
//    freopen("in.txt","r",stdin);
    double x,y;
    while(scanf("%lf%lf",&x,&y) != EOF)
    {
        if(x == 0  && y == 0)
            break;
        from = Point(x,y);
        cin >> cir.x >> cir.y >> r;
        cin >> s.x >> s.y >> t.x >> t.y;
        l[1].s.x = s.x,l[1].s.y = s.y;
        l[1].t.x = s.x,l[1].t.y = t.y;

        l[2].s.x = s.x,l[2].s.y = t.y;
        l[2].t.x = t.x,l[2].t.y = t.y;

        l[3].t.x = t.x,l[3].t.y = t.y;
        l[3].s.x = t.x,l[3].s.y = s.y;

        l[4].s.x = t.x,l[4].s.y = s.y;
        l[4].t.x = s.x,l[4].t.y = s.y;

        double m,mm;
        double l = 0,r = 2*PI;
        while(l + eps < r)
        {
            m = l+(r-l)/3;
            mm = r-(r-l)/3;
            double ans1 = cal(m);
            double ans2 = cal(mm);
            if(ans2 < ans1)
                l = m;
            else
                r = mm;
        }
        double ans =cal(l);
        printf("%.2f\n",ans);
    }
    return 0;
}

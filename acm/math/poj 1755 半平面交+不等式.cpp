/*
poj 1755 半平面交+不等式

一个比赛分三个部分,每个人在三个部分的速度为U,V,W。每个赛道的长度不一定。
现在给你n个人的情况,问他们是否能得奖

总时间 t1 = x/u1+y/v1+z/w1     t2 = x/u2+y/v2+z/w2
那么 两个人的时间差 t = t1 - t2 = ax+by+cz,判断正负即可
所以 可以看成 (a/z)x+(b/z)y+c 就成了二元方程
然后利用半平面相交计算出这些不等式最后能否得到一个>0公共区域。
如果能，则说明冠军与你有缘诶

hhh-2016-05-17 22:32:51
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
const int  maxn = 300;
const double PI = 3.1415926;
const double eps = 1e-16;
int n;
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
    double k;
    Line() {}
    Line(Point _s,Point _t)
    {
        s = _s;
        t = _t;
        k = atan2(t.y-s.y,t.x-s.x);
    }
    Point operator &(const Line &b) const
    {
        Point res = s;
        double ta = ((s-b.s)^(b.s-b.t))/((s-t)^(b.s-b.t));
        res.x += (t.x-s.x)*ta;
        res.y += (t.y-s.y)*ta;
        return res;
    }
};


//求p1,p2的直线与a,b,c这条直线的交点
Point Intersection(Point p1,Point p2,double a,double b,double c)
{
    double u = fabs(a*p1.x + b*p1.y + c);
    double v = fabs(a*p2.x + b*p2.y + c);
    Point t;
    t.x = (p1.x*v + p2.x*u)/(u+v);
    t.y = (p1.y*v + p2.y*u)/(u+v);
    return t;
}

double CalArea(Point p[],int n)
{
    double ans = 0;
    for(int i = 0; i < n; i++)
    {
        ans += (p[i]^p[(i+1)%n])/2;
    }
    return fabs(ans);
}

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}

Point p[maxn];
Point tp[maxn];
void cut(double a,double b,double c,Point p[],int &cnt)
{
    int tmp = 0;
    for(int i = 1; i <= cnt; i++)
    {
        if(a*p[i].x+b*p[i].y+c < eps) tp[++tmp] = p[i];
        else
        {
            //在p[i]处大于0,那么交点可能在(p[i-1],p[i])or(p[i+1],p[i])
            if(a*p[i-1].x + b*p[i-1].y + c < -eps)
                tp[++tmp] = Intersection(p[i-1],p[i],a,b,c);
            if(a*p[i+1].x + b*p[i+1].y + c < -eps)
                tp[++tmp] = Intersection(p[i],p[i+1],a,b,c);
        }
    }
    for(int i = 1; i <= tmp; i++)
        p[i] = tp[i];
    p[0] = p[tmp];
    p[tmp+1] = p[1];
    cnt = tmp;
}
double inf = 1000000000000000.0;
double U[maxn],V[maxn],W[maxn];
bool cal(int now)
{
    p[1] = Point(0,0);
    p[2] = Point(0,inf);
    p[3] = Point(inf,inf);
    p[4] = Point(inf,0);
    p[0] = p[4];
    p[5] = p[1];
    int cnt = 4;
    for(int i = 0; i < n; i++)
    {
        if(i == now) continue;
        double a = (U[i]-U[now])/(U[i]*U[now]);    //1/U[now] - 1/U[i]
        double b = (V[i]-V[now])/(V[i]*V[now]);
        double c = (W[i]-W[now])/(W[i]*W[now]);
        if(sgn(a)==0 && sgn(b) == 0 )
        {
            if(sgn(c) >= 0)
            return false;
            else
                continue;
        }
        cut(a,b,c,p,cnt);
    }
    if(sgn(CalArea(p,cnt)) == 0)
        return false;
    else
        return true;
}

int main()
{
   // freopen("in.txt","r",stdin);
    while(scanf("%d",&n)!= EOF)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf",&U[i],&V[i],&W[i]);
        }
        for(int i = 0; i < n; i++)
        {
            if(cal(i))
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}

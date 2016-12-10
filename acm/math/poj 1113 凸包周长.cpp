/*
poj 1113 凸包周长

给你一些点组成的城堡,要求用最少的墙围起来,且墙距离城堡有一定距离
当城堡有转角时,毫无疑问墙建成圆弧的最合适
假设一个转角内角为x，那么圆弧的角度就是180-x度
所以最终形成圆弧角度就是 n*180 - 多边形内角和 = 360
对于凹陷下去的地方而言, 很明显直线更短. 所以求个凸包
ans=凸包周长+圆周长

hhh-2016-05-06 21:51:48
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
double PI = 3.1415926;
double eps = 1e-8;
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
        top = 2,Stack[0] = 0,Stack[1] = 1;
        return ;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for(int i = 2; i < n; i++)
    {
        while(top > 1 && sgn((lis[Stack[top-1]]-lis[Stack[top-2]])
                             ^ (lis[i]-lis[Stack[top-2]])) <= 0)
            top --;
        Stack[top++] = i;
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    double len;
    while(scanf("%d%lf",&n,&len) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        Graham(n);
        double ans = 0;
        //cout << top <<endl;
        for(int i = 0; i < top; i++)
        {
            if(i == top-1)
                ans += dist(lis[Stack[i]],lis[Stack[0]]);
            else
                ans += dist(lis[Stack[i]],lis[Stack[i+1]]);
        }
        ans +=  2*PI*len;
        printf("%.0f\n",ans);
    }
    return 0;
}

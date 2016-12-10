/*
poj 1265 Area 面积+多边形内点数

给你初始点以及每次走的方向,可以得到n个点的集合.然后计算这个多边的面积,多边形
内部包含的点数以及多边形边上的点数

因为多边形顶点都是整点,所以通过皮克定理可以得出其面积S和内部格点数目i、
边上格点数目j的关系：S = i + j/2 - 1.
所以我们可以先计算出多边的面积. 多边形边上的点数j满足一个GCD关系,可以求出
于是便能得到i

hhh-2016-05-08 20:01:56
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
const int  maxn = 10100;
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

int GCD(int a,int b)
{
    if(a < b)swap(a,b);
    if(b == 0)
        return a;
    while(a % b)
    {
        int t = a%b;
        a = b;
        b = t;
    }
    return b;
}

int main()
{
   // freopen("in.txt","r",stdin);
    int n,T;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double x=0,y=0;
        double x1,y1;
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&x1,&y1);
            lis[i].x = x+x1;
            lis[i].y = y+y1;
            x = lis[i].x;
            y = lis[i].y;
        }
        printf("Scenario #%d:\n",cas++);
        double res = 0;
        for(int i = 0;i < n;i++)
        {
            res += (lis[i]^lis[(i+1)%n])/2;
        }
        int Onum = 0;
        for(int i = 0;i < n;i++)
        {
            int tx = abs(lis[i].x - lis[(i+1)%n].x);
            int ty = abs(lis[i].y - lis[(i+1)%n].y);
            Onum += GCD(tx,ty);
        }
        int Inum = res*2+2-Onum;
        printf("%d %d %.1f\n\n",Inum/2,Onum,res);
    }
    return 0;
}


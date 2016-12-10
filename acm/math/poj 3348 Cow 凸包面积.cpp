/*
poj 3348 Cow 凸包面积

给你n棵树绕成一个圈,问最多可以养多少牛
用所有点求出凸包然后求出多边形的面积即可

hhh-2016-05-08 18:47:21
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
                             ^ (lis[i]-lis[Stack[top-2]])) <= 0)
            top --;
        Stack[top++] = i;
    }
}

int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        Graham(n);

        double res = 0;
        for(int i = 0;i < top;i++)
        {
            res += (lis[Stack[i]]^lis[Stack[(i+1)%top]])/2;
        }
        int ans = res;
        printf("%d\n",ans/50);
    }
    return 0;
}


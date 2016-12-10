/*
poj 1279 半平面交核面积

给你一个多边形的图书馆.要求得到一块地方能看见墙上所有的点,并求出面积
在半平面模板上加个求面积公式即可.
而且输入并没有指定顺时针还是逆时针,可以通过求面积进行判断.

hhh-2016-05-11 21:01:47
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
const int  maxn = 1510;
const double PI = 3.1415926;
const double eps = 1e-8;

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

bool HPIcmp(Line a,Line b)
{
    if(fabs(a.k-b.k) > eps) return a.k<b.k;
    return ((a.s-b.s)^(b.t-b.s)) < 0;
}
Line li[maxn];

double CalArea(Point p[],int n)
{
    double ans = 0;
    for(int i = 0;i < n;i++)
    {
        ans += (p[i]^p[(i+1)%n])/2;
    }
    return ans;
}

double  HPI(Line line[],int n,Point res[],int &resn)
{
    int tot =n;
    sort(line,line+n,HPIcmp);
    tot = 1;
    for(int i = 1; i < n; i++)
    {
        if(fabs(line[i].k - line[i-1].k) > eps)
            line[tot++] = line[i];
    }
    int head = 0,tail = 1;
    li[0] = line[0];
    li[1] = line[1];
    resn = 0;
    for(int i = 2; i < tot; i++)
    {
        if(fabs((li[tail].t-li[tail].s)^(li[tail-1].t-li[tail-1].s)) < eps||
                fabs((li[head].t-li[head].s)^(li[head+1].t-li[head+1].s)) < eps)
            return 0;
        while(head < tail && (((li[tail] & li[tail-1]) - line[i].s) ^ (line[i].t-line[i].s)) > eps)
            tail--;
        while(head < tail && (((li[head] & li[head+1]) - line[i].s) ^ (line[i].t-line[i].s)) > eps)
            head++;
        li[++tail] = line[i];
    }
    while(head < tail && (((li[tail] & li[tail-1]) - li[head].s) ^ (li[head].t-li[head].s)) > eps)
        tail--;
    while(head < tail && (((li[head] & li[head-1]) - li[tail].s) ^ (li[tail].t-li[tail].t)) > eps)
        head++;
    if(tail <= head+1)
        return 0;
    for(int i = head; i < tail; i++)
        res[resn++] = li[i]&li[i+1];
    if(head < tail-1)
        res[resn++] = li[head]&li[tail];

    double tans = 0;
    for(int i = 0;i < resn;i++)
    {
        tans += (res[i]^res[(i+1)%resn])/2;
    }
    return fabs(tans);
}
Point p0;
Point lis[maxn];
Line line[maxn];
double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}

bool cmp(Point a,Point b)
{
    double t = (a-p0)^(b-p0);
    if(sgn(t) > 0)return true;
    else if(sgn(t) == 0 && sgn(dist(a,lis[0])-dist(b,lis[0])) <= 0)
        return true;
    else
        return false;
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
        int ans;
        if(CalArea(lis,n) < 0)
            reverse(lis,lis+n);
        for(int i = 0; i < n; i++)
        {
            line[i] = Line(lis[i],lis[(i+1)%n]);
        }
        printf("%.2f\n",HPI(line,n,lis,ans));
    }
    return 0;
}

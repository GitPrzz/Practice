/*
poj 3384

给你一个多边形,然后往里面放两个圆,问能够占的最大面积.
即相当于在能够放下两个圆的情况下使圆形离得尽可能的远.

如果将多边形的每条边往里面平移半径的长度R.那么剩下的多边形就是圆心的取点范围
然后在这个基础上枚举点即可.

主要是通过剩下的这些线段构成一个新的多边形,然后枚举它的顶点即可。
但是平移后的多边形的边的长度莫有变诶,所以可以看成多条直线围成的多边形。
那么就成了半平面交问题(即给你直线和图形在这条直线的哪一边,然后构成的多边形)

hhh-2016-05-17 19:55:56
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
const double eps = 1e-10;

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
    for(int i = 0; i < n; i++)
    {
        ans += (p[i]^p[(i+1)%n])/2;
    }
    return ans;
}

double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}


void HPI(Line line[],int n,Point res[],int &resn)
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
            return;
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
        return;
    for(int i = head; i < tail; i++)
        res[resn++] = li[i]&li[i+1];
    if(head < tail-1)
        res[resn++] = li[head]&li[tail];
    double Mans = -1;
    int ansi,ansj;
    for(int i = 0; i < resn; i++)
    {
        for(int j = 0; j < resn; j++)
            if( sgn(dist(res[i],res[j])-Mans) >= 0)
            {
                Mans = dist(res[i],res[j]) ;
                ansi = i,ansj = j;
            }
    }
    printf("%.4f %.4f %.4f %.4f\n",res[ansi].x,res[ansi].y,res[ansj].x,res[ansj].y);
}
Point p0;
Point lis[maxn];
Line line[maxn];
bool cmp(Point a,Point b)
{
    double t = (a-p0)^(b-p0);
    if(sgn(t) > 0)return true;
    else if(sgn(t) == 0 && sgn(dist(a,lis[0])-dist(b,lis[0])) <= 0)
        return true;
    else
        return false;
}

Point ta,tb;
Point tans[maxn];
void fin(Point a,Point b,double mid)
{
    double len = dist(a,b);
    double dx = (a.y-b.y)*mid/len;
    double dy = (b.x-a.x)*mid/len;
    ta.x = a.x+dx,ta.y = a.y+dy;
    tb.x = b.x+dx,tb.y = b.y+dy;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    double  r;
    while(scanf("%d%lf",&n,&r)!= EOF)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        reverse(lis,lis+n);
        for(int i = 0; i < n; i++)
        {
            fin(lis[i],lis[(i+1)%n],r);
            line[i] = Line(ta,tb);
        }
        int resn;
        HPI(line,n,tans,resn);
    }
    return 0;
}

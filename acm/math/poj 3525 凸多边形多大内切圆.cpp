/*
poj 3525 凸多边形多大内切圆

给你一个凸多边形的小岛地图,求出岛中到海岸线的最远距离。
相当于求多边形中最大的内切圆的半径,但是想了很久并没有发现什么方法 卒

问题可以转化成能够在多边形中找到一个圆。也就是二分多边形缩小的长度,然后
判断当前能否找到一个圆。
如果存在一个圆的话,那么它的圆心肯定是这个凸多边形的核。所以可以通过二分
和半平面相交判断解决
hhh-2016-05-11 22:10:56
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
    for(int i = 0; i < n; i++)
    {
        ans += (p[i]^p[(i+1)%n])/2;
    }
    return ans;
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

Point ta,tb;
Point fans[maxn];
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
    int n,T;
    while(scanf("%d",&n)!= EOF && n)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        int ans;
        double l=0,r=100000;
        double tans = 0;
        while(r - l > eps)
        {
            double mid = (l+r) /2;
            for(int i = 0; i < n; i++)
            {
                fin(lis[i],lis[(i+1)%n],mid);
                line[i] = Line(ta,tb);
            }
            HPI(line,n,fans,ans);
            if(ans)
                l = mid+eps,tans = mid;
            else
                r = mid-eps;
        }
        printf("%.6f\n",tans);
    }
    return 0;
}

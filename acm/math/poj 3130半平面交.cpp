/*
poj 3130 How I Mathematician Wonder What You Are!

每次给你一个形状判断它是否是一个星星
如果是一个星星,那么它一定存在一个点使图形内所有点与它的连线都在图形类
即是否有一个点能观察到图形的所有位置

hhh-2016-05-11 20:28:01
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
const int  maxn = 1010;
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

int main()
{
  //  freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n) != EOF && n)
    {
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf",&lis[i].x,&lis[i].y);
        }
        int ans;
        for(int i = 0; i < n; i++)
        {
            line[i] = Line(lis[i],lis[(i+1)%n]);
        }
        HPI(line,n,lis,ans);
        if(ans)
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}

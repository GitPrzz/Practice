/*
poj 2318 叉积+二分

一个矩形，有被若干直线分成N个格子，给出一个点的坐标，问你该点位于哪个点中。
知识点：其实就是点在凸四边形内的判断，若利用叉积的性质，可以二分求解。

叉积的结果也是一个向量，是垂直于向量a，b所形成的平面，如果看成三维坐标的话是在 z 轴上，上面结果是它的模。
方向判定：右手定则，（右手半握，大拇指垂直向上，四指右向量a握向b，大拇指的方向就是叉积的方向）
叉积的意义：
1：其结果是a和b为相邻边形成平行四边形的面积。
2：结果有正有负，有sin（a，b）可知和其夹角有关，夹角大于180°为负值。

hhh-2016-05-04 19:49:26
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int  maxn = 40010;
int tot;
int mod;
int n,m;
int x1,x2,y1,y2;

struct Point
{
    int x,y;
    Point() {}
    Point(int _x,int _y)
    {
        x = _x,y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    int operator ^(const Point &b)const
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
};
int tans[maxn];
Line line[maxn];
Point p;
int cal(int mid)
{
    return (line[mid].t-p)^(line[mid].s-p);
}

int main()
{
    int flag = 1;
    while(scanf("%d",&n) && n)
    {
        if(!flag)
            printf("\n");
        scanf("%d%d%d%d%d",&m,&x1,&y1,&x2,&y2);
        flag = 0;
        line[n] = Line(Point(x2,y1),Point(x2,y2));
        memset(tans,0,sizeof(tans));
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d",&x1,&x2);
            line[i] = Line(Point(x1,y1),Point(x2,y2));
        }
        while(m--)
        {
            scanf("%d%d",&x1,&y1);
            int l = 0, r = n;
            int mid,ans;
            p = Point(x1,y1);
            while(l <= r)
            {
                mid = (l+r)>>1;
                if(cal(mid) > 0)
                {
                    ans = mid;
                    r = mid-1;
                }
                else
                {
                    l = mid+1;
                }
            }
            tans[ans]++;
        }
        for(int i = 0; i <= n; i++)
        {
            printf("%d: %d\n",i,tans[i]);
        }
    }
    return 0;
}

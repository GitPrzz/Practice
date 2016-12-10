/*
poj 1873 凸包+枚举

给你n棵树,已知树的树的长度以及他们的价值。要砍掉一些树来给剩下的数围一个篱笆
要求剩下的数价值尽可能大,如果价值相同则希望剩下的树尽可能多

因为最多15棵,枚举需要砍掉的树,然后通过凸包判断是否能围成,记录一下即可

hhh-2016-05-07 21:27:41
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
const int  maxn = 20;
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
Point ta[20];
bool cmp(Point a,Point b)
{
    double t = (a-ta[0])^(b-ta[0]);
    if(sgn(t) == 0)
    {
        return dist(a,ta[0]) <= dist(b,ta[0]);
    }
    if(sgn(t) < 0)
        return false;
    else
        return true;
}

int tot;
double Graham(int n)
{
    Point p;
    if(n == 1 || n == 0)
    {
        return 0;
    }
    if(n == 2)
    {
        return dist(ta[0],ta[1])*2;
    }
    int k = 0;
    p = ta[0];
    for(int i = 1; i < n; i++)
    {
        if(p.y > ta[i].y || (p.y == ta[i].y && p.x > ta[i].x))
            p = ta[i],k = i;
    }
    swap(ta[0],ta[k]);
    sort(ta+1,ta+n,cmp);
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for(int i = 2; i < n; i++)
    {
        while(top > 1 && sgn((ta[Stack[top-1]]-ta[Stack[top-2]])
                             ^ (ta[i]-ta[Stack[top-2]])) <= 0)
            top --;
        Stack[top++] = i;
    }
    double len = 0;
    for(int i = 0; i < top; i++)
    {
        if(i == top - 1)
            len += dist(ta[Stack[i]],ta[Stack[0]]);
        else
            len += dist(ta[Stack[i]],ta[Stack[i+1]]);
    }
    return len;
}

int val[maxn];
double lent[maxn];

int main()
{
    //freopen("in.txt","r",stdin);
    int n;
    int cas = 1;
    while(scanf("%d",&n) && n)
    {
        if(cas != 1)
            printf("\n");
        for(int i = 0; i < n; i++)
        {
            scanf("%lf%lf%d%lf",&lis[i].x,&lis[i].y,&val[i],&lent[i]);
        }
        int ansV = 0x7fffffff,ansN = 0x7fffffff,ansX = 0;
        double ansL = 0;
        for(int i = 0; i < (1<<n); i++)
        {
            tot = 0;
            double lans = 0;
            int vans = 0;
            for(int j = 0; j < n; j++)
            {
                if(i & (1 << j))
                {
                    vans += val[j];
                    lans += lent[j];
                }
                else
                {
                    ta[tot++] = lis[j];
                }
            }
            if(vans > ansV)
                continue;
            double t = Graham(tot);
            if(lans >= t)
            {
                if(vans < ansV || (n-tot < ansN && vans == ansV))
                {
                    ansV = vans;
                    ansL = lans-t;
                    ansX = i;
                    ansN = n-tot;
                }
            }
        }
        printf("Forest %d\n",cas++);
        printf("Cut these trees:");
        for(int i = 0; i < n; i++)
        {
            if(ansX&(1 << i))
                printf(" %d",i+1);
        }
        printf("\n");
        printf("Extra wood: %.2f\n",ansL);
    }
    return 0;
}


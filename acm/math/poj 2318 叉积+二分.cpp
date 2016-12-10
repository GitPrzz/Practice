/*
poj 2318 ���+����

һ�����Σ��б�����ֱ�߷ֳ�N�����ӣ�����һ��������꣬����õ�λ���ĸ����С�
֪ʶ�㣺��ʵ���ǵ���͹�ı����ڵ��жϣ������ò�������ʣ����Զ�����⡣

����Ľ��Ҳ��һ���������Ǵ�ֱ������a��b���γɵ�ƽ�棬���������ά����Ļ����� z ���ϣ�������������ģ��
�����ж������ֶ��򣬣����ְ��գ���Ĵָ��ֱ���ϣ���ָ������a����b����Ĵָ�ķ�����ǲ���ķ���
��������壺
1��������a��bΪ���ڱ��γ�ƽ���ı��ε������
2����������и�����sin��a��b����֪����н��йأ��нǴ���180��Ϊ��ֵ��

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

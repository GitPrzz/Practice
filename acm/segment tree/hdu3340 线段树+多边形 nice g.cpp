/*
hdu3340 线段树+多边形 nice g
R x:表示在这有个x边形
Q l r：查询在[l,r]之间的多边形的面积

所以考虑用线段树解决，那么我们就要知道如何处理区间的面积，对于一个多边形，
它的每一条边都可以在两端作垂直于x轴的垂线然后形成一个梯形，于是用图形
上半部分的边形成的梯形和- 半部分的边形成的梯形和便能得到多边形面积。
而且两个同高的梯形的面积和等同于上底和下底的叠加

hhh-2016-03-02 20:54:04	Accepted
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 500200;
map<int,int>has;
vector<int> tp;
char op[10];

struct node
{
    int l,r;
    int mid()
    {
        return l+(r-l)/2;
    }
    double h1,h2,k,len;
    double area;
} tree[maxn];

void push_up(int r)
{
    tree[r].area = tree[r<<1].area+tree[r<<1|1].area;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].h1 = tree[i].h2 = tree[i].k = tree[i].area = 0;
    tree[i].len = tp[r]-tp[l];
    if(l == r) return;
    if(l+1 != r)
    {
        build(i<<1,l,tree[i].mid());
        build(i<<1|1,tree[i].mid(),r);
        push_up(i);
    }
}

void push_down(int i)
{
    int lson = i<<1,rson =i<<1|1;
    double h1=tree[i].h1,h2=tree[i].h2,k=tree[i].k;
    double md = (tp[tree[i].mid()]-tp[tree[i].l])*k+h1;

    tree[lson].h1+=h1,tree[lson].h2+=md,tree[lson].k+=k;
    tree[lson].area += (h1+md)*tree[lson].len/2;

    tree[rson].h1+=md,tree[rson].h2+=h2,tree[rson].k+=k;
    tree[rson].area += (md+h2)*tree[rson].len/2;

    tree[i].h1 = tree[i].h2 = tree[i].k = 0;
}

void update(int i,int l,int r,double h1,double h2,double k)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].h1+=h1,tree[i].h2+=h2,tree[i].k+=k;
        tree[i].area += (h1+h2)*tree[i].len/2;
        return ;
    }
    push_down(i);
    double md= (tp[tree[i].mid()]-tp[l])*k+h1;
    if(r <= tree[i].mid())
        update(i<<1,l,r,h1,h2,k);
    else if(l >= tree[i].mid())
        update(i<<1|1,l,r,h1,h2,k);
    else
    {
        update(i<<1,l,tree[i].mid(),h1,md,k);
        update(i<<1|1,tree[i].mid(),r,md,h2,k);
    }
    push_up(i);
}

double query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].area;
    }
    push_down(i);
    double ans = 0;
    if(l < tree[i].mid())
        ans += query(i<<1,l,r);
    if(tree[i].mid() < r)
        ans += query(i<<1|1,l,r);
    push_up(i);
    return ans;
}

struct point
{
    int x[6],y[6];
    int num;
    void get()
    {
        num = 0;
        scanf("%s",op);
        if(op[0] == 'R')
        {
            scanf("%d",&num);
            for(int i = 0; i < num; i++)
            {
                scanf("%d%d",&x[i],&y[i]);
                tp.push_back(x[i]);
            }
        }
        else
        {
            scanf("%d%d",&x[1],&y[1]);
            tp.push_back(x[1]);
            tp.push_back(y[1]);
        }
    }
} Point[50010];

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        tp.clear(),has.clear();
        scanf("%d",&n);
        for(int i =1;i <= n;i++)
        {
            Point[i].get();
        }

        sort(tp.begin(),tp.end());
        tp.erase(unique(tp.begin(),tp.end()),tp.end());
        for(int i = 0;i < (int)tp.size();i++)
            has[tp[i]] = i;
        build(1,0,tp.size()-1);
        for(int i =1;i <= n;i++)
        {
            if(Point[i].num)
            {
                for(int j = 0;j < Point[i].num;j++)
                {
                    int num = Point[i].num;
                    int x1=Point[i].x[j],y1=Point[i].y[j];
                    int x2=Point[i].x[(j+1)%num],y2=Point[i].y[(j+1)%num];
                    if(x1 > x2)swap(x1,x2),swap(y1,y2);
                    else y1=-y1,y2=-y2;
                    double k = (1.0*y1-1.0*y2)/(1.0*x1-1.0*x2);
                    update(1,has[x1],has[x2],y1,y2,k);
                   // printf("%.3f\n",query(1,has[1],has[100]));
                }
            }
            else
            {
                int x = Point[i].x[1];
                int y = Point[i].y[1];
                printf("%.3f\n",query(1,has[x],has[y]));
            }
        }
    }
    return 0;
}

/*
hdu 1542 �߶���ɨ��(���)

����n������,�������γɵ�ͼ�ε������С

���ݲ�һ��������,�����ȶ����ǽ�����ɢ������
���¾���ÿ�μ���ƽ����x�������������֮������,�����Ѿ�֪��������ƽ��
��֮��ĸ߶ȣ����Ǿ�ת�������ǰ�����ӳ�䵽x���ϵ��߶εĳ���,�������
�����߶��������

�Ȱ�����ƽ����x����߶ΰ��߶�����,Ȼ���������,ÿ�������������±�ʱ��
[l,r]�ϼ�1��ʾ�߶θ���,�����ϱ�������-1����Ӱ��.Ȼ��ÿ�μ��㸲�ǳ���
�ٳ��ϸ߼���

�ο�(ͼ�����)��
http://www.cnblogs.com/scau20110726/archive/2013/04/12/3016765.html

hhh-2016-03-26 17:58:50
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int maxn = 10005;
double hs[maxn];
struct node
{
    int l,r;
    double len;
    int sum;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];

void push_up(int i)
{
    if(tree[i].sum)
    {
        tree[i].len = (hs[tree[i].r+1]-hs[tree[i].l]);
    }
    else if(tree[i].l == tree[i].r)
    {
        tree[i].len= 0;
    }
    else
    {
        tree[i].len = tree[lson].len+tree[rson].len;
    }
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = tree[i].len = 0;
    if(l == r)
        return ;

    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <=r )
    {
        tree[i].sum += val;
        push_up(i);
        return ;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
}

struct edge
{
    double l,r,high;
    int va;
    edge() {};
    edge(double _l,double _r,double _high,int _va):l(_l),r(_r),high(_high),va(_va)
    {}
};
edge tx[maxn*2];

bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}
int tot,m;
int fin(double x)
{
    int l = 0,r = m-1;
    while(l <= r)
    {
        int mid = (l+r)>>1;
        if(hs[mid] == x)
            return mid;
        else if(hs[mid] < x)
            l = mid+1;
        else
            r = mid-1;
    }
}

int main()
{
    int n;
    int cas =1;
    while(scanf("%d",&n) != EOF && n)
    {
        double x1,x2,y1,y2;
        tot = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            hs[tot] = x1;
            tx[tot++] = edge(x1,x2,y1,1);
            hs[tot] = x2;
            tx[tot++] = edge(x1,x2,y2,-1);
        }
        sort(tx,tx+tot,cmp);
        sort(hs,hs+tot);
        m = 1;
        for(int i = 1;i < tot;i++)
        {
            if(hs[i] != hs[i-1])
                hs[m++] = hs[i];
        }
        build(1,0,m);
        double ans = 0;
        for(int i = 0;i < tot;i++)
        {
            int l = fin(tx[i].l);
            int r = fin(tx[i].r)-1;

            Insert(1,l,r,tx[i].va);
            ans += (tree[1].len)*(tx[i+1].high-tx[i].high);
            //cout << ans <<endl;
        }
        printf("Test case #%d\n",cas++);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}

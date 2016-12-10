/*
hdu 1255 ���ǵ����(�󸲸������������ϵ����)

��Ҫ����push_up�ǳ���������
�趨len�Ǹ����������ϵĳ��ȣ�len1�Ǹ���1�����ϵĳ���
��ô�����¼��������
1.sum>1 ��˵��ǰ���䱻������������
2.l == r  ֱ��Ϊ0
3.��ǰ����һ�ζ�û�����ǹ� lson.len + rson.len
4.��ǰ���䱻���ǹ�һ��sum=1,��ô  lson.len1 + rson.len1�������Һ����б�
���ٸ��ǹ�һ�εĺ�

hhh-2016-03-27 18:07:36
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
const int maxn = 50050;
struct node
{
    int l,r,sum;
    double len;
    double len1;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];
double hs[maxn];
int tot,m;
void push_up(int i)
{
    if(tree[i].sum)
        tree[i].len1 = hs[tree[i].r+1]-hs[tree[i].l];
    else if(tree[i].l == tree[i].r)
        tree[i].len1 = 0;
    else
        tree[i].len1 = tree[lson].len1+tree[rson].len1;

    if(tree[i].sum > 1)
        tree[i].len = hs[tree[i].r+1]-hs[tree[i].l];
    else if(tree[i].l == tree[i].r)
        tree[i].len = 0;
    else if(tree[i].sum == 1)
        tree[i].len = tree[lson].len1 + tree[rson].len1;
    else
        tree[i].len = tree[lson].len+tree[rson].len;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].sum=tree[i].len= 0;
    tree[i].len1 = 0;
    if(l ==r )
    {
        return ;
    }
    int mid=tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].sum += val;
        push_up(i);
        return;
    }
    push_down(i);
    int mid = tree[i].mid();
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
    edge(double ll,double rr,double h,int v):l(ll),r(rr),high(h),va(v) {}
} tx[maxn];

bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}

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
    int n,x,q,t;
    int cas =1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        tot = 0;
        double x1,x2,y1,y2;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            hs[tot] = x1;
            tx[tot++] = edge(x1,x2,y1,1);
            hs[tot] = x2;
            tx[tot++] = edge(x1,x2,y2,-1);
        }
        sort(hs,hs+tot);
        sort(tx,tx+tot,cmp);
        m = 1;
        for(int i = 1; i < tot; i++)
            if(hs[i] != hs[i-1])
                hs[m++] = hs[i];
        build(1,0,m-1);
        double ans = 0;
        for(int i = 0;i < tot;i++)
        {
            int l = fin(tx[i].l);
            int r = fin(tx[i].r)-1;
            //cout << tx[i].l <<" " << tx[i].r <<" "<<endl;
            Insert(1,l,r,tx[i].va);
            ans += tree[1].len*(tx[i+1].high-tx[i].high);
        }
        printf("%.2f\n",ans);
    }
    return 0;
}

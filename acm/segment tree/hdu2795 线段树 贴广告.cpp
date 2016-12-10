/*
hdu2795 �߶��� �����
��һ��h*w�Ĺ���������棬ÿ�ι��Ĵ�СΪ1*wi
Ҫ��ÿ�ξ��������ĸߣ�Ȼ������ÿ�ι������һ��
h��w��Ϊ10^9�������ܹ�ֻ��200000����棬ÿ�ι�����վһ�У�����h=min(h,q)��
�������Ĵ�С����ʹ���߶�����ÿ���ȼ���ܹ����룬Ȼ��������λ���ϼ��ϼ���
hhh-2016-02-29 10:42:10
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <queue>
#include <map>
#include <vector>
typedef long long ll;
using namespace std;
const int maxn = 200000+5;
ll h,w;
struct node
{
    int l,r;
    ll Min;
} tree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    tree[r].Min = min(tree[lson].Min,tree[rson].Min);
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Min  = 0;
    if(l == r)
    {
        return ;
    }
    int mid = (l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    push_up(i);
}
void push_down(int r)
{

}

void Insert(int i,ll k)
{
    if(tree[i].l == tree[i].r)
    {
        tree[i].Min += (ll)k;
        printf("%d\n",tree[i].l);
        return ;
    }
    push_down(i);
    ll M1 = tree[i<<1].Min;
    //ll M2 = tree[i<<1|1].Min;
    if(w-M1 >= k) Insert(i<<1,k);
    else Insert(i<<1|1,k);
    push_up(i);
}

int main()
{
    ll q;
    while(scanf("%I64d%I64d%I64d",&h,&w,&q)!=EOF)
    {
        h = min(h,q);
        build(1,1,h);
        ll x;
        for(int i =1; i <= q; i++)
        {
            scanf("%I64d",&x);
            if(w-tree[1].Min>=x)
                Insert(1,x);
            else
                printf("-1\n");
        }
    }
    return 0;
}


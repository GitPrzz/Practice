/*
hdu 4533 �߶���(����ת��+)

��֪��n�����δ���,����ˮ��ԭ�㿪ʼ����,t��ʱ(0,0)->(t,t)�ķ�Χ�ڻ���˯
����m��ѯ��,xʱ�䴲��ʪ�����

�ʼ�����ɨ����,�о��е���������ظ�����Ĳ��֡��������˻ᷢ��ɨ�����Ǵ�
�����ϵ��Ƴ�����,��������Ҫ����(x,x)������η�Χ�ڵ����,������ͨ��һ��query���,�� Orz

Ȼ���ȥĤ�ݴ�����TAT
����һ�����δ���(x1,y1,x2,y2)���������ȫ�������Ҳ����(x2-x1)*(y2-y1).���������һ����Ҳ����
(t-x1)*(t-y1)(tΪ�����εı߳�).
���Ǹ��Ƿ�ʽ�кü���
 1.max(x1,y1)<=t<=min(x2,y2):�������ε�ֱ�ǵľ�����
 ->s=(t-x1)*(t-y1)=t*t-(x1+y1)*t+x1*y1
 2.min(x2,y2)<=t<=max(x2,y2):����ֻ���ϱ��ཻ(��ͼ)
 s=(t-x1)*(t-y1) - (t-x2)*(t-y1) = (-x1-y1+x2+y1)*t+(x1*y1-x2*y1)
      _
 ____|_|_
|    | | |
|    |_| |
|        |
|________|
ֻ���������ұ��ཻ�ұߵ����ͬ��....

���Է�������������ʽ������ת���� A*t*t+B*t+C(һ������t�Ĺ�ʽ)
��һ��λ�õ�t����,��ͨ�Ĵ����������һ����ͬA,B,Cϵ��,�����ǿ��ԼӼ����ӵ�
���ǾͿ��������߶�������ÿ��t��Ӧ��ϵ��,Ȼ������query����һ�¾��ܽ����
��ת��Ҳ�Ǹ����� �r(�s_�t)�q

����������Ҫͨ���ж���ȷ���������ʺ�t�ķ�Χ,���2�Ͳ����ܳ�������������.�ұ�ͬʱ
�ཻ�������
�ֵ����ཻ���ԣ�
ͼ1(x2,y2)        ͼ2(y1,y2)
t1=max(x1,y1)    t2=(min(x2,y2))   ->max(t1,t2)~max(x2,y2)
      _              _
     | |            | |
 ____|_|         ___|_|__
|    |_|        |        |
|      |        |        |
|______|        |        |
                |________|
�ο���http://blog.csdn.net/zkfzkfzkfzkfzkfzkfzk/article/details/8738504
hhh-2016-04-03 17:22:44
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
const int mod = 1e8+7;
const int maxn = 200050;
int limi = 200000;

struct node
{
    int l,r;
    ll A,B,C;
    int mid()
    {
        return (l+r)>>1;
    }
    int len()
    {
        return (r-l+1) ;
    }
} tree[maxn<<2];

void update_up(int i)
{

}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].A = tree[i].B = tree[i].C = 0;
    if(l == r)
        return ;
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    update_up(i);
}

void update_down(int i)
{
    tree[lson].A+=tree[i].A,tree[rson].A+=tree[i].A;
    tree[lson].B+=tree[i].B,tree[rson].B+=tree[i].B;
    tree[lson].C+=tree[i].C,tree[rson].C+=tree[i].C;
    tree[i].A = tree[i].B = tree[i].C = 0;
}

void update(int i,int l,int r,ll *va)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].A += va[0],tree[i].B += va[1],tree[i].C += va[2];
        return ;
    }
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,va);
    if(r > mid)
        update(rson,l,r,va);
    update_up(i);
}

ll query(int i,ll k)
{
    if(tree[i].l == tree[i].r)
    {
        return (ll)tree[i].A*k*k+tree[i].B*k+tree[i].C;
    }
    int mid = tree[i].mid();
    update_down(i);
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}
ll Min(ll a,ll b)
{
    return a<b ? a:b;
}

ll Max(ll a,ll b)
{
    return a>b ? a:b;
}
ll v[5];
void cal(ll x1,ll y1,ll x2,ll y2)
{
    int a=Max(x1,y1),b = Min(x2,y2),c = Max(x2,y2);
    v[0]=v[1]=v[2] =0;
    v[2] = (x2-x1)*(y2-y1);
    update(1,c+1,limi,v);                           //��ȫ��Χ
    v[0] = 1,v[1] = -(x1+y1),v[2] = x1*y1;
    if(b > a)                                       //�������� ��.�ϱ�ͬʱ�ཻ�����
        update(1,a+1,b,v);
    if(x2 < y2)                                      //ֻ���������ϱ��ཻ
    {
        v[0] = 0,v[1]+= (x2+y1),v[2]-= x2*y1;
    }
    else if(x2 > y2)                                 //ֻ���������ұ��ཻ
    {
        v[0] = 0,v[1]+= (x1+y2),v[2]-=x1*y2;
    }
    if(a > b)    //�벻ͬ�ı��Բ�ͬ�ཻ ��Χ��һ��
        b = a;
    update(1,b+1,c,v);
}




int main()
{
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        ll x1,y1,x2,y2;
        build(1,1,limi);
        for(int i = 0; i < n; i++)
        {
            scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
            cal(x1,y1,x2,y2);
        }
        scanf("%d",&m);
        while(m--)
        {
            ll k;
            scanf("%I64d",&k);
            printf("%I64d\n",query(1,k));
        }
    }
    return 0;
}

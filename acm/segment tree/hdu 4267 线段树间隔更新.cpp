/*
hdu 4267 �߶����������
A Simple Problem with Integers

��������������
1.��[l,r]��(i-l)%k==0��������val
2.������ֵ

�������뵽����������һ�������͵���Ŀ,���������k�ǲ��̶���
���Բ�������

����ÿ����,�����k�����������Ǳ��,���Էֳ�k��,����k������ܹ�55��,
������add[55]����������ӵ�ֵ.
Ȼ���ڲ���pos��ʱ��,���϶���ÿ��k����pos�������ֵ����

hhh-2016-03-26 13:47:26
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
int n,qw;
int k;
const int maxn = 50050;
int po[15][15];
int a[maxn];
struct node
{
    int l,r;
    int sum;
    int add[56];
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];



void push_up(int i)
{

}

void build(int l,int r,int i)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = 0;
    memset(tree[i].add,0,sizeof(tree[i].add));
    if(l == r)
        return ;

    int mid = tree[i].mid();
    build(l,mid,lson);
    build(mid+1,r,rson);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].sum)
    {
        tree[lson].sum += tree[i].sum;
        tree[rson].sum += tree[i].sum;

        for(int j = 0; j < 55; j++)
        {
            tree[lson].add[j]+= tree[i].add[j];
            tree[rson].add[j]+= tree[i].add[j];
            tree[i].add[j] = 0;
        }
        tree[i].sum = 0;
    }
}
void Insert(int i,int l,int r,int val,int k,int t)
{
    if(tree[i].l >= l && tree[i].r <=r )
    {
        tree[i].sum += val;
        tree[i].add[po[k][t]] += val;
        return ;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(l <= mid)
        Insert(lson,l,r,val,k,t);
    if(r > mid)
        Insert(rson,l,r,val,k,t);
    push_up(i);
}

int query(int i,int pos)
{
    //if(tree[i].l >= l && tree[i].r <= r)
    if(tree[i].l == tree[i].r)
    {
        int tmp = 0;
        for(int j = 1;j <= 10;j++)
            tmp += tree[i].add[po[j][pos%j]];
        return tmp;
    }
    push_down(i);
    int mid = tree[i].mid();

    if(pos <= mid)
        return query(lson,pos);
    if(pos > mid)
        return query(rson,pos);
}

int main()
{
    int T,cas = 1,cnt = 0;
    for(int i = 1; i <= 10; i++)
    {
        for(int j = 0; j < i; j++)
            po[i][j] = cnt++;
    }

    while(scanf("%d",&n) != EOF)
    {
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        build(1,n,1);

        int l,r,q;
        int val,k;
        scanf("%d",&q);
        for(int i = 1; i <=q; i++)
        {
            int op;
            scanf("%d",&op);
            if(op == 1)
            {
                scanf("%d%d%d%d",&l,&r,&k,&val);
                Insert(1,l,r,val,k,l%k);
            }
            else
            {
                scanf("%d",&l);
                printf("%d\n",query(1,l)+a[l]);
            }
        }
    }
    return 0;
}

/*
hdu 4027 Can you answer these queries?

0:��[l,r]����ȡƽ����
1:��[l,r]�ĺ�

����0������ȡƽ����,�о����ʺ��ڱ���´��������������ÿ�������µ��ڵ�Ļ�̫
��ʱ��,���ҿ��Է���2^64���8�ξͱ��1��,���Ҷ���1ȥƽ��������,������
������µĻ������ж������Ƿ�ȫΪ1����

hhh-2016-03-29 15:17:46
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<math.h>
#include<functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int maxn = 100500 ;

struct node
{
    int l,r;
    ll sum;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].sum=tree[lson].sum+tree[rson].sum;
}

void build(int i,int l,int r)
{
    tree[i].l = l, tree[i].r = r;
    tree[i].sum = 0;
    if(l == r)
    {
        scanf("%I64d",&tree[i].sum);
        return ;
    }

    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void update(int i,int l,int r)
{
    if(tree[i].l == tree[i].r)
    {
        tree[i].sum = sqrt(tree[i].sum*1.0);
        return;
    }

    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tree[i].sum == tree[i].r-tree[i].l+1)
            return ;
    }
    if(l <= tree[i].mid())
        update(lson,l,r);
    if(r > tree[i].mid())
        update(rson,l,r);
    push_up(i);
}

ll query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].sum;
    ll ans = 0;
    push_down(i);
    if(l <= tree[i].mid())
        ans += query(lson,l,r);
    if(r > tree[i].mid())
        ans += query(rson,l,r);
    return ans;
}

int main()
{
    int cas = 1,n;
    while(scanf("%d",&n) != EOF)
    {
        build(1,1,n);
        printf("Case #%d:\n", cas++);
        int q,x,y,op;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d",&op);
            if(op == 0)
            {
                scanf("%d%d",&x,&y);
                if(x > y)swap(x,y);
                update(1,x,y);
            }
            if(op == 1)
            {
                scanf("%d%d",&x,&y);
                if(x > y)swap(x,y);
                printf("%I64d\n",query(1,x,y));
            }
        }
        printf("\n");
    }
    return 0 ;
}

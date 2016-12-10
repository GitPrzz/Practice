/*
hdu 2871 �߶���(���ֲ���)

New x:��1��ʼ�ҵ�һ������x�հ������������ڴ�
Free x:�ͷ�x��������������ڴ� ��������Ҷ˵�
Get x:��õ�x���������˵�
reset:�ͷ�ȫ�����ڴ�

�����һ������������ڴ�����Ϊ1,�հ״�ȫ��0
1.����New������Ҫ�ı���0������������� ��ͨ��ls,rs,ms����,���ж������Ƿ��ܷ���
�����ҳ�������˵㼴��
2.Ȼ����Free,��1�����䡣���ǿ�����from��to����¼һ����������Ҷ˵㣬Ȼ��ͨ��
push_down�·ŵ�����.����ֻ��Ҫ�ҳ�x���Ӧ�Ľڵ���i����
3.��Ϊ����ǵ�x������,���Կ�ʼ��num���ʱ����˺ü��Ρ����ֿ��԰�������˵�
���Ϊ1.������ʵ�ֵ�ʱ���������жϵ�ǰλ���Ƿ���Ҫ�����������˵㣬�䣡
if(tree[i].l == l)
    tree[i].num = 1;
4.����reset,������ȫ������Ϊ0����

�󵥵������������Ҷ˵�+��������������+���k������

hhh-2016-04-02 17:48:33
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
    int l,r;
    int ls,ms,rs;   //��¼0����������
    int num,same;
    int from,to;    //��¼1�����Ҷ˵�
    int mid()
    {
        return (l+r)>>1;
    }
    int len()
    {
        return (r-l+1);
    }
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].ls = tree[lson].ls,tree[i].rs= tree[rson].rs;
    if(tree[i].ls == tree[lson].len())
        tree[i].ls += tree[rson].ls;
    if(tree[i].rs == tree[rson].len())
        tree[i].rs += tree[lson].rs;
    tree[i].ms = max(tree[lson].ms,tree[rson].ms);
    tree[i].ms = max(tree[i].ms,tree[lson].rs + tree[rson].ls);

    tree[i].num = tree[lson].num + tree[rson].num;
}

void ini(int i,int val)
{
    tree[i].ls=tree[i].rs=tree[i].ms=val;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].same =tree[i].from = tree[i].to = -1;
    tree[i].num = 0;
    if(l == r)
    {
        ini(i,1);
        return ;
    }
    int mid = (l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].same != -1)
    {
        tree[lson].same = tree[i].same;
        tree[rson].same = tree[i].same;
        tree[lson].from = tree[rson].from = tree[i].from;
        if(tree[i].num != -1)
        {
            tree[lson].num = tree[i].num;
            tree[rson].num = 0;
        }
        tree[lson].to = tree[rson].to = tree[i].to;
        ini(lson,(!tree[i].same)*tree[lson].len());
        ini(rson,(!tree[i].same)*tree[rson].len());
        tree[i].same = -1;
    }

}

void update(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].same = val;
        if(val)
        {
            if(tree[i].l == l)
            tree[i].num = 1;
            tree[i].from = l;
            tree[i].to = r;
            ini(i,0);
        }
        else
        {
            if(tree[i].l == l)
            tree[i].num = 0;
            tree[i].from = tree[i].to = -1;
            ini(i,tree[i].len());
        }
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update(lson,l,r,val);
    if(r > mid)
        update(rson,l,r,val);
    push_up(i);
    return ;
}

int New(int i,int len)
{
    if(tree[i].l == tree[i].r)
    {
        return tree[i].l;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(tree[lson].ms >= len)
        return New(lson,len);
    else if(tree[lson].rs + tree[rson].ls >= len)
        return mid-tree[lson].rs+1;
    else
        return New(rson,len);
}

int Free(int i,int k)
{
    if(tree[i].l == tree[i].r)
        return i;
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        return Free(lson,k);
    else
        return Free(rson,k);
}

int Get(int i,int k)
{
    if(tree[i].l == tree[i].r)
        return tree[i].l;
    push_down(i);
    if(tree[lson].num >= k)
        return Get(lson,k);
    else
        return Get(rson,k-tree[lson].num);
}

char op[10];

int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m) != EOF)
    {
        build(1,1,n);
        int x;
        while(m--)
        {
            scanf("%s",op);
            if(op[0] == 'N')
            {
                scanf("%d",&x);

                if(tree[1].ms >= x)
                {
                    int l = New(1,x);
                    printf("New at %d\n",l);
                    update(1,l,l+x-1,1);
                }
                else
                    printf("Reject New\n");

            }
            else if(op[0] == 'F')
            {
                scanf("%d",&x);
                int t = Free(1,x);
                if(tree[t].from == -1)
                    printf("Reject Free\n");
                else
                {
                    printf("Free from %d to %d\n",tree[t].from,tree[t].to);
                    update(1,tree[t].from,tree[t].to,0);
                }
            }
            else if(op[0] == 'G')
            {
                scanf("%d",&x);
                if(tree[1].num >= x)
                    printf("Get at %d\n",Get(1,x));
                else
                    printf("Reject Get\n");
            }
            else if(op[0] == 'R')
            {
                update(1,1,n,0);
                printf("Reset Now\n");
            }
        }
        printf("\n");
    }
    return 0;
}

/*
hdu 3397 �߶���˫���

����5��������
0:������[a,b]֮�����ȫ����Ϊ0
1:������[a,b]֮�����ȫ����Ϊ1
2:������[a,b]֮��� 1->0  0->1
3:������[a,b]֮��1�ĸ���
4:������[a,b]֮��1�����������

���趨ls1,rs1,ms1,num1  ls0,rs0,ms0,num0�ֱ��¼1,0�����
Ȼ����rev��same���,����ϲ���Щ����ûʲô����,��Ҫ���ڱ���·�
�ʼû��ע����֮��Ļ���Ӱ�������,����[a,b]�ϼ���rev����same
����Ӧ����ô����֮.�����ʼWR�˼���,Ȼ����ֻ��¼same���,������
rev����ʱ  Ҫô���µ���,Ҫô����same�Ա�ǽ����޸ģ������˺ܾã�һֱ
TLE

Ȼ����same��rev֮��Ĺ�ϵ��
����same��[a,b]������һ��rev,��ô�Ѹ�������ԭ���е�revɾ��.
���rev��[a,b]������һ��same���,��ôֻ��Ҫ��same�����޸ļ���,����
��0 1�����ݽ��н���

hhh-2016-04-01 21:52:19
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
const int maxn = 200050;

struct node
{
    int l,r;
    int same,rev;
    int ls1,rs1,ms1;
    int ls0,rs0,ms0;
    int num1,num0;
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
    tree[i].ls0 = tree[lson].ls0,tree[i].ls1 = tree[lson].ls1;
    tree[i].rs0 = tree[rson].rs0,tree[i].rs1 = tree[rson].rs1;
    tree[i].num1 = tree[lson].num1 + tree[rson].num1;
    tree[i].num0 = tree[lson].num0 + tree[rson].num0;

    if(tree[i].ls1 == tree[lson].len() )
        tree[i].ls1 += tree[rson].ls1;
    if(tree[i].ls0 == tree[lson].len() )
        tree[i].ls0 += tree[rson].ls0;
    if(tree[i].rs1 == tree[rson].len() )
        tree[i].rs1 += tree[lson].rs1;
    if(tree[i].rs0 == tree[rson].len() )
        tree[i].rs0 += tree[lson].rs0;
    tree[i].ms1 = max(tree[lson].ms1,tree[rson].ms1);
    tree[i].ms0 = max(tree[lson].ms0,tree[rson].ms0);
    tree[i].ms1 = max(tree[i].ms1,tree[lson].rs1+tree[rson].ls1);
    tree[i].ms0 = max(tree[i].ms0,tree[lson].rs0+tree[rson].ls0);
}
void ini1(int i,int val)
{
    tree[i].num1=tree[i].ls1 = tree[i].rs1 = tree[i].ms1 = val;
}

void ini0(int i,int val)
{
    tree[i].num0=tree[i].ls0 = tree[i].rs0 = tree[i].ms0 = val;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    ini1(i,0),ini0(i,0);
    tree[i].same = -1;
    tree[i].rev = 0;
    if(l == r)
    {
        int x;
        scanf("%d",&x);
        if(x)
            ini1(i,1);
        else
            ini0(i,1);
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void exchange(int i)
{
    swap(tree[i].ls1,tree[i].ls0);
    swap(tree[i].rs1,tree[i].rs0);
    swap(tree[i].ms0,tree[i].ms1);
    swap(tree[i].num0,tree[i].num1);
}

void solve(int i)
{
    tree[i].same ^= 1;
    if(tree[i].same)
    {
        ini1(i,tree[i].len());
        ini0(i,0);
    }
    else
    {
        ini1(i,0);
        ini0(i,tree[i].len());
    }
}

void push_down(int i)
{
    if(tree[i].same != -1)
    {
        tree[lson].rev = tree[rson].rev = 0;
        tree[lson].same = tree[i].same;
        tree[rson].same = tree[i].same;
        if(tree[i].same)
        {
            ini1(lson,tree[lson].len()),ini0(lson,0);
            ini1(rson,tree[rson].len()),ini0(rson,0);
        }
        else
        {
            ini1(lson,0),ini1(rson,0);
            ini0(lson,tree[lson].len()),ini0(rson,tree[rson].len());
        }
        tree[i].same = -1;
    }
    if(tree[i].rev)
    {
        if(tree[lson].same != -1)
        {
            solve(lson);
        }
        else
        {
            tree[lson].rev ^= 1;
            exchange(lson);
        }
        if(tree[rson].same != -1)
        {
            solve(rson);
        }
        else
        {
            tree[rson].rev ^= 1;
            exchange(rson);
        }
        tree[i].rev = 0;
    }
}

void update_same(int i,int l,int r,int va)
{
    if(tree[i].l >= l && tree[i].r <= r )
    {
        tree[i].rev = 0;
        if(va)
        {
            ini1(i,tree[i].len()),ini0(i,0);
        }
        else
        {
            ini1(i,0),ini0(i,tree[i].len());
        }
        tree[i].same = va;
        return;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update_same(lson,l,r,va);
    if(r > mid)
        update_same(rson,l,r,va);
    push_up(i);
}

void update_rev(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tree[i].same != -1)
        {
            solve(i);
            return ;
        }
        tree[i].rev ^= 1;
        exchange(i);
        return;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        update_rev(lson,l,r);
    if(r > mid)
        update_rev(rson,l,r);
    push_up(i);
}

int query1(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].ms1;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(r <= mid)
        return query1(lson,l,r);
    else if(l > mid)
        return query1(rson,l,r);
    else
    {
        int ans1 = query1(lson,l,mid);
        int ans2 = query1(rson,mid+1,r);
        return max(max(ans1,ans2),min(tree[lson].rs1,mid-l+1)+min(tree[rson].ls1,r-mid));
    }
}

int query2(int i,int l,int r)
{
    if(l <= tree[i].l && tree[i].r <= r)
    {
        return tree[i].num1;
    }
    push_down(i);
    int mid = tree[i].mid();
    int num = 0;
    if(l <= mid)
        num += query2(lson,l,r);
    if(r > mid)
        num += query2(rson,l,r);
    return num;
}

int op;
int x,y;
int T,n,m;
int main()
{

    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        build(1,0,n-1);

        while(m--)
        {
            scanf("%d",&op);
            scanf("%d%d",&x,&y);
            if(op == 0)
                update_same(1,x,y,0);
            else if(op == 1)
                update_same(1,x,y,1);
            else if(op == 2)
                update_rev(1,x,y);
            else if(op == 3)
                printf("%d\n",query2(1,x,y));
            else
                printf("%d\n",query1(1,x,y));
        }
    }
    return 0;
}

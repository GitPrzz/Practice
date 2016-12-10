/*
hdu 1828 �߶���ɨ����(�ܳ�)

����һЩ����,�в���orȫ���ص�.������ͼ�ε��ܳ�

����x��ı�,������±߱�Ϊ1,������ϱ߱�Ϊ-1.ÿ�β�����õ�ǰ�������
��ȥ��һ�εĸ������(����������)��ɨ���һ��������ϱߺ���������±ߵ�
Ӱ�졣
��x,y��ֱ�ɨ��һ�μ���

�ʼû�����رߵ�����,���C++ AC(G++ WR)
Ȼ����ĺ�G++�Ź� - -

2
0 0 1 1
1 0 2 1

2
0 0 1 1
0 1 1 2

hhh-2016-03-26 16:35:21
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
const int maxn = 20050;
int a[maxn];
struct node
{
    int l,r;
    int sum,len;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*5];

void push_up(int i)
{
    if(tree[i].sum)
        tree[i].len = (tree[i].r-tree[i].l+1);
    else if(tree[i].l == tree[i].r)
        tree[i].len = 0;
    else
        tree[i].len = tree[lson].len+tree[rson].len;
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = 0;
    tree[i].len = 0;
    if(l == r)
        return ;

    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
//    if(tree[i].sum)
//    {
//        tree[lson].sum += tree[i].sum;
//        tree[rson].sum += tree[i].sum;
//        tree[lson].len = tree[lson].r-tree[lson].l;
//        tree[rson].len = tree[rson].r-tree[rson].l;
//    }
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
    int l,r;
    int va,high;
};
edge tx[maxn*2];
edge ty[maxn*2];

bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else   //������ر���Ҫ�Ȳ�����ɾ��
        return a.va > b.va;
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        int x1,x2,y1,y2;
        int tox = 0,lx=0x3f3f3f3f,rx=0;
        int toy = 0,ly=0x3f3f3f3f,ry=0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            lx = min(x1,lx),rx = max(rx,x2);
            ly = min(y1,ly),ry = max(ry,y2);
            tx[tox].l = x1,tx[tox].r = x2,tx[tox].high=y1,tx[tox++].va=1;
            tx[tox].l = x1,tx[tox].r = x2,tx[tox].high=y2,tx[tox++].va=-1;
            ty[toy].l = y1,ty[toy].r = y2,ty[toy].high=x1,ty[toy++].va=1;
            ty[toy].l = y1,ty[toy].r = y2,ty[toy].high=x2,ty[toy++].va=-1;
        }
        sort(tx,tx+tox,cmp);
        sort(ty,ty+toy,cmp);
        int ans=0,prelen = 0;
        build(1,lx,rx-1);
        for(int i = 0; i < tox; i++)
        {
            Insert(1,tx[i].l,tx[i].r-1,tx[i].va);
            ans += abs(tree[1].len-prelen);
            prelen = tree[1].len;
        }
        //cout << ans <<endl;
        build(1,ly,ry-1);
        prelen = 0;
        for(int i = 0; i < toy; i++)
        {
            Insert(1,ty[i].l,ty[i].r-1,ty[i].va);
            ans += abs(tree[1].len-prelen);
            prelen = tree[1].len;
        }
        cout << ans <<endl;
    }
    return 0;
}

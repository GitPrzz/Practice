/*
poj2828 BuyTickets �߶���

����n��pos[]��val[],��ʾval[i]�ڵ�pos[i]�������ұ�

�о������������Ƶ���Ŀ
���ڵ�i��������,����ǰ���Ȼ��pos[i]����,���Կ��ǴӺ�����ǰ����
(���˳�����Ļ�û�취�����λ)
����Ļ����������ڵ�i����ǰ������pos[i]����λ����,���������߶����ҳ���
pos[i]+1����λ����

hhh-2016-03-24 15:51:59
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn =  200020;
struct node
{
    int l,r;
    int num;
    int mid()
    {
        return ((l+r)>>1);
    };
} tree[maxn<<2];


void update_up(int i)
{
    tree[i].num = tree[lson].num + tree[rson].num;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;

    if(l == r)
    {
        tree[i].num = 1;
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    update_up(i);
}

void update_down(int i)
{

}
int cur;
void Insert(int i,int k)
{
    if(tree[i].l ==  tree[i].r)
    {
        tree[i].num = 0;
        cur = tree[i].l;
        return;
    }
    update_down(i);
    int mid = tree[i].mid();
    if(k <= tree[lson].num)
        Insert(lson,k);
    else
        Insert(rson,k-tree[lson].num);
    update_up(i);
}

int a[maxn],val[maxn],ans[maxn];

int main()
{
    int k,n,t,m,nex;
    while(scanf("%d",&n) != EOF)
    {
        for(int i = 1; i <= n; i++)
            scanf("%d%d",&a[i],&val[i]);
        build(1,1,n);

        for(int i = n ; i > 0; i--)
        {
            Insert(1,a[i]+1);
            //cout << cur <<endl;
            ans[cur] = val[i];
        }
        for(int i = 1; i <= n; i++)
        {
            printf("%d",ans[i]);
            printf("%c",i==n ? '\n':' ');
        }
    }
    return 0;
}

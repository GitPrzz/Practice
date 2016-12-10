/*
hdu 4288 �����߶���+������G
�ֱ�����ӣ�ɾ�������
sum���� i%5==3���������ĺͣ�������������a[0] < a[1] ......
��ʼ��Ϊֻ�������к�����ӣ�Ȼ��WR
�����ʼ������ͺ��鷳�����������±������TLE

�����ȶ�����Ҫ�õ������д���Ȼ��ÿ���ҳ�����Ӧ���ڵ�λ�ã�����
����ɾ�����ɡ�
��Ҫ��û�뵽�����й������Ƴ���ʽ
tree[i].sum[j]=(ll)(tree[lson].sum[j]+tree[rson].sum[((j-tree[lson].cnt)%5+5)%5]);

hhh-2016-03-02 23:14:26
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
#define lson (i<<1)
#define rson (i<<1|1)
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 500000+10;
int x[maxn];
int tp[maxn],tot;
char opr[maxn][10];
struct node
{
    int l,r;
    ll sum[6];
    int cnt;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];
int flag;
void push_up(int i)
{
    for(int j = 0; j < 5; j++)
    {
        tree[i].sum[j] = (ll)(tree[lson].sum[j]+tree[rson].sum[((j-tree[lson].cnt)%5+5)%5]);
    }
}

void build(int i,int l,int r)
{
    tree[i].l=l,tree[i].r=r;
    tree[i].cnt = 0;
    memset(tree[i].sum,0,sizeof(tree[i].sum));
    int mid = tree[i].mid();
    if(l == r)
        return;
    build(lson,l,mid);
    build(rson,mid+1,r);
}

void update(int i,int k,int val)
{
    tree[i].cnt += 2*flag-1;
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].sum[0] = flag*val;
        return ;
    }
    int mid = tree[i].mid();
    if(k <= mid)update(lson,k,val);
    else update(rson,k,val);
    push_up(i);
}

int Search(int k)
{
    int l = 0,r = tot-1;
    while(l<=r)
    {
        int mid = (l+r)>>1;
        if(tp[mid]<k)
            l = mid+1;
        else if(tp[mid]>k)
            r = mid-1;
        else
            return mid;
    }
}
int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        tot = 0;
        for(int i = 0; i<n; i++)
        {
            scanf("%s",opr[i]);
            if(opr[i][0] != 's')
            {
                scanf("%d",&x[i]);
                tp[tot++] = x[i];
            }
        }
        sort(tp,tp+tot);
        tot = unique(tp,tp+tot)-tp;//ȥ��
        if(!tot)
            memset(tree[1].sum,0,sizeof(tree[1].sum));
        else
            build(1,0,tot);
        for(int i =0; i < n; i++)
        {
            if(opr[i][0] == 's')
            {
                printf("%I64d\n",tree[1].sum[2]);
            }
            else if(opr[i][0] == 'a')
            {
                flag = 1;
                int pos = Search(x[i]);
                update(1,pos,x[i]);
            }
            else if(opr[i][0] == 'd')
            {
                flag =0 ;
                int pos = Search(x[i]);
                update(1,pos,x[i]);
            }
        }
    }
    return 0;
}

/*
hdu4521 线段树+dp
隔k个数的最长上升子序列
用线段树来维护到第最大值小于等于i时的子序列长度，然后则是注意添加的时候
每次i-k>0进行插入，到了下个for循环则刚好是添加到第i-k-1个。
hhh-2016-02-29 19:13:32
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 100020;

struct node
{
    int l,r;
    int len;
} tree[maxn*100];
int tans[maxn];
int a[maxn];
void push_up(int r)
{
    int lson = r<<1;
    int rson = r<<1|1;
    tree[r].len = max(tree[lson].len,tree[rson].len);
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].len = 0;
    if(l == r)
        return;
    int mid = (l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    push_up(i);
}

void update(int i,int k,int c)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].len = c;
        return ;
    }
    int mid = (tree[i].l+tree[i].r)>>1;
    if(k <= mid)update(i<<1,k,c);
    else update(i<<1|1,k,c);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].len;
    int mid = (tree[i].l+tree[i].r)>>1;
    int ans = 0;
    if(l <= mid)
        ans = max(ans,query(i<<1,l,r));
    if(r > mid)
        ans = max(ans,query(i<<1|1,l,r));
    return ans ;
}

int main()
{
    int n,k,x;
    while(scanf("%d%d",&n,&k) != EOF)
    {
        int ans = 0;
        build(1,0,maxn);
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            if(a[i]>0)
                tans[i] = query(1,0,a[i]-1)+1;
            else
                tans[i] = 1;
            ans = max(ans,tans[i]);
            if(i-k>0)
                update(1,a[i-k],tans[i-k]);
        }
        cout << ans <<endl;
    }
    return 0;
}

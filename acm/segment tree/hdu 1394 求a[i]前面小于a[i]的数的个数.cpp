/*
hdu 1394 求a[i]前面小于a[i]的数的个数
给你一个序列，求每个a[i]后面小于a[i]的个数，
然后你可以把第一个数放到最后，这样的话sum变化：sum = sum+(n-1-a[i])-a[i];
hhh-2016-02-27 15:18:09
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
int a[maxn];
struct node
{
    int l,r;
    int num;
} tree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    tree[r].num = (tree[lson].num+tree[rson].num);
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].num  = 0;
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



void Insert(int i,int k)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].num++;
        return ;
    }
    push_down(i);
    int mid = (tree[i].l + tree[i].r) >>1;
    if(k <= mid) Insert(i<<1,k);
    if(k > mid) Insert(i<<1|1,k);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].num;
    }
    push_down(i);
    int mid = (tree[i].l+tree[i].r)>>1;
    int ans = 0;
    if(l <= mid) ans+=(query(i<<1,l,r));
    if(r > mid) ans+=(query(i<<1|1,l,r));
    return ans ;
}

int main()
{
    int T,n,m,cas = 1;
    while(scanf("%d",&n)!=EOF)
    {
        build(1,0,n-1);
        int sum = 0;
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            Insert(1,a[i]);
            int t;
            if(a[i] - 1 < 0)
                t = 0;
            else
               t = query(1,0,a[i]-1);
            sum += (a[i] - t);
        }

        int ans = sum;
        for(int i = 1;i <= n;i++)
        {
            sum = sum+(n-1-a[i])-a[i];
            ans = min(ans,sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}


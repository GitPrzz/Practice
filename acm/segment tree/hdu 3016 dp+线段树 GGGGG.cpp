/*
hdu 3016 dp+线段树 GGGGG
感觉没做过类似的，导致一直没什么思路
由于每次我们只能从两边跳下来，倒推的答案是唯一的
于是先按照高度排个序，然后就类似于叠木板，先判断当前的两端下面是哪个木板
然后取较大值再加上当前值即可
study~~~
hhh-2016-02-29 22:54:23
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 100050;
const int inf = 0x3f3f3f3f;
struct node
{
    int l,r,mid;
    int cov;
} tree[maxn<<2];

struct segment
{
    int l,r,h;
    int val;
    void get()
    {
        scanf("%d%d%d%d",&h,&l,&r,&val);
    }
} seg[maxn];
int dp[maxn];
bool cmp(segment a,segment b)
{
    return a.h < b.h;
}

void push_up(int r)
{
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].cov = 0;
    tree[i].mid = (l +r)>>1;
    if(l == r)
    {
        return ;
    }
    build(i<<1,l,tree[i].mid);
    build(i<<1|1,tree[i].mid+1,r);
    push_up(i);
}

void push_down(int r)
{
    int lson = r<<1,rson = r<<1|1;
    if(tree[r].cov != -1)
    {
        tree[lson].cov = tree[r].cov;
        tree[rson].cov = tree[r].cov;
        tree[r].cov = -1;
    }
}

void update(int i,int l,int r,int c)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].cov = c;
        return ;
    }
    push_down(i);
    if(l <= tree[i].mid)
        update(i<<1,l,r,c);
    if(r > tree[i].mid)
        update(i<<1|1,l,r,c);
    push_up(i);
}

int query(int i,int k)
{
    if(tree[i].cov != -1)
    {
        return tree[i].cov;
    }
    push_down(i);
    if(k <= tree[i].mid)
        return query(i<<1,k);
    else
        return query(i<<1|1,k);
    push_up(i);
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        build(1,1,maxn);
        for(int i =1; i <= n; i++)
        {
            seg[i].get();
        }
        memset(dp,0,sizeof(dp));
        sort(seg+1,seg+n+1,cmp);
        int l=0,r=0;
        for(int i = 1; i <= n; i++)
        {
            if(i > 1)
            {
                l = query(1,seg[i].l);
                r = query(1,seg[i].r);
            }
            dp[i] = max(dp[l],dp[r])+seg[i].val;
            update(1,seg[i].l,seg[i].r,i);
        }
        dp[n] += 100;
        if(dp[n] <= 0)
            printf("-1\n");
        else
            printf("%d\n",dp[n]);
    }
    return 0;
}

/*
hdu 1754 线段树(Max+单点修改)
U i j：在第i个上改为j
Q i j：求i到j的最大值
hhh-2016-02-27 14:20:36
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
struct node
{
    int l,r;
    int Max;
} tree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    tree[r].Max = max(tree[lson].Max,tree[rson].Max);
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Max  = 0;
    if(l == r)
    {
        scanf("%d",&tree[i].Max);
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

void change(int i,int k,int c)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].Max = c;
        return ;
    }
    push_down(i);
    int mid = (tree[i].l + tree[i].r) >>1;
    if(k <= mid) change(i<<1,k,c);
    if(k > mid) change(i<<1|1,k,c);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].Max;
    }
    push_down(i);
    int mid = (tree[i].l+tree[i].r)>>1;
    int ans = 0;
    if(l <= mid) ans= max(ans,query(i<<1,l,r));
    if(r > mid) ans= max(ans,query(i<<1|1,l,r));
    return ans ;
}

int main()
{
    int T,n,m,cas = 1;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        build(1,1,n);
//        printf("Case %d:\n",cas++);
        char op[10];
        int l,r;
        for(int i =1;i <= m;i++)
        {
            scanf("%s",op);
            if(op[0] == 'Q')
            {
                scanf("%d%d",&l,&r);
                printf("%d\n",query(1,l,r));
            }
            else
            {
                scanf("%d%d",&l,&r);
                change(1,l,r);
            }
        }
    }
    return 0;
}


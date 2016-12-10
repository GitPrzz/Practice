/*
hdu 1166 线段树(sum+单点修改)
add i j：在第i个上加j
sub i j：在第i个上减j
query i j：求i到j的和
hhh-2016-02-27 14:11:18
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
const int maxn = 50000+5;
struct node
{
    int l,r;
    int sum;
} tree[maxn<<2];

void push_up(int r)
{
    int lson = r<<1,rson = (r<<1)|1;
    tree[r].sum = tree[lson].sum + tree[rson].sum;
}
void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].sum  = 0;
    if(l == r)
    {
        scanf("%d",&tree[i].sum);
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
        tree[i].sum += c;
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
        return tree[i].sum;
    }
    push_down(i);
    int mid = (tree[i].l+tree[i].r)>>1;
    int ans = 0;
    if(l <= mid) ans += query(i<<1,l,r);
    if(r > mid) ans += query(i<<1|1,l,r);
    return ans ;
}

int main()
{
    int T,n,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        build(1,1,n);
        printf("Case %d:\n",cas++);
        char op[10];
        int l,r;
        while(scanf("%s",op))
        {
            if(op[0] == 'E') break;
            if(op[0] == 'Q')
            {
                scanf("%d%d",&l,&r);
                printf("%d\n",query(1,l,r));
            }
            if(op[0] == 'A')
            {
                scanf("%d%d",&l,&r);
                change(1,l,r);
            }
            if(op[0] == 'S')
            {
                scanf("%d%d",&l,&r);
                change(1,l,-r);
            }
        }
    }
    return 0;
}


/*
51nod 1376 最长递增子序列的数量

problem:
给你一个数组,求其中最长递增子序列有多少个

solve:
对于第i个数a[i]而言,它需要知道[1,a[i]-1]中最长递增子序列的长度以及数量. 所以可以利用线段树来维护,
然后利用长度和数量来更新a[i]

hhh-2016/09/03-16:41:1
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1000000007;
const int maxn = 50010;
const double PI = acos(-1.0);
int a[maxn],t[maxn];
struct node
{
    int l,r;
    ll Max,num;
    int mid;
} tree[maxn << 2];

void push_up(int i)
{
    if(tree[lson].Max == tree[rson].Max)
    {
        tree[i].Max = tree[lson].Max;
        tree[i].num = tree[lson].num + tree[rson].num;
        tree[i].num %= mod;
    }
    else if(tree[lson].Max > tree[rson].Max)
    {
        tree[i].Max = tree[lson].Max;
        tree[i].num = tree[lson].num;
    }
    else
    {
        tree[i].Max = tree[rson].Max;
        tree[i].num = tree[rson].num;
    }
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Max = tree[i].num = 0;
    tree[i].mid = (l+r) >> 1;
    if(l == r)
        return ;
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid + 1,r);
    push_up(i);
}

void push_down(int i)
{

}

void update(int i,int k,ll len,ll many)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        if(tree[i].Max < len) tree[i].Max = len,tree[i].num = many;
        else if(tree[i].Max == len) tree[i].num += many;
        tree[i].num %= mod;
        return ;
    }
    int mid = tree[i].mid;
    if(k <= mid)
        update(lson,k,len,many);
    else update(rson,k,len,many);
    push_up(i);
}
ll tans,tnum;
void query(int i,int l,int r)
{
    if(l > r)
    {
        tans = 0,tnum = 1;
        return ;
    }
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tans == -1)
            tans = tree[i].Max,tnum = tree[i].num;
        else
        {
            if(tans == tree[i].Max) tnum += tree[i].num;
            else if(tans < tree[i].Max)
            {
                tans = tree[i].Max,tnum = tree[i].num;
            }
            tnum %= mod;
        }
        return ;
    }
    push_down(i);
    int mid = tree[i].mid;
    if(l <= mid)
        query(lson,l,r);
    if(r > mid)
        query(rson,l,r);
    return;
}

int cnt = 0;
int main()
{
    int n;
    while(scanfi(n) != EOF)
    {
        for(int i = 0; i< n;i++){
            scanfi(a[i]);
            t[i] = a[i];
        }
        sort(a,a+n);
        cnt = 0;
        for(int i = 1;i < n;i++)
        {
            if(a[i] != a[cnt])
            a[++cnt] = a[i];
        }
//        for(int i = 0;i <= cnt;i++)
//            printf("%d\n",a[i]);
        build(1,0,cnt);
        ll tMax = 0,ans = 0;
        int id = lower_bound(a,a+cnt+1,t[0]) -a;
        update(1,id,1,1);
        tMax = 1,ans = 1;
        for(int i = 1;i < n;i++)
        {
            id = lower_bound(a,a+cnt+1,t[i]) -a;
//            cout << id <<" " ;
            tans = -1,tnum = 0;
            query(1,0,id-1);
            if(!tans && !tnum)
                tnum = 1;
            if(tMax < tans+ 1) tMax = tans+1,ans = tnum;
            else if(tMax == tans+1) ans += tnum;
            ans %= mod;
            update(1,id,tans + 1,tnum);
        }
//        cout <<endl;
        printf("%I64d\n",ans);
    }
    return 0;
}

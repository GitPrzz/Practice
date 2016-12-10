/*
51nod 1364 最大字典序排列(线段树)

problem:
给出一个1至N的排列，允许你做不超过K次操作，每次操作可以将相邻的两个数交换，问能够得到的字典序最大的排列是什么？
例如：N = 5， {1 2 3 4 5}，k = 6，在6次交换后，能够得到的字典序最大的排列为{5 3 1 2 4}。

solve:
贪心的思想.  从1~n维护第i个数尽可能大. 就成了在[i+1,k+i]中查找最大值. 然后把找到的数从后面的数组中删除插到前面.
因为我的删除是用num来表示,所以每次都要先找到对应区间的边界位置. 然后在计算移动过去需要多少步. 直到操作结束

hhh-2016/09/04-11:16:36
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
const int maxn = 100010;
const double PI = acos(-1.0);
int n;
int a[maxn];
struct node
{
    int l,r,mid;
    int pos,num;
    int Max;
} tree[maxn<<2];

void push_up(int i)
{
    if(tree[lson].Max >= tree[rson].Max)
    {
        tree[i].Max= tree[lson].Max;
        tree[i].pos = tree[lson].pos;
    }
    else
    {
        tree[i].Max = tree[rson].Max;
        tree[i].pos = tree[rson].pos;
    }
    tree[i].num = tree[lson].num + tree[rson].num;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].mid = (l+r) >>1;
    tree[i].num = 0;
    if(l == r && l)
    {
        tree[i].num = 1;
        tree[i].Max= a[l];
        tree[i].pos = l;
        return ;
    }
    build(lson,l,tree[i].mid);
    build(rson,tree[i].mid+1,r);
    push_up(i);
}
int tMax,tpos;

void update(int i,int k)
{
    if(tree[i].l >= k && tree[i].r <= k)
    {
        tree[i].Max = 0;
        tree[i].num = 0;
        return ;
    }
    int mid = tree[i].mid;
    if(k <= mid)
        update(lson,k);
    else
        update(rson,k);
    push_up(i);
    return ;
}
void query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tMax < tree[i].Max)
            tMax = tree[i].Max,tpos = tree[i].pos;
        else if(tMax == tree[i].Max)
            tpos = min(tree[i].pos,tpos);
        return ;
    }
    int mid = tree[i].mid;
    if(l <= mid)
        query(lson,l,r);
    if(r > mid)
        query(rson,l,r);
    push_up(i);
    return ;
}

int query_x(int i,int k)
{
    if(tree[i].l == tree[i].r)
    {
        return tree[i].l;
    }
    int mid = tree[i].mid;
    if(tree[lson].num >= k)
       return  query_x(lson,k);
    else
        return query_x(rson,k-tree[lson].num);
    push_up(i);
}

int query_num(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].num;
    }
    int ans = 0;
    if(l <=tree[i].mid)
        ans += query_num(lson,l,r);
    if(r > tree[i].mid)
        ans += query_num(rson,l,r);
    return ans;
}

int ans[maxn];
int main()
{
    int t;
//    freopen("in.txt","r",stdin);
    while(scanfi(n) != EOF)
    {
        scanfi(t);
        a[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            scanfi(a[i]);
        }
        build(1,1,n);
        int cnt = 1;
        while(t > 0 && cnt <= n)
        {
            tMax = 0,tpos = n;
            if(cnt + t >= n)
            {
                query(1,1,n);
                update(1,tpos);
                t -= query_num(1,1,tpos);

                printf("%d\n",tMax);
                cnt++;
                a[tpos] = -1;
            }
            else
            {
                int pos = query_x(1,t+1);
                query(1,1,pos);
                update(1,tpos);
                t -= query_num(1,1,tpos);
                cnt++;
                printf("%d\n",tMax);
                a[tpos] = -1;
            }
        }
        for(int i = 1; i <= n; i++)
            if(a[i]  !=  -1)
                printf("%d\n",a[i]);
    }
    return 0;
}

/*
hdu 4031 attack 线段树区间更新

problem:
每个位置有一个防御塔，每次敌人会对一个区间进行攻击。防御塔有一个冷却时间t。
问某个时间时，某个位置被成功攻击的次数（没有被防御）

solve:
主要是怎么处理这个冷却值的问题，区间攻击都可以使用 线段树区间更新来解决。
最开始考虑的是通过 更新来维护每个点，那每次就要更新[1,n]，感觉应该会超时吧
然后想到是 通过每次-1来体现时间的变化，但是无法知道每个点攻击成功的情况

所以直接暴力搞了- -
通过线段树记录被攻击了多少次，然后通过记录可以知道防御成功了多少次
于是就能得出答案。

hhh-2016-08-05 21:16:55
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <set>
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn=100000 + 10;
const int INF=0x3f3f3f3f;
const int mod = 1e9+7;
int n;

struct node
{
    int l,r;
    int val;
    int len ;
    int mid()
    {
        return (l+r)>> 1;
    }
} tree[maxn<<2];


void push_up(int i)
{
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].val = tree[i].len = 0;
    if(l == r)
    {
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].val)
    {
        tree[lson].val += tree[i].val;
        tree[rson].val += tree[i].val;
        tree[i].val = 0;
    }
}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].val += val;
        push_up(i);
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
}

int query(int i,int k)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        return tree[i].val;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}
struct Point
{
    int l,r;
    Point()
    {

    }
    Point(int a,int b)
    {
        l = a,r = b;
    }
};
Point pt[maxn];
char op[5];

int main()
{
    int T,n,m,k;
    int cas = 1;
    int a,b;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        int cnt = 0;
        build(1,1,n);
        printf("Case %d:\n",cas++);
        for(int i = 1;i <= m;i++)
        {
            scanf("%s",op);
            if(op[0] == 'Q')
            {
                int num = 0;
                scanf("%d",&a);
                for(int i = 0;i < cnt;)
                {
                    if( a>= pt[i].l && a <= pt[i].r)
                    {
                        num++;
                        i += k;
                    }
                    else
                    {
                        i++;
                    }
                }
                printf("%d\n",query(1,a) - num);
            }
            else
            {
                scanf("%d%d",&a,&b);
                Insert(1,a,b,1);
                pt[cnt++] = Point(a,b);
            }
        }
    }
    return 0;
}

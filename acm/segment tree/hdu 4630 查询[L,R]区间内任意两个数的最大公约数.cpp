/*
hdu 4630 查询[L,R]区间内任意两个数的最大公约数

给你n个数，m个询问,输出区间[l,r]内的任意两个数的最大公约数

对于每一个数而言,对左右都会造成影响,所以我们考虑把查询按r从小到大排序,遇到r则输出结果
像这样的话我们就能只考虑a[i]与 [1,i-1]之间数的关系
因为是求的最大公约数,所以枚举a[i]的因子,如果发现此因子已经出现过,则在此前因子出现的地方赋值
(因为我们是求[l,r]之间的,并不能保证之前因子出现的位置在此之内),然后更新该因子的位置

hhh-2016-04-05 19:55:32
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
const int maxn = 5e5+5;
int pos[maxn];
int a[maxn];
int tans[maxn];
struct node
{
    int l,r;
    int Max;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].Max = max(tree[lson].Max,tree[rson].Max);
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].Max=0;
    if(l == r)
        return ;
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void update(int i,int k,int val)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        tree[i].Max =  max(tree[i].Max,val);
        return ;
    }
    int mid = tree[i].mid();
    if(k <= mid)
        update(lson,k,val);
    else
        update(rson,k,val);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].Max;
    }
    int ans = 0;
    int mid = tree[i].mid();
    if(l <= mid)
        ans = max(ans,query(lson,l,r));
    if(r > mid)
        ans = max(ans,query(rson,l,r));
    return ans;
}

struct qy
{
    int l,r;
    int id;
} qry[maxn];

bool cmp(qy a ,qy b)
{
    return a.r < b.r;
}

int main()
{
    int T;
    int n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        build(1,1,n);
        memset(pos,-1,sizeof(pos));
        for(int i = 1; i <= n; i++)
            scanf("%d",&a[i]);
        int m;
        scanf("%d",&m);
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d",&qry[i].l,&qry[i].r);
            qry[i].id = i;
        }
        sort(qry+1,qry+1+m,cmp);

        for(int i = 1,cur = 1; i <= n; i++)
        {

            for(int j = 1; j*j <= a[i]; j++)
            {
                if(a[i]%j == 0)
                {
                    if(pos[j] != -1)
                        update(1,pos[j],j);
                    if(pos[a[i]/j]!= -1)
                        update(1,pos[a[i]/j],a[i]/j);
                    pos[j] = i;
                    pos[a[i]/j] = i;
                }
            }

            while(i == qry[cur].r && cur <= m)
            {
                tans[qry[cur].id] = query(1,qry[cur].l,qry[cur].r);
                cur ++;
            }
        }
        for(int i = 1; i <= m; i++)
        {
            printf("%d\n",tans[i]);
        }
    }
    return 0;
}

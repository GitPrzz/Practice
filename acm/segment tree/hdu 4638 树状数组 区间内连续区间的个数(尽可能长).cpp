/*
hdu 4638 树状数组 区间内连续区间的个数(尽可能长)

给你n个数,让你查询区间[l,r]内最长连续区间的个数。求的是区间长度平方的和,
所以区间长度越长越好
3 1 2 5 4  在[1,5]上:1,2,3,4,5   1个
           在[2,4]上:1,2 和 4    2个
首先我们把每个数看成独立的,即每个数赋值为1
对于当前出现的a[i],如果前面出现了a[i-1],a[i+1]那么就能组成一队,但是我们
是从左往右递推出来的,所以保存的值应尽可能在右边以方便查询,所以如果前面出现了
a[i-1],a[i+1].则在它们的位置上-1,删除它们的独立值.

hhh-2016-04-04 17:05:44
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 10007;
const int maxn = 100050;

int s[maxn];
int a[maxn];
int p[maxn];
int ans[maxn];
struct node
{
    int l,r;
    int id;
} op[maxn];
int n,m;
bool cmp(node a,node b)
{
    return a.r < b.r;
}

int lowbit(int x)
{
    return x&(-x);
}

void add(int x,int val)
{
    while(x <= n)
    {
        s[x] += val;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int cnt = 0;
    while(x)
    {
        cnt += s[x];
        x -= lowbit(x);
    }
    return cnt;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(s,0,sizeof(s));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            p[a[i]] = i;
        }
        for(int i =0; i< m; i++)
        {
            scanf("%d%d",&op[i].l,&op[i].r);
            op[i].id = i;
        }
        sort(op,op+m,cmp);
        for(int i = 1,cur = 0; i <= n; i++)
        {
            add(i,1);
            if(a[i] > 1 && p[a[i]-1] < i)
                add(p[a[i]-1],-1);
            if(a[i] < n && p[a[i]+1] < i)
                add(p[a[i]+1],-1);

            while(i == op[cur].r && cur < m)
            {
                ans[op[cur].id] = sum(op[cur].r)-sum(op[cur].l-1);
                cur++;
            }
        }
        for(int i = 0; i < m; i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}

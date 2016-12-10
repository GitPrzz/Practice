/*
hdu 5869 区间不同GCD个数(树状数组)

problem:
给你一组数, 然后是q个查询. 问[l,r]中所有区间GCD的值总共有多少个(不同的)

solve:
感觉很像线段树/树状数组. 因为有很多题都是枚举从小到大处理查询的r. 这样的话就只需要维护[1,i]的情况
最开始用的set记录生成的gcd然后递推, 超时了.
因为区间gcd是有单调性的.  (i-1->1)和i区间gcd是递减的.
而且用RMQ可以O(1)的查询[i,j]gcd的值.如果枚举[1,i-1]感觉很麻烦.所以用二分跳过中间gcd值相同的部分,即查询与i的区间gcd值为x的
最左边端点.

因为要求不同的值, 这让我想到了用线段树求[l,r]中不同数的个数(忘了是哪道题了 zz)
就i而言,首先找出最靠近i的位置使gcd的值为x. 然后和以前的位置作比较. 尽可能的维护这个位置靠右.
假设：
[3,i-1]的gcd为3,[2,i]的gcd为3.  那么在位置3上面加1.因为只要[l,i]包含这个点,那么就会有3这个值.

hhh-2016-09-10 19:01:57
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define ll long long

using namespace std;

const int maxn = 100100;

int a[maxn];
map<ll,int>mp;

struct node
{
    int l,r;
    int id;
} p[maxn];

bool tocmp(node a,node b)
{
    if(a.r != b.r)
        return a.r < b.r;
    if(a.l != b.l)
        return a.l < b.l;
}

ll Gcd(ll a,ll b)
{
    if(b==0) return a;
    else return Gcd(b,a%b);
}

int lowbit(int x)
{
    return x&(-x);
}

ll out[maxn];
ll siz[maxn];

int n;
void add(int x,ll val)
{
    if(x <= 0)
        return ;
    while(x <= n)
    {
        siz[x] += val;
        x += lowbit(x);
    }
}

ll sum(int x)
{
    if(x <=0)
        return 0;
    ll cnt = 0;
    while(x > 0)
    {
        cnt += siz[x];
        x -= lowbit(x);
    }
    return cnt;
}


int dp[maxn][40];
int m[maxn];

int RMQ(int x,int y)
{
    int t = m[y-x+1];
    return Gcd(dp[x][t],dp[y-(1<<t)+1][t]);
}

void iniRMQ(int n,int c[])
{
    m[0] = -1;
    for(int i = 1; i <= n; i++)
    {
        m[i] = ((i&(i-1)) == 0)? m[i-1]+1:m[i-1];
        dp[i][0] = c[i];
    }
    for(int j = 1; j <= m[n]; j++)
    {
        for(int i = 1; i+(1<<j)-1 <= n; i++)
            dp[i][j] = Gcd(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
    }
}

void init()
{
    mp.clear();
    memset(siz,0,sizeof(siz));
    iniRMQ(n,a);
}

int main()
{
    int qry;
    while(scanf("%d",&n) != EOF)
    {
        scanf("%d",&qry);

        for(int i = 1; i<=n; i++)
        {
            scanf("%d",&a[i]);
        }
        init();
        for(int i = 0; i < qry; i++)
        {
            scanf("%d",&p[i].l),scanf("%d",&p[i].r),p[i].id = i;
        }
        int ta = 0;
        sort(p, p+qry, tocmp);

        for(int i = 1; i <= n; i++)
        {
            int thea = a[i];
            int j = i;
            while(j >= 1)
            {
                int tmid = j;
                int l = 1,r = j;

                while(l <= r)
                {
                    int mid = (l+r) >> 1;
                    if(l == r && RMQ(mid,i) == thea)
                    {
                        tmid = mid;
                        break;
                    }

                    if(RMQ(mid,i) == thea)
                        r = mid-1,tmid = mid;
                    else
                        l = mid+1;
                }

                if(!mp[thea])
                    add(j,1);
                else if(mp[thea] < j && mp[thea])
                {
                    add(mp[thea],-1);
                    add(j,1);
                }
                mp[thea] = j;

                j = tmid-1;

                if(j >= 1) thea = RMQ(j,i);
            }

            while(ta < qry && p[ta].r == i)
            {
                out[p[ta].id] = sum(p[ta].r) - sum(p[ta].l-1);
                ta++;
            }

        }

        for(int i = 0; i < qry; i++)
            printf("%I64d\n",out[i]);
    }
    return 0;
}

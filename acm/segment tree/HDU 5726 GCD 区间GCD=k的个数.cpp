/*
HDU 5726 GCD 区间GCD=k的个数

problem:
给你一列数字,然后是m个询问,每次询问区间[l,r]的gcd以及整个序列中有多少个区间的gcd与之相等

solve:
第一个可以通过线段树或者类rmq的方法来解决.但是求区间的个数就不知怎么弄了- -
最开始想的是每次询问求出值之后用 二分+枚举右端点 的思路来查找有多少个区间的
但是发现整个是递减的,感觉很难确定区间的大小,卒.

看别人题解才发现可以预处理,就一个左端点l而言,[l+1,n]中的到l的区间gcd是递减的.
例：
GCD[l,j] = 4,GCD[l,j+1] = 4,GCD[l,j+2] = 2
感觉题解相当于枚举以l为左点的所有区间GCD值,然后二分到当前GCD值的最右点,计算出区间的个数

因此会涉及很多次区间GCD查询,用线段树的话超时,用RMQ实现O(1)的查询AC
至于时间复杂度, 并不会算QAQ

hhh-2016-08-15 21:35:11
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
int a[maxn];
int m[maxn];
int dp[maxn][20];

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
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
            dp[i][j] = gcd(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
    }
}

int RMQ(int x,int y)
{
    int k = m[y-x+1];
    return gcd(dp[x][k],dp[y-(1<<k)+1][k]);
}

map<int,ll>mp;

void ini(int n)
{
    mp.clear();
    for(int i = 1;i <= n;i++)
    {
       int now = a[i],j = i;
       while(j <= n)
       {
           int l = j,r = n;
           while(l < r)
           {
               int mid = (l+r+1) >> 1;
               if(RMQ(i,mid) == now)
                l = mid;
               else
                r = mid-1;
           }
           mp[now] += (ll)(l-j+1);
           j = l+1;
           now = RMQ(i,j);
       }
    }
}

int main()
{
    int T,n,m;
    int cas = 1;
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        printf("Case #%d:\n",cas++);
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        iniRMQ(n,a);
        ini(n);
        scanf("%d",&m);
        int a,b;
        for(int i =1; i <= m; i++)
        {
            scanf("%d%d",&a,&b);
            int ans1 = RMQ(a,b);
            printf("%d %I64d\n",ans1,mp[ans1]);
        }
    }
    return 0;
}

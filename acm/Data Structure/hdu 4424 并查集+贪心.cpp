/*
hdu 4424 并查集+贪心

problem:
给你由n-1条边相连的n个点，求找到一个点使其到其它个点的val和最大
a-b的val为a到b路径上的最小值
solve:
贪心的想法：
因为是区路径上的最小值，考虑将其按从大到小排序，那么当出现边C将集合A和
集合B连起来时，因为C肯定的最小的，所以集合A或者B中路径val会全部变成C
然后计算出来较大值即可

hhh-2016-08-09 19:20:29
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
typedef unsigned int ul;
const int INF = 0x3f3f3f3f;
const int  maxn = 200000+100;
const int mod = 1e9+7;
int tans;
int pre[maxn];
ll sum[maxn];
ll num[maxn];
int fin(int x)
{
    if(pre[x] == -1)
        return x;
    return pre[x] = fin(pre[x]);
}

struct Edge
{
    int u,v;
    ll len;
}edge[maxn<<1];

bool cmp(Edge a,Edge b)
{
    return a.len > b.len;
}

int main()
{
    int n;
    int a,b;
    ll c;
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n) != EOF)
    {
        tans  = 0;
        memset(pre,-1,sizeof(pre));
        for(int i = 1; i < n;i++)
        {
            num[i] = 1;
            scanf("%d%d%I64d",&a,&b,&c);
            edge[i].u = a,edge[i].v = b,edge[i].len = c;
        }
        ll ans = 0;
        num[n] = 1;
        memset(sum,0,sizeof(sum));
        sort(edge+1,edge+n,cmp);
        for(int i = 1;i < n;i++)
        {
            int ta = fin(edge[i].u);
            int tb = fin(edge[i].v);
           // cout << ta <<" " <<tb <<" " << edge[i].len <<endl;
             ll sum1 = sum[tb]+num[ta]*edge[i].len;
            ll sum2 = sum[ta]+num[tb]*edge[i].len;
          //  cout << sum1 << " " <<sum2 <<endl;
            if(sum1 > sum2)
                sum[ta] = sum[tb] = sum1;
            else
                sum[ta] = sum[tb] = sum2;
            pre[ta] = tb;
            num[tb] += num[ta];
            num[ta] = num[tb];
            ans = sum[ta];
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

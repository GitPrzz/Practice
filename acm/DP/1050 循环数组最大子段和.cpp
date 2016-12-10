/*
1050 循环数组最大子段和

最开始考虑的是把数组重复一遍然后在里面找出长度超过n的最大字段和，当感觉有点麻烦

然后发现别人是分成两种情况讨论：
1. 这个最大字段在[1,n]中,直接求出
2. a[n],a[1],a[2]....这种情况   求出[1,n]的最小字段,然后减去即可  (木有想到TAT)

hhh-2016/06/19 10:27:42
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
const int  maxn = 40010;
const int mod = 1e9+7;


ll a[100005];
int main()
{
    int n;
    scanf("%d",&n);
    ll sum = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%I64d",&a[i]);
        sum += a[i];
    }
    ll manx = 0;
    ll minx = 0x3fffffff;
    ll sum_min = 0;
    ll sum_max = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i == 1)
        {
            sum_min = a[i];
            sum_max = a[i];
        }
        else
        {
            if(sum_min > 0)
            {
                sum_min = 0;
            }
            if(sum_max < 0)
            {
                sum_max = 0;
            }
            sum_min += a[i];
            sum_max += a[i];
            manx = max(manx,sum_max);
            minx = min(minx,sum_min);
        }
    }
    printf("%I64d\n",max(manx,sum-minx));
    return 0;
}

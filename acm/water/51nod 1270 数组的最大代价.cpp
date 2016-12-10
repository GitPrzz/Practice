/*
51nod 1270 数组的最大代价

problem:
数组A包含N个元素A1, A2......AN。数组B包含N个元素B1, B2......BN。并且数组A中的每一个元素Ai，都满足1 <= Ai <= Bi。
数组A的代价定义如下：
两个相邻元素A的差的绝对值之和

solve:
按照贪心的思路来,感觉肯定是取 B[i]或者1.  所以第i步的情况应该是由i-1推过来的.
但是写的时候,觉得如果第i位如果取最大值,那么i-1就取最小值mdzz,所以少了一些情况. 实际上i-1的最大最小值都应该考虑.

hhh-2016/09/03 13:32:28
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
const ll mod = 1e9+7;
const int maxn = 50010;
const double PI = acos(-1.0);

ll dp[maxn][2];
ll a[maxn];
int main()
{
    int n;
    while(scanfi(n) != EOF)
    {
        clr(dp,0);
        for(int i = 1;i <= n;i++)
        {
            scanfl(a[i]);
        }
//        dp[1][1] = a[1];
//        dp[1][0] = 1;
        for(int i =2; i<=n;i++)
        {
            dp[i][1] = dp[i-1][0] + a[i] - 1LL;
            dp[i][0] = dp[i-1][1] + a[i-1] - 1LL;
            dp[i][1] = max(dp[i-1][1] + (a[i] - a[i-1]),dp[i][1]);
            dp[i][0] = max(dp[i-1][0],dp[i][0]);
        }
        printf("%I64d\n",max(dp[n][0],dp[n][1]));
    }
    return 0;
}

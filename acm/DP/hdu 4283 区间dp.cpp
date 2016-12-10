/*
hdu 4283 区间dp

problem:
给定一个序列，序列内的人有值Di，然后将这个序列的人进栈，第i个人如果是第k个出栈，那么最后的总值增加
Di*(k-1), 求一个出栈序列使得总值最小。

solve:
对于[1,n]而言,如果1是第k个出栈,那么[2,k]肯定比1先出栈,[k+1,n]肯定比1后出栈.于是求能划分出子区间
所以可以用区间DP解决,只是在合并的时候需要处理

study:http://blog.csdn.net/woshi250hua/article/details/7969225
2016-08-17 16:57:17
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
int dp[105][105];
int a[maxn];
int sum[maxn];

int main()
{
//    freopen("in.txt","r",stdin);
    int T,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        sum[0] = 0;
        printf("Case #%d: ",cas++);
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
        {
            for(int j = i + 1;j <= n;j++)
                dp[i][j] = inf;
        }
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            sum[i] = sum[i-1] + a[i];
//            cout << a[i] << endl;
        }

        for(int lgd = 1; lgd <  n; lgd++)
        {
            for(int i = 1; i + lgd <= n; i++)
            {
                int j = i + lgd;
                for(int k = i; k <= j; k++)
                {
                    int tp = (k-i)*a[i];
                    tp += dp[i+1][k] + dp[k+1][j];
                    tp += (k-i+1)*(sum[j] - sum[k]);
                    dp[i][j] = min(dp[i][j],tp);
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}

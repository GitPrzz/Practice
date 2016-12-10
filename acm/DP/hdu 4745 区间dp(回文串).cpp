/*
hdu 4745 区间dp(回文串)
problem:
给n个数的环装东西，A、B两人沿相反的方向走，每单位时间走一步，要求相同时间两人到达相同的数，
且同一位置同一个人不能走两次，走过的位置不能越过
solve:
因为可以越过没有走过的部分,最开始想的是直接找个回文子串再加1即可(从案例看出)。但是发现如果旁边也是
一个回文子串也可以,所以相当于找两个互不影响的尽可能长的回文子串
hhh-2016-08-17 20:54:39
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
int dp[maxn][maxn];
int a[maxn];
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n) != EOF && n)
    {
        memset(dp,0,sizeof(dp));
        for(int i =1;i <= n;i++)
        {
            scanf("%d",&a[i]);
            dp[i][i] = 1;
        }

        for(int len = 1;len <= n;len++)
        {
            for(int i = 1;i+len <= n;i++)
            {
                int j = i + len;
                dp[i][j] = max(dp[i][j],dp[i+1][j]);
                dp[i][j] = max(dp[i][j],dp[i][j-1]);
                if(a[i] == a[j])
                    dp[i][j] = max(dp[i][j],dp[i+1][j-1]+2);
//                cout << "i:" <<i <<" j:"<<j<<" "<<dp[i][j]<<endl;
            }
        }
        int ans = 0;
        for(int i =1;i <=n;i++)
        {
            ans = max(ans,dp[1][i]+dp[i+1][n]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

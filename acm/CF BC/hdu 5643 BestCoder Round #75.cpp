/*
hdu 5643 BestCoder Round #75

这个类似于约瑟夫环，至少第i次报i的人被干掉
简单粗暴点就是打表，另外一种就是递推

我们要求的是n个人时最后存活的是谁f[n]
但是我们发现杀掉一个人之后从它的下一位开始重新编号
就成了求f[n-1]的解，所以考虑递推
      i+1                i               i-1
0 1 2 3 4 5 6 7  -> 1 2 3 4 5 6 7 -> 1 3 4 5 6 7
                    0 1 2 3 4 5 6    5 0 1 2 3 4
对于第i次而言，我们要干掉第n-i+1个人,而且会从下一位重新编号
所以i->i+1时  每个数的编号相对增加了n-i+1  然后进行取模即可
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 5005;
int dp[maxn];
int main()
{
    int T,m,n;
    scanf("%d",&T);
    while(T--)
    {
        dp[1] = 0;
        scanf("%d",&n);
        for(int i = 2; i <= n; i++)
        {
            dp[i] = (dp[i-1]+n-i+1)%i;
        }
        dp[n] += 1;
        printf("%d\n",dp[n]);
    }
    return 0;
}

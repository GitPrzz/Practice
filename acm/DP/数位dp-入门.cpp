/*
数位dp-入门

给出一个区间，问这个区间内的数，转换成B进制后，刚好有k个1的的数有多少个。

假设把二进制从高位到低位排到二叉树上面,便能预处理出f[i][j]在第i层有j个1所有可能(即第i位是0的情况)
从高到低位进行枚举,如果遇1则加上f[i][j](第i位取0),然后将走过的数目加1(继续查找第i为取1的情况)
如果遇到的数大于1,则说明当前位置一直到0都可以任取,所以加上f[i+1][j]

hhh-2016-04-08 22:00:41
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
const int maxn = 100;
int a,b,k,m;
int f[maxn][maxn];
int bit[maxn];

int cal(int cur,int c,int tot)
{
    int t = 0;
    while(cur)
    {
        bit[t++] = cur%c;
        cur /= c;
    }
    int ans = 0;
    int now = 0;
    for(int i = t-1; i >= 0; i--)
    {
        if(i == 0 && tot == now)
            ans ++;
        if(bit[i] > 1)
        {
            ans += f[i+1][tot-now];
            break;
        }
        if(bit[i] == 1)
        {
            if(i >= tot-now)
                ans += f[i][tot-now];
            now++;
            if(now > tot)
                break;
        }
    }
    return ans;
}

void ini()
{
    f[0][0]=1;
    for (int i=1; i<=31; ++i)
    {
        f[i][0]=f[i-1][0];
        for (int j=1; j<=i; ++j)
            f[i][j]=f[i-1][j]+f[i-1][j-1];
    }
}

int main()
{
    ini();
    while(scanf("%d%d%d%d",&a,&b,&k,&m) != EOF)
    {
        printf("%d\n",cal(b,m,k) - cal(a-1,m,k));
    }
    return 0;
}

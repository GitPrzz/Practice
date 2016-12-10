/*
hdu 4569 数学思考(G)
f[x] = (a1*x^n + ...... + an+1)
求x的值使f[x]%(M*M)=0

①f[x]%(M*M) = 0  ->  ②f[x]%M = 0 -> f[x+k*M]%M = 0;
所以只需要枚举[0,M],如果满足②,然后在[i,M*M]之间找出能满足①的
因为过程中要满足②，所以每次增加M。如果没有No Solution

首先感觉没有什么特别的算法可以求解这类问题。而且我们发现是特判
所以一般都是构造或者枚举什么的。假设是枚举答案的话，我们不知道什么
时候停下(没有结果时)，所以很有可能我们能从公式中得出答案的范围从而
缩小范围得出结果

hhh-2016-03-06 17:44:39
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 50;
int a[maxn];
int MOD;
int n;
bool can(ll t,int mod)
{
    ll cnt = 0;
    t %= mod;
    ll q=1;
    for(int i = 0;i <= n;i++)
    {
        cnt =(cnt+q*(a[n-i])%mod+mod)%mod;
        q = q*t;
    }
    return (cnt%mod == 0);
}

int main()
{
    int t,cas=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 0;i <= n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&MOD);
        int flag =0 ;
        int ans ;
        for(int i =0;i < MOD;i++)
        {
            if(can(i,MOD))
            {
                for(int j = i;j <= MOD*MOD;j += MOD)
                if(can(j,MOD*MOD))
                {
                    ans = j;
                    flag =1;break;
                }
            }
        }
        printf("Case #%d: ",cas++);
        if(flag)
            printf("%d\n",ans);
        else
            printf("No solution!\n");
    }
    return 0;
}

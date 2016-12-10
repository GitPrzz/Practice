/*
hdu 5750 Dertouzos 素数

problem:
求n里面最大约数(不包含自身)为d的个数

solve:
如果是最大约数,那么另一个数必定数质数. 所以就是求最大的质数x,满足 x*d<n
但是有可能d的最小质数比x小: 4000 1000  ---> x = 3.   但实际上当x = 3时, 3*1000 = 3000 = 2*1500
所以还要求d的最小质数,最较小的即可.

hhh-2016-08-29 16:46:41
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
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 1e9
using namespace std;
const ll mod = 1e9+7;
const int maxn = 1000005;

int prime[maxn+100];
void get_prime()
{
    clr(prime,0);
    for(int i =2; i <= maxn; i++)
    {
        if(!prime[i]) prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && prime[j] <= maxn/i; j++)
        {
            prime[prime[j]*i] = 1;
            if(i%prime[j] == 0) break;
        }
    }
}


int main()
{
    int T,n,d;
    int ans,tans;
    get_prime();
    scanfi(T);
    while(T--)
    {
        scanfi(n),scanfi(d);
        int limit = min(d,n/d);

        tans = ans = 0;
        if(prime[1] * d >= n)
        {
            printf("0\n");
            continue;
        }
        for(int i = 1; i <= prime[0]; i++)
        {
            if(d % prime[i] == 0)
            {
                ans = i;
                break;
            }
            else
            {
                if(prime[i]*d < n && prime[i+1]*d >= n)
                {
                    ans = i;
                    break;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

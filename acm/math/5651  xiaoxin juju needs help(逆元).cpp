/*
5651  xiaoxin juju needs help(逆元)

给你n个字母，求可以组成的回文串的个数
1.n为奇数,有一个字母的个数为奇数
2.n为偶数,字母个数全为偶数

然后将字母的个数num[i]/2,得出在对称轴左边的个项字母的个数
假设左边有len个字母,如果每个字母都不同则有len!中可能
然后除去所有重复的可能num[i]!即可
因为除法取模 (len!/num[i]!)%mod
a^(p-1) = 1(mod p) 于是 a*a^(p-2) = 1(mod p)所以a^(p-2)替代1/a.
所以上面的公式  ->  len!*(num[i]!)^(p-2)%mod

hhh-2016-03-26 21:45:56
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
const int maxn = 20050;
const int mod = 1e9+7;
int a[maxn];

char Ma[maxn];
int Mp[maxn];
int num[26];

ll pow_mod(ll a,ll n)
{
    ll t = 1;
    while(n)
    {
        if(n & 1) t = t*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return t;
}

ll cal(int t)
{
    ll ans = 1;
    for(int i =1;i <= num[t];i++)
    {
        ans = ans*i%mod;
    }
    return pow_mod(ans%mod,mod-2);
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",Ma);
        int sum = 0;
        int len = strlen(Ma);
        memset(num,0,sizeof(num));
        for(int i = 0; i < len; i++)
        {
            Mp[i] = Ma[i]-'a';
            if(num[Mp[i]] == 0)
                sum ++;
            num[Mp[i]]++;
        }
        int flag = 0;
        int t;
        for(int i = 0; i < 26; i++)
        {
            if(num[i]%2)
            {
                flag ++;
                t = num[i];
            }
        }
        if((len%2 && !flag) || (len%2==0 && flag) || (flag > 2))
            printf("0\n");
        else if(len == 1)
            printf("1\n");
        else
        {
            ll ans = 1;
            for(int i =1;i <= len/2;i++)
                ans = ans*i%mod;
            for(int i = 0;i < 26;i++)
            {
                if(num[i])
                {
                    num[i] /= 2;
                    ans = ans*cal(i)%mod;
                }
            }
            printf("%I64d\n",ans);
        }

    }
    return 0;
}

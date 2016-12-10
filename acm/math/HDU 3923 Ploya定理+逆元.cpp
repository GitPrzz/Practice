/*
HDU 3923 Ploya定理+逆元

裸Polya计数,只是在后面求个逆元即可

hhh-2016-04-19 11:40:12
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <math.h>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int maxn = 100040;
const int mod = 1000000007;
ll euler(ll n)
{
    ll ans = n;
    for(int i = 2;i*i <= n;i++)
    {
        if(n % i == 0)
        {
            ans -= ans/i;
            while(n % i == 0)
            {
                n /= i;
            }
        }
    }
    if(n > 1) ans -= ans/n;
    return ans%mod;
}

ll Pow(ll a, ll b)
{
    ll res = 1;
    a %= mod;
    while(b)
    {
        if(b&1) res =res*a%mod;
        a = a*a%mod;
        b >>= 1;
    }
    return res%mod;
}

ll polya(ll n,ll k)
{
    ll ans = 0;
    for(ll i = 1; i <= n; i++)
    {
        if(n % i == 0)   //枚举循环节的长度
        ans =(ans+Pow(k,i)*euler(n/i)%mod)%mod;
    }

    if(n & 1)
        ans =(ans+Pow(k,n/2+1)*n%mod)%mod;
    else
    {
        ans = (ans+Pow(k,n/2)*(n/2)%mod)%mod;
        ans = (ans+Pow(k,n/2+1)*(n/2)%mod)%mod;
    }
   ll t = Pow(n*2,mod-2);     //求逆元
    return ans*t%mod;
}

int main()
{
    ll n,c;
    int T,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d",&c,&n);
        printf("Case #%d: ",cas++);
        printf("%I64d\n",polya(n,c));
    }
    return 0;
}

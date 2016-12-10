/*
2015 ICL, Finals, Div. 1 Ceizenpok’s formula（组合数取模，扩展lucas定理）

求C(n,k)%m
如果m是素数的话直接就能套lucas模板.
对于m为合数,我们可以把它分解成素数在进行处理 m = p1*p2*p3..pk   (pk = prime[i]^t)
然后利用扩展lucas定理可以求出  C(n,k) % pi的值，最后利用中国剩余定理

涨姿势：http://www.cnblogs.com/jianglangcaijin/p/3446839.html
题目链接：http://codeforces.com/gym/100633/problem/J
hhh-2016-04-16 13:07:05
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
typedef long long ll;
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;

const int maxn = 1e6+10;
ll fac[maxn];
int w[maxn],num[maxn],tw[maxn];
int tot;
void get_factor(ll m)
{
    ll mm = m;
    tot = 0;
    for(ll i = 2; i*i <= m; i++)
    {
        if(mm % i == 0)
        {
            num[tot] = 0;
            w[tot] = i;
            tw[tot] = 1;
            while(mm % i == 0)
            {
                num[tot]++;
                mm /= i;
                tw[tot] *= i;
            }
            tot++;
        }
    }
    if(mm > 1)
    {
        num[tot] = 1;
        w[tot] = mm;
        tw[tot] = mm;
        tot ++;
    }
}

ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
    if(a == 0 && b == 0)
        return -1;
    if(b == 0)
    {
        x = 1,y = 0;
        return a;
    }
    ll d = ex_gcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
}

ll pow_mod(ll a,ll b,ll mod)
{
    ll ret = 1;
    while(b)
    {
        if(b&1) ret = ret*a%mod;
        a = a*a%mod;
        b >>= 1;
    }
    return ret;
}

ll revers(ll a,ll b)
{
    ll x,y;
    ll d = ex_gcd(a,b,x,y);
    if(d == 1) return (x%b+b)%b;
    else return 0;
}

ll c1(ll n,ll p,ll pk)
{
    if(n==0)return 1;
    ll ans=1;
    for(ll i = 2; i <= pk; i++)
        if(i % p)
            ans = ans*i%pk;
    ans=pow_mod(ans,n/pk,pk);
    for(ll k=n%pk,i=2; i<=k; i++)if(i%p)ans=ans*i%pk;
    return ans*c1(n/p,p,pk)%pk;
}

ll cal(ll n,ll m,int cur,ll mod)
{
    ll pi = w[cur],pk = tw[cur];
    ll k = 0,ans;
    ll a,b,c;
    a=c1(n,pi,pk),b=c1(m,pi,pk),c=c1(n-m,pi,pk);

    for(ll i=n; i; i/=pi)k+=i/pi;
    for(ll i=m; i; i/=pi)k-=i/pi;
    for(ll i=n-m; i; i/=pi)k-=i/pi;

    ans = a*revers(b,pk)%pk*revers(c,pk)%pk*pow_mod(pi,k,pk)%pk;
    return ans*(mod/pk)%mod*revers(mod/pk,pk)%mod;
}

ll lucas(ll n,ll m,ll mod)
{
    ll ans = 0;
    for(int i = 0; i < tot; i++)
    {
        ans = (ans+cal(n,m,i,mod))%mod;
    }
    return ans;
}


ll n,k;
ll m;
int main()
{
    int T;
    while(scanf("%I64d%I64d%I64d",&n,&k,&m) != EOF)
    {
        get_factor(m);
        printf("%I64d\n",lucas(n,k,m));
    }
    return 0;
}



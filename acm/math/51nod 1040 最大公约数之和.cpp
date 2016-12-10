/*
51nod 1040 最大公约数之和（欧拉函数）

给你n,然后求[1-n]所有数与n的最大公约数的和
n的最大公约数必定是n的因子v，所以考虑枚举因子分别求他们的个数num，那么因子v对答案的贡献就是v*num
相当于求[1-n]中 GCD(a[i],n) = v的个数,也就成了GCD(a[i]/v,n/v)=1的个数。 欧拉函数求出即可。

欧拉函数：[1-n]中 gcd[i,n]=x的个数

hhh-2016/05/27  11:09:03
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
const int maxn = 1040;
typedef long long ll;
ll eular(ll n)
{
    ll ans=1;
    for(ll i=2; i*i<=n; i++)
    {
        if(n%i==0)
        {
            n/=i;
            ans*=i-1;
            while(n%i==0)
            {
                n/=i;
                ans*=i;
            }
        }
    }
    if(n>1)
        ans*=n-1;
    return ans;
}

int main()
{
    ll x;
    scanf("%I64d",&x);
    ll ans = 0;
    for(ll i = 1 ; i*i <= x; i++)
    {
        if(x % i != 0)
            continue;
        ll t = x/i;
        ans += i*eular(t);
        //cout << i  << ": " << eular(t) << endl;
        if(i != t)
        {
            ans += (t)*eular(x/t);
            //cout << t  << ": " << eular(x/t) << endl;
        }
    }
    printf("%I64d\n",ans);
}

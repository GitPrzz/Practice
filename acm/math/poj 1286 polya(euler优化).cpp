/*
poj 1286 polya(euler�Ż�)

������ģ���⣬ֻ������������Ż�
�Ż���(����)
��ǰ����ֱ��ö��i����⡣  ���ǿ��Կ���ͨ��ö��ѭ���ڵĳ���L,Ȼ������ж��ٸ�i
L = n/(GCD(n,i))  ->   GCD(n,i) = n/L
������ a = n/L = GCD(n,i) , ������ i = a*t  -> GCD(n,i) = GCD(a*L,a*t) = a
����ֻ�� GCD(L,t) = 1�ǲ��С�  0 �� i <n --->   0 �� t < L(n/a)
��С��L����L���ʵĸ���,�����ŷ���������

hhh-2016-04-19 11:14:49
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
    return ans;
}

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}
ll Pow(ll a, ll b)
{
    ll res = 1;
    while(b)
    {
        if(b&1) res *= a;
        a = a*a;
        b >>= 1;
    }
    return res;
}

ll polya(ll n,ll k)
{
    ll ans = 0;
    for(ll i = 1; i <= n; i++)
    {
        if(n % i == 0)   //ö��ѭ���ڵĳ���
        ans += Pow(k,i)*euler(n/i);
    }

    if(n & 1)
        ans  += Pow(k,n/2+1)*n;
    else
    {
        ans += Pow(k,n/2)*(n/2);
        ans += Pow(k,n/2+1)*(n/2);
    }
    return ans/(n*2);
}

int main()
{
    ll n;
    while(scanf("%I64d",&n) != EOF)
    {
        if(n == -1)
            break;
        if(n == 0)
            printf("0\n");
        else
        printf("%I64d\n",polya(n,3));
    }
    return 0;
}

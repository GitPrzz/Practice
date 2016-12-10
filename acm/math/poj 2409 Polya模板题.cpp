/*
poj 2409 Polyaģ����

��ת��
L = sum(k^Ci)/n(i = 0,1.....n-1)      ���ÿ����תiλ�ĺ�
˳ʱ����תi����û���,ѭ���ĸ���ΪGCD(n,i),����Ϊn/GCD(n,i).
so Ci = GCD(n,i)

��ת��
��nΪż��ʱ,n/2�����û�Ci = n/2�� n/2�����û�Ci = n/2-1
��nΪ����ʱ,n���û�Ci = n/2+1

hhh-2016-04-19 10:06:23
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

ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}
ll pow(ll a, ll b)
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
    for(int i = 1; i <= n; i++)
    {
        ans += pow(k,gcd(n,i));
    }

    if(n & 1)
        ans  += pow(k,n/2+1)*n;
    else
    {
        ans += pow(k,n/2)*(n/2);
        ans += pow(k,n/2+1)*(n/2);
    }
    return ans/(n*2);
}

int main()
{
    ll n,c;
    while(scanf("%I64d%I64d",&c,&n) != EOF)
    {
        if(!n && !c)
            break;
        printf("%I64d\n",polya(n,c));
    }
    return 0;
}

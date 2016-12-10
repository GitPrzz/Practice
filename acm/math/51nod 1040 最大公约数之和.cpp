/*
51nod 1040 ���Լ��֮�ͣ�ŷ��������

����n,Ȼ����[1-n]��������n�����Լ���ĺ�
n�����Լ���ض���n������v�����Կ���ö�����ӷֱ������ǵĸ���num����ô����v�Դ𰸵Ĺ��׾���v*num
�൱����[1-n]�� GCD(a[i],n) = v�ĸ���,Ҳ�ͳ���GCD(a[i]/v,n/v)=1�ĸ����� ŷ������������ɡ�

ŷ��������[1-n]�� gcd[i,n]=x�ĸ���

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

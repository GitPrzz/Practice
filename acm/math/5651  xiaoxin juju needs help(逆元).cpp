/*
5651  xiaoxin juju needs help(��Ԫ)

����n����ĸ���������ɵĻ��Ĵ��ĸ���
1.nΪ����,��һ����ĸ�ĸ���Ϊ����
2.nΪż��,��ĸ����ȫΪż��

Ȼ����ĸ�ĸ���num[i]/2,�ó��ڶԳ�����ߵĸ�����ĸ�ĸ���
���������len����ĸ,���ÿ����ĸ����ͬ����len!�п���
Ȼ���ȥ�����ظ��Ŀ���num[i]!����
��Ϊ����ȡģ (len!/num[i]!)%mod
a^(p-1) = 1(mod p) ���� a*a^(p-2) = 1(mod p)����a^(p-2)���1/a.
��������Ĺ�ʽ  ->  len!*(num[i]!)^(p-2)%mod

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

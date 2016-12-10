/*
poj 2888 Magic Bracelet(Polya+矩阵快速幂)

给你m个不同的珠子组成一个长度为n的项链   (个人理解),只考虑旋转的情况下总共能够成
多少种不同的项链。 而且规定有的珠子不能挨在一起

大致还是Polya计数,只是要想办法解决找出长度为i的循环节有多少个。于是乎可以考虑
矩阵快速幂(一个经典问题：解决m步从a走到b的方案数)

主要是一直TLE,知道后来把euler改成通过素数求才过- -.   而且取模过多好像也会TLE

hhh-2016-04-19 22:31:42
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
//typedef long long ll;
using namespace std;
const int  maxn = 40010;
struct Matrix
{
    int ma[12][12];
};

int n,m;
int isprime[maxn];
int prime[maxn];
int pnum;
void get_prime()
{;
    pnum = 0;
    memset(isprime, -1, sizeof(isprime));
    for(int i = 2; i <= maxn-10; i ++)
        if(isprime[i])
        {
            prime[pnum ++] = i;
            for(int j = i * i; j <= maxn-10; j += i)
                isprime[j] = 0;
        }
}

Matrix mult(Matrix ta,Matrix tb, int mod)
{
    Matrix tc;
    memset(tc.ma,0,sizeof(tc.ma));
    for(int i = 0; i < m; i ++)
        for(int k = 0; k < m; k ++)
            if(ta.ma[i][k])
            {
                for(int j = 0; j < m; j ++)
                    if(tb.ma[k][j])
                        tc.ma[i][j] = (tc.ma[i][j] + ta.ma[i][k] * tb.ma[k][j]) % mod;
            }
    return tc;
}

Matrix Mat_pow(Matrix ta,int n,int mod)
{
    Matrix t;
    memset(t.ma,0,sizeof(t.ma));
    for(int i = 0; i < m; i++)
        t.ma[i][i] = 1;
    while(n)
    {
        if(n & 1) t = mult(t,ta,mod);
        ta = mult(ta,ta,mod);
        n >>= 1;
    }
    return t;
}

int pow_mod(int a,int n,int mod)
{
    int ret = 1;
    a %= mod;
    while(n)
    {
        if(n & 1) ret = ret*a,ret%=mod;
        a = a*a;
        a%=mod;
        n >>= 1;
    }
    return ret;
}
int mod;
int euler(int cur )
{
    int ans, x;
    ans = x = cur;
    for(int i = 0; i < pnum && prime[i] * prime[i] <= cur; i++)
        if(x % prime[i] == 0)
        {
            ans = ans / prime[i] * (prime[i] - 1);
            while(x % prime[i] == 0)
                x /= prime[i];
        }
    if(x > 1)
        ans = ans / x * (x - 1);
    return ans%mod;
}

Matrix mat;
int cal(int len)
{
    int ret = 0;
    Matrix t = Mat_pow(mat,len,mod);
    for(int i = 0; i < m; i++)
        ret = ret + t.ma[i][i];
    ret %= mod;

    return ret;
}

int Polya(int n)
{
    int ans = 0;
    for(int i= 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            if(i*i == n)
            {
                ans = ans+cal(i)*euler(i);
                ans%=mod;
            }
            else
            {
                ans = (ans+cal(i)*euler(n/i)+cal(n/i)*euler(i));
                ans%=mod;
            }
        }
    }
    ans = ans*pow_mod(n,mod-2,mod);
    return ans % mod;
}

int main()
{
    int T;
    get_prime();
    mod = 9973;
    scanf("%d",&T);
    while(T--)
    {
        int k;
        scanf("%d%d%d",&n,&m,&k);
        int u,v;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < m; j++)
                mat.ma[i][j] = 1;
        for(int i = 1; i <= k; i++)
        {
            scanf("%d%d",&u,&v);
            mat.ma[u-1][v-1] = mat.ma[v-1][u-1] = 0;
        }
        printf("%d\n",Polya(n));
    }
    return 0;
}

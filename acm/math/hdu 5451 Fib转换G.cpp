/*
hdu 5451 Fib转换G
在公式转换上还是有很大问题
感觉是很不错的Fib数的递推，如果能把公式转换好就能出，还有就是循环节上的问题
hhh-2016-02-23 11:18:44
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long  double ld;

const int maxn = 200010;

struct Matrix
{
    ll ma[2][2];
};


Matrix mult(Matrix a,Matrix b,ll mod)
{
    Matrix c;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            c.ma[i][j]=0;
            for(int k = 0; k < 2; k++)
                c.ma[i][j] = (c.ma[i][j]+a.ma[i][k]*b.ma[k][j]%mod)%mod;
        }
    }
    return c;
}


Matrix Matrix_pow(Matrix a,ll n,ll mod)
{
    if(n == 1)
        return a;
    else if(n & 1)
        return mult(a,Matrix_pow(a,n-1,mod),mod);
    else
    {
        Matrix t = Matrix_pow(a,n>>1,mod);
        return mult(t,t,mod);

    }
}
ll pow_mod(ll a,ll n,ll mod)
{
    ll tmp = 1;
    a %= mod;
    while(n)
    {
        if(n & 1)
            tmp = tmp*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return tmp;
}


int main()
{
    int T,cas = 1;
    ll n,mod;
    Matrix star;
    scanf("%d",&T);
    while(T--)
    {
        star.ma[0][0] = 5;
        star.ma[0][1] = 12;
        star.ma[1][0] = 2;
        star.ma[1][1] = 5;
        scanf("%I64d%I64d",&n,&mod);
        ll tt = pow_mod(2,n,(mod-1)*(mod+1))+1;
        Matrix ans = Matrix_pow(star,tt,mod);
        printf("Case #%d: %I64d\n",cas++,(ans.ma[0][0]*2-1)%mod);
    }
    return 0;
}

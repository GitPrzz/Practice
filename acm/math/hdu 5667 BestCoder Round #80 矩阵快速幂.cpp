/*
hdu 5667 BestCoder Round #80 矩阵快速幂

F[n] = 1 (n == 1)
F[n] = a^b (n == 2)
F[n] = a^b * F[n-1]^c *F [n-2]

最开始试了下化简公式,但是无果. 也从矩阵快速幂上面考虑过(毕竟 F[n]与 F[n-1],F[n-2]有关)
但是发现是 乘法运算不知道怎么弄了(2b了)

能够发现运算时基于a的次方的,当a的次方相乘时就变成了他们的次方相加 (好气 TAT)
于是乎 a^g[n] = a^(b + c*g[n-1] * g[n-2])
然后用类似快速幂求斐波那契数的方法即可

F[n]    F[n-1] 1         C  1  0
F[n-1]  F[n-2] 1    *    1  0  0
                         b  0  1
hhh-2016-04-18 20:36:40
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

struct Matrix
{
    ll ma[3][3];
    Matrix()
    {
        memset(ma,0,sizeof(ma));
    }
};

Matrix mult(Matrix ta,Matrix tb, ll mod)
{
    Matrix tc;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            tc.ma[i][j] = 0;
            for(int k = 0; k < 3; k++){
                tc.ma[i][j] += (ta.ma[i][k] * tb.ma[k][j])%mod;
                tc.ma[i][j] %= mod;
            }
        }
    }
    return tc;
}

Matrix Mat_pow(Matrix ta,ll n,ll mod)
{
    Matrix t;
    for(int i = 0; i < 3; i++)
        t.ma[i][i] = 1;
    while(n)
    {
        if(n & 1) t = mult(t,ta,mod);
        ta = mult(ta,ta,mod);
        n >>= 1;
    }
    return t;
}

ll pow_mod(ll a,ll n,ll mod)
{
    ll t = 1;
    a %= mod ;
    while(n)
    {
        if(n & 1) t = t*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return t;
}

Matrix mat;
Matrix an;
ll a,b,c;
void ini(ll mod)
{
    mat.ma[0][0] = c,mat.ma[0][1] = 1,mat.ma[0][2] = 0;
    mat.ma[1][0] = 1,mat.ma[1][1] = 0,mat.ma[1][2] = 0;
    mat.ma[2][0] = b,mat.ma[2][1] = 0,mat.ma[2][2] = 1;


    an.ma[0][0] = (b+b*c%mod)%mod,an.ma[0][1] = b,an.ma[0][2] = 1;
    an.ma[1][0] = b,an.ma[1][1] = 0,an.ma[2][1] = 1;
}
ll mod,n;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d%I64d%I64d%I64d",&n,&a,&b,&c,&mod);
        a%=mod,b%=mod,c%=mod;
        ini(mod-1);
        if(n == 1)
        {
            printf("1\n");
        }
        else if(n == 2)
            printf("%I64d\n",pow_mod(a,b,mod));
        else
        {
            mat = Mat_pow(mat,n-3,mod-1);
            mat = mult(an,mat,mod-1);
            ll ci = mat.ma[0][0];
            //cout << ci <<endl;
            printf("%I64d\n",pow_mod(a,ci,mod));
        }
    }
    return 0;
}

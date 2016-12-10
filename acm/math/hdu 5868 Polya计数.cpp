/*
hdu 5868 Polya计数

problem:
给你n个人,围绕成圆坐下,任意两人之间的距离必需是2pi/n的倍数.求旋转等效的情况下有多少种方案数

solve:
相当于给你n个间距为2pi/n的点,然后进行黑白染色,黑点不能相邻. (黑点表示坐人)
考虑Polya计数的话,需要枚举长度且得到长度为i的方案数.
找规律可以发现 f[n] = f[n-1] + f[n-2],用矩阵快速幂可以快速求出

hhh-2016-09-20 19:26:01
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 200100;
const int inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
struct Matrix
{
    ll ma[2][2];
    Matrix()
    {
        memset(ma,0,sizeof(ma));
    }
};

Matrix mat;
Matrix from;

Matrix Mul(Matrix a,Matrix b)
{
    Matrix c;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            c.ma[i][j] = 0;
            for(int k = 0; k < 2; k++)
            {
                c.ma[i][j] = c.ma[i][j] + a.ma[i][k]*b.ma[k][j] % mod;
                c.ma[i][j] %= mod;
            }
        }
    }
    return c;
}

Matrix Pow(int n)
{
    Matrix cnt;
    Matrix t = mat;
    memset(cnt.ma,0,sizeof(cnt.ma));
    for(int i = 0; i < 2; i++)
        cnt.ma[i][i] = 1;
    while(n)
    {
        if(n & 1)
            cnt = Mul(cnt,t);
        t = Mul(t,t);
        n >>= 1;
    }
    return cnt;
}

void init()
{
mat.ma[0][0] = 1,mat.ma[0][1] = 1,mat.ma[1][0] = 1,mat.ma[1][1] = 0;
    from.ma[0][0] = 3,from.ma[1][0] = 1,from.ma[0][1] = 0,from.ma[1][1] = 0;
}
int n;
ll f(int i)
{
    if(i == 1)
         return 1;
    if(i == 2)
        return 3;
    Matrix t = Mul(Pow(i-2),from);
    return t.ma[0][0];
}

ll pow_mod(ll a,ll n)
{
    ll ret = 1;
    a %= mod;
    while(n)
    {
        if(n & 1) ret = ret*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return ret%mod;
}

ll euler(ll n)
{
    ll ans = n;
    ll i;
    for (i = 2; i*i <= n; i++)
    {
        if (n%i == 0)
        {
            while (n%i == 0)
                n /= i;
            ans = ans/i*(i-1) ;
        }
    }
    if (n != 1)
        ans = ans/n*(n-1);
    return ans;
}


void cal(int n)
{
    if(n == 1)
    {
        printf("2\n");
        return ;
    }
    ll ans = 0;
    for(int i = 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            ans = (ans + f(i)*euler(n/i)%mod)%mod;
            if( i*i != n)
            {
                ans = (ans + f(n/i)*euler(i)%mod)%mod;
            }
        }
    }
//    cout <<ans <<endl;
    ans = ans*pow_mod(n,mod-2)%mod;
    printf("%I64d\n",ans);
}

int main()
{
    init();
//    for(int i =1 ;i <= 10;i++)
//        cout << f(i) <<endl;
//    for(int i =1 ;i <= 10;i++)
//        cout << euler(i) <<endl;
    while(scanf("%d",&n) != EOF)
    {
        init();
        cal(n);
    }
}

/*
hdu 5895  广义Fibonacci数列

problem:
求x^g(n*y)%(s+1)的值. f(0)=0,f(1)=1,f(n)=f(n−2)+2∗f(n−1) g(n)是前n项f的平方和

solve:
因为n*y很大,所以可以通过欧拉降幂.  而且找规律发现g(n*y) = f(n*y)*f(n*y+1)/2
所以可以通过矩阵快速幂求出这两个值,然后用求个逆元

hhh-2016-09-19 20:00:04
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const double PI = acos(-1.0);
ll mod ;
struct Matri
{
    ll a[2][2];
};
Matri Mat;
Matri from;
Matri Mul(Matri A,Matri B)
{
    Matri c;
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            c.a[i][j]=0;
            for(int k=0; k<2; k++)
            {
                c.a[i][j]=(c.a[i][j]+((A.a[i][k]%mod)*(B.a[k][j]%mod)))%mod;
            }
        }
    }
    return c;
}
ll Euler (ll n)
{
    ll i,ans=n;
    for (i=2; i*i<=n; i++) if (n%i==0)
        {
            ans=ans/i*(i-1);
            while (n%i==0) n/=i;
        }
    if (n>1) ans=ans/n*(n-1);
    return ans;
}
Matri Pow(ll n)
{
    Matri t ;
    Matri ta = Mat ;
    t.a[0][0] = t.a[1][1] = 1;
    t.a[1][0] = t.a[0][1] = 0;
    while(n)
    {
        if(n & 1) t = Mul(t,ta);
        ta = Mul(ta,ta);
        n >>= 1;
    }
    return t;
}
Matri Add(Matri a,Matri b)
{
    Matri c;
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            c.a[i][j]=a.a[i][j]+b.a[i][j];
            c.a[i][j]%=mod;
        }
    }
    return c;
}
ll PowerMod(ll a, ll b, ll c)
{

    ll ans = 1;
    ll k = a % c;
    while(b>0)
    {
        if(b % 2 == 1)
            ans = ((ans%c)*(k%c)) % c;
        b = b/2;
        k = ((k% c )* (k% c) )% c;
    }
    return ans;

}
void solve(char *s,ll &ans)
{
    ans = 0;
    for(unsigned int i = 0; i < strlen(s); i++)
    {
        ans = ans*10 + (s[i] - '0');
    }
}
char str1[10],str2[10],str3[10];
int main()
{

    ll x,y,s,n;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(from.a,0,sizeof(from.a));
        from.a[0][0] = 1;
        Mat.a[0][0] = 2,Mat.a[0][1] = 1,Mat.a[1][1] = 0,Mat.a[1][0] = 1;
        scanf("%s%s%s%I64d",str1,str2,str3,&s);
        solve(str1,n),solve(str2,y),solve(str3,x);
        if(n*y == 0)
        {
            printf("1\n");
            continue;
        }
        mod = Euler(s+1LL);
        mod*=2LL;
        Matri tp = Mul(Pow(n*y-1LL),from);
        Matri tp1 = Mul(Pow(n*y),from);
        ll ta = tp.a[0][0]*tp1.a[0][0]%mod;
        ta=ta%(mod)/2LL;
        ll to = ta+mod;
        printf("%I64d\n",PowerMod(x,to,s+1LL));
    }
    return 0;
}

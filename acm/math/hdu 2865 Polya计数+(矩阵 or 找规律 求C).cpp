/*
hdu 2865 Polya����+(���� or �ҹ��� ��C)

����n��С��ȫ������һ��������Ȼ������ǽ���Ⱦɫ��Ҫ������������ɫ��һ��
����ȷ������Ϊһ����ɫ(k�ֿ���)��Ȼ����ʣ��k-1����Polyaȥ����С�򼴿�

�ڼ���ѭ���ڳ���Ϊi�Ŀ�����ʱ����k�ܴ�,��������ݺ����Բ�����
1.���Կ��ǵ���,�����һ����ɫ��x,��f[i][1]��ʾ��ǰ��ɫ��x,f[i][0]��ʾ��ǰ��ɫ��x��
f[i][1] = f[i-1][0]
f[i][0] = (k-2)*f[i-1][0]+(k-1)*f[i-1][1]

2.������3����ɫȾѭ���ڳ���ΪlenС��,���������ľ�����
0 1 1     2 1 1      2 3 3      6 5 5    10 11 11
1 0 1 ->  1 2 1  ->  3 2 3  ->  5 6 5 -> 11 10 11
1 1 0     1 1 2      3 3 2      5 5 6    11 11 10
�����ο���cxlove����.
���Է������й��ɵģ�(2 = 3-1)
n = 1  ->   0   (2^n - 2)
n = 2  ->   6   (2^n + 2)
n = 3  ->   6   (2^n - 2)
n = 4  ->   18  (2^n + 2)
n = 5  ->   30  (2^n - 2)
����Ϊע�Ͳ���

hhh-2016-04-22 10:12:35
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
using namespace std;
const ll mod = 1e9 + 7;
const int  maxn = 40010;

int num;
int prime[maxn];
int isPrime[maxn];

void get_prime()
{
    num = 0;
    memset(isPrime,0,sizeof(isPrime));
    for(int i = 2; i <= maxn-10; i++)
    {
        if(!isPrime[i])
        {
            prime[num++] = i;
            for(int j = i+i; j <= maxn-10; j+=i)
                isPrime[j] = 1;
        }
    }
}

ll euler(ll cur)
{
    ll ans = cur;
    ll x = cur;
    for(int i = 0; i < num && prime[i]*prime[i] <= cur; i++)
    {
        if(x % prime[i] == 0)
        {
            ans = ans/prime[i]*(prime[i]-1);
            while(x % prime[i] == 0)
                x /= prime[i];
        }
    }
    if(x > 1)
    {
        ans = ans/x*(x-1);
    }
    return ans%mod;
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


/*
another:
ll solve(ll p,ll k)
{
    ll ans=pow_mod(p-1,k);
    if(k&1)
        ans=(ans+mod-(p-1))%mod;
    else
        ans=(ans+p-1)%mod;
    return ans;
}
*/


struct Matrix
{
    ll ma[3][3];
    Matrix()
    {
        memset(ma,0,sizeof(ma));
    }
};

Matrix mult(Matrix ta,Matrix tb)
{
    Matrix tc;
    for(int i = 0 ; i < 2; i ++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 2; k++)
                tc.ma[i][j] = (tc.ma[i][j] + ta.ma[i][k]*tb.ma[k][j]%mod)%mod;
        }
    }
    return tc;
}

Matrix Mat_mod(Matrix a,int n)
{
    Matrix cnt;
    for(int i = 0; i < 2; i++)
        cnt.ma[i][i] = 1;
    while(n)
    {
        if(n & 1 ) cnt = mult(cnt,a);
        a = mult(a,a);
        n >>= 1;
    }
    return cnt;
}

Matrix mat;
Matrix begi;

ll solve(ll p,ll k)
{
    begi.ma[0][1] = 1,begi.ma[0][0] = 0,begi.ma[1][0] = 0,begi.ma[1][1] = 0;
    mat.ma[0][0] = p - 2, mat.ma[1][0] = p - 1, mat.ma[0][1] = 1, mat.ma[1][1] = 0;
    mat = Mat_mod(mat,k-1);
    Matrix tp = mult(begi,mat);
    return p*tp.ma[0][0]%mod;
}

ll cal(ll  n,ll k)
{
    ll ans = 0;
    for(int i = 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            ans = (ans + solve(k,n/i)*euler(i)%mod)%mod;
            if(n != i*i)
                ans = (ans + solve(k,i)*euler(n/i)%mod)%mod;
        }
    }
    return (ans*pow_mod(n,mod-2))%mod;
}

ll N,k;

int main()
{
    get_prime();
    while(scanf("%I64d%I64d",&N,&k) != EOF)
    {
        printf("%I64d\n",k*cal(N,k-1)%mod);
    }
    return 0;
}

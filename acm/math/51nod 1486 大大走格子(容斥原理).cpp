/*
51nod 1486 大大走格子(容斥原理)

problem:
有一个h行w列的棋盘，里面有一些格子是不能走的，现在要求从左上角走到右下角的方案数。只能往右 或者 往下

solve:
很明显用所有的方案数减去经过黑点的方案数就是答案. 而有可以重复计算,所以容斥一下.
然后就没什么想法了, 主要是觉得方案数不怎么好求(结果发现可以直接组合数解决...GG)
容斥计算出每个黑点到左上角的方案数, ans[i] - sum(ans[j] * f(j,i) while j < i) f来表示i,j之间的方案数
所以把h,w加入黑点全部求一遍.

hhh-2016/09/26-21:12:09
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <math.h>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 1e6 + 1000;
const int inf = 0x3f3f3f3f;
const ll mod = 1000000007;
const double eps = 1e-7;
template<class T> void read(T&num)
{
    char CH;
    bool F=false;
    for(CH=getchar(); CH<'0'||CH>'9'; F= CH=='-',CH=getchar());
    for(num=0; CH>='0'&&CH<='9'; num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p)
{
    if(!p)
    {
        puts("0");
        return;
    }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}

ll pow_mod(ll a,ll n)
{
    ll cnt = 1;
    ll t = a % mod;

    while(n)
    {
        if(n & 1) cnt = cnt * t % mod;
        t = t*t%mod;
        n >>= 1;
    }
    return cnt;
}

int h,w,n;
ll ans[maxn];
ll fac[maxn];
ll inv[maxn];
struct node
{
    int a,b;
}x[maxn];
bool cmp(node u,node v)
{
    if(u.a != v.a)
        return u.a < v.a;
    else
        return u.b < v.b;
}

int main()
{
    read(h),read(w),read(n);
    for(int i = 0;i < n;i++)
    {
        read(x[i].a),read(x[i].b);
    }
    x[n].a = h,x[n].b= w;
//    for(int i = 0;i <= n;i++)
//        cout << x[i].a << " " <<x[i].b <<endl;
    fac[0] = inv[0] = 1;
    fac[1] = 1,inv[1] = 1;
    sort(x , x + n + 1,cmp);
    for(int i = 2;i <= h + w;i++)
    {
        fac[i] = fac[i-1] * i % mod;
        inv[i] = pow_mod(fac[i],mod-2);
    }
    for(int i = 0;i <= n;i++)
    {
        int tx = x[i].a,ty = x[i].b;
        ans[i] = fac[tx + ty-2] * inv[tx-1]%mod * inv[ty-1] % mod;
        for(int j = 0;j < i;j++)
        {
            if(x[j].a <= x[i].a && x[j].b <= x[i].b)
            {
                 int tu = x[j].a,tv = x[j].b;
                 ans[i] = (ans[i] - ans[j]*fac[tx-tu+ty-tv] % mod * inv[tx-tu]%mod*inv[ty-tv]%mod)%mod;
            }

        }
        while(ans[i] < 0)
           ans[i] += mod;
        ans[i] %= mod;
    }
//    for(int i = 0;i < n;i++)
//        print(ans[i]);
    print(ans[n]);
    return 0;
}

/*
hdu 5830 FFT + cdq分治

problem:
已知长度为i的shells有a[i]种. 求组成长度为n的方案数
f[i]=∑(f[i - j] * a[j]), j∈[1, i];
让你求f[n] % Z

学习参考:http://blog.csdn.net/snowy_smile/article/details/52020971
solve:
首先卷积求出来之后坐标和相等的在同一列.
a1 a2 a3
b1 b2 b3
-->>
a1*b1 a2*b1 a3*b1 |
      a1*b2 a2*b2 | a3*b2
            a1*b3 | a2*b3 a3*b3
所以可以解决多项式为f[i]=∑(f[i - j] * a[j])这种的问题.但是如果直接暴力的话
必需要n次fft递推出f[n].

通过上面那个卷积公式可以发现当我们计算f[4]的时候,已经把后面一部分的答案计算了出来.
所以我们可以在计算[l,mid]的时候处理出f[l,mid]对[mid,r]的所有贡献. 那么剩下的就只需要在
[mid,r]中处理就行了.也就是CDQ分治了

hhh-2016-09-22 21:21:08
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
const int maxn = 1 << 18;
const int inf = 0x3f3f3f3f;
const int mod = 313;
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

const double PI = acos(-1.0);

struct Complex
{
    double x,y;
    Complex(double _x = 0.0,double _y = 0.0)
    {
        x = _x;
        y = _y;
    }
    Complex operator-(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator+(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator*(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};

void change(Complex y[],int len)
{
    int i,j,k;
    for(i = 1,j = len/2; i < len-1; i++)
    {
        if(i < j) swap(y[i],y[j]);
        k = len/2;
        while(j >= k)
        {
            j-=k;
            k/=2;
        }
        if(j < k) j+=k;
    }
}

void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h = 2; h <= len; h <<= 1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j = 0; j < len; j+=h)
        {
            Complex w(1,0);
            for(int k = j; k < j+h/2; k++)
            {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+ t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
    {
        for(int i = 0; i < len; i++)
            y[i].x /= len;
    }
}

double dis(int a,int b)
{
    return sqrt(a*a + b*b);
}

Complex a[maxn];
Complex b[maxn];
int ans[maxn];
int ta[maxn];

void cal(int l,int r)
{
    if(l == r)
    {
        ans[l] = (ans[l]+ta[l])%mod;
        return;
    }
    int mid = (l + r) >> 1;
    cal(l,mid);
    int len1 = mid-l + 1;
    int len2 = r-l + 1;
    int len = 1;
    while(len < (len1 + len2)) len <<= 1;
    for(int i = 0;i < len1;i++) a[i] = ans[l+i];
    for(int i = len1;i < len;i++) a[i] = 0;
    fft(a,len,1);
    for(int i = 0;i < len2;i++) b[i] = ta[i];
    for(int i = len2;i < len;i++) b[i] = 0;
    fft(b,len,1);

    for(int i = 0;i < len;i++)
        a[i] = a[i] * b[i];
    fft(a,len,-1);

    for(int i = mid + 1;i <= r ;i++)
        ans[i] = (ans[i] + int(a[i-l].x + 0.5))%mod;

    cal(mid+1,r);
}

int main()
{
    int n;
    while(scanf("%d",&n ) != EOF && n)
    {
        memset(ans,0,sizeof(ans));
        for(int i = 1; i <= n;i++){
            scanf("%d",&ta[i]);
            ta[i] %= mod;
        }
        cal(1,n);
        print(ans[n]);
    }
    return 0;
}

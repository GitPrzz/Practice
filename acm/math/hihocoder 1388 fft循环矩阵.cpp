/*
hihocoder 1388 fft循环矩阵

problem:
给你两个数组,求差值平方和的最小值.  (a[i] - b[(i+k)%n])^

solve:
可以转换成 (a[i]*a[i]-2*a[i]*b[j]+b[j]*b[j]). 也就成了求a[i]*b[j]的最大值. 然后就没什么想法了- -
参考：http://blog.csdn.net/VictorZC8/article/details/52655099
说的是可以转换成两个数组相乘. 这样的话fft就能解决了. double型的话会有精度问题
结果发现别人是先求fft求完,比较出k的价值. 然后计算 ( 好机制Orz )

hhh-2016-09-25 16:53:25
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
const ll mod = 1e9 + 7;
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

Complex a[maxn];
Complex b[maxn];
ll x[maxn],y[maxn];
int n;

void File()
{
    freopen("in.txt","r",stdin);
}

int main()
{
    int T;
//    File();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int len = 1;
        while(len <= (n*2 -1)) len <<= 1;
        for(int i = 0;i < n;i++)
        {
            scanf("%lld",&x[i]);
            a[i] = x[i];
        }
        for(int i = n;i < len;i++)
            a[i] = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%lld",&y[i]);
        }
        for(int i = 0;i < n;i++) b[i] = y[n-1-i];
        for(int i = 0;i < n-1;i++) b[i+n] = y[n-1-i];
        for(int i = 2*n-1;i < len;i ++)
            b[i] = 0;
        fft(a,len,1);
        fft(b,len,1);

        for(int i = 0;i < len;i++)
            a[i] = a[i] * b[i];

        fft(a,len,-1);
        ll Max = -1;
        int pos = 0;
        for(int i = n-1,j = 0;j <= n;j++ )
        {
            if( (ll)(a[i+j].x + 0.5) > Max)
            {
                pos = j;
                Max = (ll)(a[i+j].x + 0.5);
            }
        }
        ll ans = 0;
        pos = (n-pos) % n;
//        cout << pos<<endl;

        for(int i = 0;i < n;i++)
        {
            ans += (x[i] - y[(i + pos) % n])*(x[i] - y[(i + pos) % n]);
        }
        print(ans);
    }
    return 0;
}

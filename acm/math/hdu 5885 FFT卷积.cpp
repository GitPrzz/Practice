/*
hdu 5885 FFT���

problem:
����һ��n��m�ĸ���,������С�ڵ���r����Щ���Ӷ��ṱ��p(i,j)/(d+1), dΪ�������ӵľ���. p[i][j]Ϊ���ӵļ�ֵ
ѡ��һ������, ʹ�ù��׺����.

solve:
�ο���https://async.icpc-camp.org/d/558-2016-icpc
��ΪС��r�ĸ��Ӷ������ǰ���ӹ���, ���Կ��Կ����ȼ�������и��Ӷ�<r���������ӵĹ���.��ô���һ�α��������ҳ�
�����ֵ.��ô�ᴦ�����һ�� (n+r+r,m+r+r)�ľ���.
Ȼ�������μ���, ����(i,j)����(x,y)�ƶ���ᵽ����(i+x,j+y).�������
��������з������һ��һά����,��ô��ǰ����������˺��λ�þ��ǵ�ǰ���ܵ����Ŀ��λ��(������������)
��ת����һά.
0*M+0 0*M+1 0*M+2
0*M+0 0*M+1 0*M+2 1*M+0 ...   (����)
---->
0*M+0 0*M+1 0*M+2 1*M+0
      0*M+1 0*M+2 1*M+0
����������֮���Ǵ���һ����ϵ��.������A,B�������ж���a+b=c�������˼��.  (�¼���get)
(���������˺ܾòŶ� TAT.. )
��a[i*M + j]����p(i,j), b[i*M+j]���� 1/d.
c = a*b, ��ô��i*M + j����i,j�Ĺ��׺�.

�����ʼ�õ�m���Ƿ���������,��Ϊһ�д������m+2*r����,����M�ͺ���....
hhh-2016-09-21 21:10:30
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

double dis(int a,int b)
{
    return sqrt(a*a + b*b);
}

Complex a[2*maxn];
Complex b[2*maxn];

int main()
{
    int k;
    int n,m,limit;
    double x,r;
    while(scanf("%d%d%lf",&n,&m,&r) != EOF)
    {
        limit =0, k = 1;
        while(r >= limit)
        {
            limit ++ ;
        }
        limit -= 1;
        int M = m +limit + limit;
        while(k < (n+r+r)*(m+r+r))
           k <<= 1;

        for(int i = 0;i < k;i++)
        {
            a[i] = b[i] = 0;
        }
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++)
            {
                read(x);
                a[i*M + j] = x;
            }
        }
        fft(a,k,1);
        for(int i = -limit;i <= limit;i++)
        {
            for(int j = -limit;j <= limit;j++)
            {
                double len = dis(i,j);
                if( r > len)
                b[(i+limit) * M + j + limit] = 1.0/(len+1);

            }
        }

        fft(b,k,1);
        for(int i = 0;i < k;i++)
            a[i] = a[i] * b[i];
        fft(a,k,-1);
        double ans = 0;
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < m;j++)
            {
                ans = max(ans,a[(i + limit) * M + j + limit].x);
            }
        }
        printf("%.3f\n",ans);
    }
    return 0;
}

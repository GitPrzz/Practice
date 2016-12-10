/*
hdu 2855 矩阵快速幂+Fib+二项式定理

给你n,m  求 C(n,i)*F[i]的和. F为斐波那契数列
(1+x)^n = C(n,0)*x^n+C(n,1)*x^(n-1)+C(n,2)x^(n-2)+····+C(n,n)*1
而且Fib可以通过矩阵快速幂来求。  所以可以把x看成
|1 1|
|1 0|
所以把1看成单位矩阵进行即可
hhh-2016-05-03 21:49:22
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int  maxn = 40010;
int tot;
int mod;
struct Matrix
{
    int ma[2][2];
};

Matrix mult(Matrix ta,Matrix tb)
{
    Matrix tc;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            tc.ma[i][j] = 0;
            for(int k = 0; k < 2; k++)
            {
                tc.ma[i][j] = tc.ma[i][j]+ta.ma[i][k]*tb.ma[k][j]%mod;
                tc.ma[i][j] %= mod;
            }
        }
    }
    return tc;
}
Matrix cnt;
Matrix pow_mat(Matrix a,int n)
{
    while(n)
    {
        if(n&1) cnt = mult(cnt,a);
        a = mult(a,a);
        n >>= 1;
    }
    return cnt;
}
Matrix mat;

void ini()
{
    mat.ma[0][0] = 2,mat.ma[0][1] = 1;
    mat.ma[1][0] = 1,mat.ma[1][1] = 1;

    cnt.ma[0][0] = 1,cnt.ma[0][1] = 0;
    cnt.ma[1][0] = 0,cnt.ma[1][1] = 0;
}



int main()
{
    int n,T;

    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d",&n);
        scanf("%d",&mod);
        if(n == 0)
        {
            printf("0\n");
            continue;
        }
        pow_mat(mat,n);
        printf("%d\n",cnt.ma[0][1]);
    }
    return 0;
}

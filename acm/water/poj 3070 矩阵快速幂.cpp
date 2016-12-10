/*
poj 3070 ¾ØÕó¿ìËÙÃÝ
hhh-2016-02-20 02:23:49
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
const int MOD = 10000;
struct matrix
{
    int ma[2][2];
};


matrix mult(matrix a,matrix b)
{
    matrix c;
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            c.ma[i][j] = 0;
            for(int k = 0; k < 2; k++)
                c.ma[i][j] = (c.ma[i][j]+a.ma[i][k]*b.ma[k][j]%MOD)%MOD;
        }
    }
    return c;
}

matrix Pow(matrix Mat,int n)
{
    if(n==1)
        return Mat;
    else if(n&1)
    {
        return mult(Mat,Pow(Mat,n-1));
    }
    else
    {
        matrix temp=Pow(Mat,n>>1);
        return mult(temp,temp);
    }
}

int main()
{
    matrix in;
    in.ma[0][0] = 1;
    in.ma[0][1] = 1;
    in.ma[1][0] = 1;
    in.ma[1][1] = 0;
    int n ;
    while(scanf("%d",&n) != EOF)
    {
        if(n == -1)
            break;
        matrix ans = Pow(in,n+1);
//        for(int i = 0; i < 2; i++)
//        {
//            for(int j = 0; j < 2; j++)
//                printf("%d ",ans.ma[i][j]);
//            printf("\n");
//        }
        printf("%d\n",ans.ma[1][1]%10000);
    }
    return 0;
}

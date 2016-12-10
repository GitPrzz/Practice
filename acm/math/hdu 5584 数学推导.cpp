/*
hdu 5584 ��ѧ�Ƶ�

����x yÿ�ο����� x+z y  or  x y+z;(zΪx,y�����Լ��)
����x=ka y=kb  ->��һ��   x1=ka y1=kb+kab=kb(a+1) gcd(x1,y1) = k
����ͨ��x1 y1�������x y
�ݹ��жϼ���

hhh-2016-03-07 15:25:59

*/
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

const long long MOD = 1000000007;

int gcd(int x,int y)
{
    while(x % y)
    {
        int t = y;
        y = x%y;
        x = t;
    }
    return y;
}

int main()
{
    int t, n, cas = 1;
    scanf("%d", &t);
    int a,b;
    while(t--)
    {
        scanf("%d%d",&a,&b);

        if(a > b)swap(a,b);
        int k = gcd(a,b);
        int ans = 1;
        while(a%k==0 && b%(k*(1+a/k)) == 0)
        {
            int x1 = a/k;
            int x2 = b/k/(x1+1);
            b = x2*k;
            if(a > b)
                swap(a,b);
            k = gcd(a,b);
            ans ++;
        }
        printf("Case #%d: %d\n",cas++,ans);
    }
    return 0;
}

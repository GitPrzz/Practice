/*
hdu 5584 数学推导

给你x y每次可以走 x+z y  or  x y+z;(z为x,y的最大公约数)
假设x=ka y=kb  ->下一步   x1=ka y1=kb+kab=kb(a+1) gcd(x1,y1) = k
所以通过x1 y1可以求出x y
递归判断即可

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

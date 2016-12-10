/*
HDU 4497 合数分解(ggg)

有三个数，已经知道了GCD(x,y,z)和LCM(x,y,z),求总共有多少种可能
假设m = LCM/GCD,则m可以看成质因数的乘积，而这些质因子来自这三个数
假设m分解成p1^t1 * p2^t2 * p3^t3..
x = p1^i1 * p2^i2 * p3^i3 *...
y = p1^j1 * p2^j2 * p3^j3 *...
z = p1^k1 * p2^k2 * p3^k3 *...

因为最大公约数已经被除去了,所以i1,j1,k1中必定有0和t1
所以对于p1有三种可能
0 0 t1  3
0 t1 t1 3
0 t1 1~t1-1 6*(t1-1)
所以对每一个质因子而言，有6*t1中可能
而质因子之间没有影响，所以相乘即可

参考：http://www.cnblogs.com/liuxueyang/archive/2013/08/26/3281680.html

hhh-2016-03-06 21:40:15
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)

const int MOD = 1e9 + 7;
int main()
{
    int t,n;
    int a,b;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&a,&b);
        if(b % a)
            printf("0\n");
        else
        {
            int t = b/a;
            int ans = 1;
            for(int i = 2; i <= t; i++)
            {
                if(t % i == 0)
                {
                    int num = 0;
                    while(t % i == 0)
                    {
                        t /= i;
                        num++;
                    }
                    ans = ans*num*6;
                }
            }
            if(t != 1)
                ans *= 6;
            printf("%d\n",ans);
        }
    }
    return 0;
}

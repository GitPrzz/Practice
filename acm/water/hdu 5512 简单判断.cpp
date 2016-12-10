/*
hdu 5512
如果有一个为1或者两个互质，那么全可以修。
如果不互质，n/(gcd(a，b))
1到n个塔，Yuwgna和Iaka两人从a，b两点开始修建塔，每次可以修建塔的位置i=j+k或i=j-k；
j和k为已修建好的塔的位置，Yuwgna开始修，最后谁不能修了谁就输了，问最后谁赢。
hhh-2016-02-19 18:19:36
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

const int maxn = 20005;

int gcd(int a,int b)
{
    while(a % b!=0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return b;
}

int main()
{
    int T,n,a,b;
    scanf("%d",&T);
    int cas = 1;
    while(T--)
    {

        scanf("%d%d%d",&n,&a,&b);
        printf("Case #%d: ",cas++);
        int flag;
        if(a == 1 || b == 1 || gcd(a,b) == 1)
        {
            if(n%2)
                flag = 1;
            else
                flag = 0;
        }
        else
        {
            int t = gcd(a,b);
            if(n/t % 2)
                flag = 1;
            else
                flag = 0;
            //printf("gcd:%d\n",t);
        }
        if(flag)
            printf("Yuwgna\n");
        else
            printf("Iaka\n");
    }
    return 0;
}

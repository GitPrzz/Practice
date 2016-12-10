/*
hdu 5491 二进制
将l转换成进制，求下一个二进制1的数目在[a,b]之间的
先找出小于b的 如果大于a直接输出，否知将1填上输出
主要是细节方面出了问题
最开始写的是 ans += tans[i]*tt，但是tans是int所以乘出来估计溢出了= =
hhh-2016-02-19 21:58:16
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
const int maxn = 100;
int tans[maxn],tot;
ll get_num(ll x)
{
    ll t = x;
    tot = 0;
    ll ans = 0;
    while(t)
    {
        tans[tot] = t % 2;
        if(t%2)
            ans ++;
        t /= 2;
        tot ++;
//        if(t == 0)
//            break;
    }
    return ans;
}

void prin()
{
    for(int i = 0; i < tot; i++)
        printf("%d",tans[i]);
    printf("\n");
}

int main()
{
    int T,cas,l,a,b;
    cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        memset(tans,0,sizeof(tans));
        scanf("%d%d%d",&l,&a,&b);
        printf("Case #%d: ",cas++);

        ll x = l+1,t;
        while(1)
        {
            t = get_num(x);
            //pri();
            if(t <= b)
                break;
            x++;
        }
        if(t < a)
        {
            int ned = a - t;
            for(int i = 0;i < maxn; i++)
            {
                if(tans[i] == 0)
                {
                    tans[i] = 1;
                    ned--;
                }
                if(!ned)
                    break;

            }
        }
        ll ans = 0;
        ll tt = 1;
        for(int i = 0; i < maxn; i++)
        {
            if(tans[i])
                ans += tt;
            tt <<= 1;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

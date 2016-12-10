/*
Binary Tree
因为n <= 2^k，可以依靠最左边的树枝解决问题,只是在最后一步走左右进行一下判断就好
2016-02-24 18:08:35
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
typedef long  double ld;
const int maxn = 65;

int op[maxn];
int main()
{
    int T,cas =1,k;
    ll n;
    scanf("%d",&T);
    while(T--)
    {
        memset(op,0,sizeof(op));
        scanf("%I64d%d",&n,&k);
        ll tans = 1<<k;
//        cout << tans<<endl;
        printf("Case #%d:\n",cas++);
        ll t = tans-1-n,tot = 0;
        int flag = 0;
        if(t % 2 != 0) {t++;flag =1;}
        t /= 2;
        while(t)
        {
            op[tot++] = t%2;
            t /= 2;
        }
        ll ans = 1;
        for(int i = 0; i < k-1; i++)
        {
            printf("%I64d %c\n",ans,op[i] == 1? '-':'+');
            ans *= 2;
        }
        if(flag) ans += 1;
        printf("%I64d %c\n",ans,op[k-1] == 1? '-':'+');
    }
    return 0;
}

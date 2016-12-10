/*
poj2975 Nim 胜利的方案数

nim游戏是异或和不为0的时候，是必胜的。
例：先手人员可以先拿一个，然后异或和为0，然后对手拿多少，你就拿多少。
从而达到必胜的。
1011     ------>      1010
1010     拿一个       1010

这个是求总共有多少种必胜的方法，开始想的是通过SG值来计算，但是数范围太大
结果还是从nim的原理上分析
如果我们从一个人那个哪走一部分，从而使剩下的所有的异或和为0
那么取的 那一堆的数量    ta[i] > 剩下其它碓的异或和
所以可以依靠这个来判断胜利的方法数量。

hhh-2016-08-01 20:16:14
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f;
const int maxn = 1000100;

//int vis[22];
//int sg[maxn];
//
//int SG(int cur)
//{
//    memset(vis,0,sizeof(vis));
//    for(int i = 1;i <= cur;i++)
//    {
//        if( (i^cur) < cur)
//        {
//            vis[sg[cur-i]] = true;
//        }
//    }
//    for(int i = 0 ; i <= 20; i++)
//    {
//        if(!vis[i])
//            return i;
//    }
//    return 0;
//}

ll ta[maxn];

int main()
{
    int n ;
    while(scanf("%d",&n) != EOF && n)
    {
        ll ans = 0;
        int tans = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%I64d",&ta[i]);
            ans ^= ta[i];
        }
        for(int i = 0;i < n;i++)
        {
            if( (ans ^ ta[i]) < ta[i])
                tans ++;
        }
        printf("%d\n",tans);
    }
    return 0;
}

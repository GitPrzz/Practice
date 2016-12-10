/*
hdu 5445 多重背包

problem:
给一场运动会提供食物，每种食物提供ti能量，占用vi空间，最多可提供ui个，把食物运到指定地点，每种车可以运送ai体积的
食物，消耗bi的金钱，总共有ci个这种车，问给运动会提供至少p的能量，最少需要花多少运费
(每个食物可以拆开来运)

solve:
可以将其分成两个多重背包计算,先计算出运送指定能量的食物最少需要多少的空间,然后在这个空间的基础上计算最少需要
的花费.结果RE,后来发现这个空间可能很大.
而题目中说了50000这个界限,所以直接计算出50000的花费能够达到的最大空间

hhh-2016-08-17 15:13:15
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
int dp[51000];
int ta,a,c;

void cal_min(int cost,int val,int num,int m)
{
    if(cost * num >= m)
    {
        for(int i = cost; i <= m; i++)
        {
            dp[i] = min(dp[i],dp[i-cost] + val);
        }
    }
    else
    {
        int k = 1;
        while(k < num)
        {
            for(int i = m; i >= cost*k; i--)
                dp[i] = min(dp[i],dp[i-cost*k]+val*k);
            num -= k;
            k *= 2;
        }
        for(int i = m; i >= cost*num; i--)
            dp[i] = min(dp[i],dp[i-cost*num]+val*num);
    }
}

void cal_max(int cost,int val,int num,int m)
{
    if(cost * num >= m)
    {
        for(int i = cost; i <= m; i++)
        {
            dp[i] = max(dp[i],dp[i-cost] + val);
        }
    }
    else
    {
        int k = 1;
        while(k < num)
        {
            for(int i = m; i >= cost*k; i--)
                dp[i] = max(dp[i],dp[i-cost*k]+val*k);
            num -= k;
            k *= 2;
        }
        for(int i = m; i >= cost*num; i--)
            dp[i] = max(dp[i],dp[i-cost*num]+val*num);
    }
}

int main()
{
//    freopen("in.txt","r",stdin);
    int n,m,cnt;
    int T;
    cin >> T;
    while(T--)
    {
        memset(dp,inf,sizeof(dp));
        dp[0] = 0;
        scanf("%d%d%d",&n,&cnt,&m);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d%d",&a,&c,&ta);
            cal_min(a,c,ta,m + 100); //因为每个能量最多100,所以最大界限为m+100
        }
        int minpart = inf;
        for(int i = m; i <= m+100; i++)
        {
            minpart = min(minpart,dp[i]);
        }


//        cout <<"m:" <<m <<"  min:"<<minpart <<endl;
        memset(dp,0,sizeof(dp));
        for(int i = 1; i <= cnt; i++)
        {
            scanf("%d%d%d",&a,&c,&ta);
            cal_max(c,a,ta,50000+100);
        }
        int ans = inf;
        for(int i = 0;i <= 50000;i++){
            if(dp[i] >= minpart)
            {
                ans = i;
                break;
            }
        }
        if(ans == inf)
            printf("TAT\n");
        else
            printf("%d\n",ans);
    }
    return 0;
}

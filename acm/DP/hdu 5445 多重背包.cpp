/*
hdu 5445 ���ر���

problem:
��һ���˶����ṩʳ�ÿ��ʳ���ṩti������ռ��vi�ռ䣬�����ṩui������ʳ���˵�ָ���ص㣬ÿ�ֳ���������ai�����
ʳ�����bi�Ľ�Ǯ���ܹ���ci�����ֳ����ʸ��˶����ṩ����p��������������Ҫ�������˷�
(ÿ��ʳ����Բ�����)

solve:
���Խ���ֳ��������ر�������,�ȼ��������ָ��������ʳ��������Ҫ���ٵĿռ�,Ȼ��������ռ�Ļ����ϼ���������Ҫ
�Ļ���.���RE,������������ռ���ܴܺ�.
����Ŀ��˵��50000�������,����ֱ�Ӽ����50000�Ļ����ܹ��ﵽ�����ռ�

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
            cal_min(a,c,ta,m + 100); //��Ϊÿ���������100,����������Ϊm+100
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

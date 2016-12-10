/*
hdu 5656 CA Loves GCD(n����ѡk�������Լ����)2

����n����,ÿ����ѡk����������GCD,�����в��ظ�����ĺ�

��ʼ���˺ü��ζ�TLE,�䡣
1.����������ǿ�����dp�����,dp[i][j]��ʾǰi������GCDΪj�ĸ������
2.���������������i�ı����ĸ���lan[i],��ô���ĳ�ȡ������2^lan[i]-1
���Դ�������Լ��Ϊi�ķ�����

hhh-2016-04-03 14:29:30
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 1e8+7;
const int maxn = 1005;
int mm = 1000;
int gc[maxn][maxn];
ll dp[maxn][maxn];
int a[maxn];
int gcd(int a,int b)
{
    while(a%b)
    {
        int t = a%b;
        a = b;
        b = t;
    }
    return b;
}

int main()
{
    int n,m;
    int t;
    for(int i = 1; i <= mm; i++)
    {
        for(int j = i; j <= mm; j++)
            gc[i][j] =gc[j][i]= gcd(i,j);
    }
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        for(int i = 1; i <= n; i++)
        {

            for(int j = 1; j <= mm; j++)
            {
                dp[i][j] = (dp[i][j]+dp[i-1][j])%mod;
                dp[i][gc[a[i]][j]] =(dp[i][gc[a[i]][j]]+dp[i-1][j])%mod;
            }
            dp[i][a[i]]++;
        }
        ll ans = 0;
        for(int i = 1; i <= mm; i++)
        {
            ans = (ans+(ll)i*dp[n][i]%mod)%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

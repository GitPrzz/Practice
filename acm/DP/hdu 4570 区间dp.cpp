/*
hdu 4570 ����dp

���⣨�𴦸��ƣ���  һ������Ϊn�����У�����ֳ����ɶΣ�ÿһ�εĳ���Ҫ<=20����  Ҫ���ai*(2^bi)��С������ai��ÿһ��
���еĵ�һ�bi��ÿһ�εĳ��ȡ�

����sample imput  n=7��A={1 2 4 4 5 4 3}������ֳ�1 2 4| 4 5| 4| 3��  �������ÿռ�Ϊ1*2^3+4*2^2+4*2^1+3*2^1=38��
������ֳ�1 2| 4 4 5| 4 3���������ÿռ�Ϊ1*2^2+4*2^3+4*2^2=52����38��

hhh-2016-08-05 10:00:14
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int INF=0x3f3f3f3f;
const int mod = 250000+10;
int tot;
int val[maxn];
ll bin[maxn];
ll dp[maxn][maxn];
int main()
{
    int T,n;
    //freopen("in.txt","r",stdin);
    bin[0] = 1;
    for(int i = 1;i <= 20;i++)
    {
        bin[i] = (ll)bin[i-1] * 2;
    }
    scanf("%d",&T);
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for(int i = 0 ; i < n; i++)
            scanf("%d",&val[i]);
        memset(dp,INF,sizeof(dp));
        for(int l = 1;l <= n;l++)
        {
            for(int i = 0;i < n;i++)
            {
                int j = i + l - 1;
                if(j >= n)
                    break;
                if(l <= 20)
                {
                    dp[i][j] = (ll)val[i]*bin[l];
                }

                for(int k = i;k < j;k++)
                    dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]);
            }
        }
        printf("%I64d\n",dp[0][n-1]);
    }
    return 0;
}

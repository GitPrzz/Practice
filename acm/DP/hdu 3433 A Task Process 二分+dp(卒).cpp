/*
hdu 3433 A Task Process ����+dp(��)

dp����Ͼ�������ʵû�������״̬ת�Ʒ���
��Ҫ�������ر�С,���Կ��Ƕ��ִ�Ȼ��ͨ���ж������
���֪�����ܹ�ʹ�õ�ʱ��limi.����dp[i][j]��ʾǰi�������j��A����ʱ�������ɶ���
��B����
ת�Ʒ��̣�
dp[i][j] = (dp[i-1][j-k] + (limi-k*a[i])*b[i],dp[i][j])

hhh-2016-04-10 21:02:38
*/
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
using namespace std;
const int mod = 1e9+7;
const int maxn = 205;
int a[maxn],b[maxn];
int x,y,n;
int dp[maxn][maxn];
bool cal(int limi)
{
    //dp[i][j] ǰi�������j��A����������,�����ɶ��ٸ�B
    memset(dp,-1,sizeof(dp));
    for(int i =0; i <= x && i*a[1] <= limi; i++)
    {
        dp[1][i] = (limi-i*a[1])/b[1];
    }

    for(int i = 2; i <= n; i++)
    {
        for(int j = 0; j <= x; j++)
        {
            for(int k = 0; k*a[i] <= limi && k <= j; k++)
            {
                if(dp[i-1][j-k] >= 0)
                    dp[i][j] = max(dp[i][j],dp[i-1][j-k]+(limi-k*a[i])/b[i]);
                //�������ͬһ������,��ô��������ͬʱ����
            }
        }
    }
    return dp[n][x] >= y;
}

int main()
{
    int T;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&x,&y);
        int ma = 0;
        for(int i =1 ; i <= n; i++)
        {
            scanf("%d%d",&a[i],&b[i]);
            ma = max(ma,a[i]);
        }
        int l = 0,r = ma*x;
        int ans = 0;
        while(l <= r)
        {
            int mid = (l+r)>>1;

            if(cal(mid))
            {
                ans = mid;
                r = mid-1;
            }
            else
                l = mid + 1;
        }
        printf("Case %d: %d\n",cas++,ans);
    }
    return 0;
}

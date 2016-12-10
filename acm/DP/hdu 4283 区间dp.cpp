/*
hdu 4283 ����dp

problem:
����һ�����У������ڵ�����ֵDi��Ȼ��������е��˽�ջ����i��������ǵ�k����ջ����ô������ֵ����
Di*(k-1), ��һ����ջ����ʹ����ֵ��С��

solve:
����[1,n]����,���1�ǵ�k����ջ,��ô[2,k]�϶���1�ȳ�ջ,[k+1,n]�϶���1���ջ.�������ܻ��ֳ�������
���Կ���������DP���,ֻ���ںϲ���ʱ����Ҫ����

study:http://blog.csdn.net/woshi250hua/article/details/7969225
2016-08-17 16:57:17
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
int dp[105][105];
int a[maxn];
int sum[maxn];

int main()
{
//    freopen("in.txt","r",stdin);
    int T,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        sum[0] = 0;
        printf("Case #%d: ",cas++);
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
        {
            for(int j = i + 1;j <= n;j++)
                dp[i][j] = inf;
        }
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            sum[i] = sum[i-1] + a[i];
//            cout << a[i] << endl;
        }

        for(int lgd = 1; lgd <  n; lgd++)
        {
            for(int i = 1; i + lgd <= n; i++)
            {
                int j = i + lgd;
                for(int k = i; k <= j; k++)
                {
                    int tp = (k-i)*a[i];
                    tp += dp[i+1][k] + dp[k+1][j];
                    tp += (k-i+1)*(sum[j] - sum[k]);
                    dp[i][j] = min(dp[i][j],tp);
                }
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}

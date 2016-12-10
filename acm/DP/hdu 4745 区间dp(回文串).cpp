/*
hdu 4745 ����dp(���Ĵ�)
problem:
��n�����Ļ�װ������A��B�������෴�ķ����ߣ�ÿ��λʱ����һ����Ҫ����ͬʱ�����˵�����ͬ������
��ͬһλ��ͬһ���˲��������Σ��߹���λ�ò���Խ��
solve:
��Ϊ����Խ��û���߹��Ĳ���,�ʼ�����ֱ���Ҹ������Ӵ��ټ�1����(�Ӱ�������)�����Ƿ�������Ա�Ҳ��
һ�������Ӵ�Ҳ����,�����൱������������Ӱ��ľ����ܳ��Ļ����Ӵ�
hhh-2016-08-17 20:54:39
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
int dp[maxn][maxn];
int a[maxn];
char str[maxn];
int main()
{
//    freopen("in.txt","r",stdin);
    int n;
    while(scanf("%d",&n) != EOF && n)
    {
        memset(dp,0,sizeof(dp));
        for(int i =1;i <= n;i++)
        {
            scanf("%d",&a[i]);
            dp[i][i] = 1;
        }

        for(int len = 1;len <= n;len++)
        {
            for(int i = 1;i+len <= n;i++)
            {
                int j = i + len;
                dp[i][j] = max(dp[i][j],dp[i+1][j]);
                dp[i][j] = max(dp[i][j],dp[i][j-1]);
                if(a[i] == a[j])
                    dp[i][j] = max(dp[i][j],dp[i+1][j-1]+2);
//                cout << "i:" <<i <<" j:"<<j<<" "<<dp[i][j]<<endl;
            }
        }
        int ans = 0;
        for(int i =1;i <=n;i++)
        {
            ans = max(ans,dp[1][i]+dp[i+1][n]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

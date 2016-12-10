/*
hdu 5534
����n���㹹��һ��������F[d],d����ڵ�Ķȣ�������
���ȸ�ÿ���ڵ�һ���ȣ�Ȼ���ڰ�ʣ�µ�n-2���ȷָ�n���ڵ㼴��
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
typedef long long ll;
typedef long double ld;
const int inf = 0x3f3f3f3f;
const int maxn = 20005;
int dp[maxn];
int p[maxn];
int main()
{
    int n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0 ; i <= n; i++)
            dp[i] = -inf;
        for(int i = 0; i < n-1; i++)
        {
            scanf("%d",&p[i]);
            if(i != 0)
                p[i] -= p[0];
        }
        int all = n-2;
        dp[0] = p[0]*n;
        for(int i = 1; i <= all; i++)
        {
            for(int j =1;j <= i; j++)
                dp[i] =max(dp[i],dp[i-j]+p[j]);
        }
        printf("%d\n",dp[all]);
    }
    return 0;
}

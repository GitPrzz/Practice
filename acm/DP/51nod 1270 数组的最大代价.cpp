/*
51nod 1270 �����������

problem:
����A����N��Ԫ��A1, A2......AN������B����N��Ԫ��B1, B2......BN����������A�е�ÿһ��Ԫ��Ai��������1 <= Ai <= Bi��
����A�Ĵ��۶������£�
��������Ԫ��A�Ĳ�ľ���ֵ֮��

solve:
����̰�ĵ�˼·��,�о��϶���ȡ B[i]����1.  ���Ե�i�������Ӧ������i-1�ƹ�����.
����д��ʱ��,���������iλ���ȡ���ֵ,��ôi-1��ȡ��Сֵmdzz,��������һЩ���. ʵ����i-1�������Сֵ��Ӧ�ÿ���.

hhh-2016/09/03 13:32:28
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 50010;
const double PI = acos(-1.0);

ll dp[maxn][2];
ll a[maxn];
int main()
{
    int n;
    while(scanfi(n) != EOF)
    {
        clr(dp,0);
        for(int i = 1;i <= n;i++)
        {
            scanfl(a[i]);
        }
//        dp[1][1] = a[1];
//        dp[1][0] = 1;
        for(int i =2; i<=n;i++)
        {
            dp[i][1] = dp[i-1][0] + a[i] - 1LL;
            dp[i][0] = dp[i-1][1] + a[i-1] - 1LL;
            dp[i][1] = max(dp[i-1][1] + (a[i] - a[i-1]),dp[i][1]);
            dp[i][0] = max(dp[i-1][0],dp[i][0]);
        }
        printf("%I64d\n",max(dp[n][0],dp[n][1]));
    }
    return 0;
}

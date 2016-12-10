/*
hdu 5643 BestCoder Round #75

���������Լɪ�򻷣����ٵ�i�α�i���˱��ɵ�
�򵥴ֱ�����Ǵ������һ�־��ǵ���

����Ҫ�����n����ʱ��������˭f[n]
�������Ƿ���ɱ��һ����֮���������һλ��ʼ���±��
�ͳ�����f[n-1]�Ľ⣬���Կ��ǵ���
      i+1                i               i-1
0 1 2 3 4 5 6 7  -> 1 2 3 4 5 6 7 -> 1 3 4 5 6 7
                    0 1 2 3 4 5 6    5 0 1 2 3 4
���ڵ�i�ζ��ԣ�����Ҫ�ɵ���n-i+1����,���һ����һλ���±��
����i->i+1ʱ  ÿ�����ı�����������n-i+1  Ȼ�����ȡģ����
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 5005;
int dp[maxn];
int main()
{
    int T,m,n;
    scanf("%d",&T);
    while(T--)
    {
        dp[1] = 0;
        scanf("%d",&n);
        for(int i = 2; i <= n; i++)
        {
            dp[i] = (dp[i-1]+n-i+1)%i;
        }
        dp[n] += 1;
        printf("%d\n",dp[n]);
    }
    return 0;
}

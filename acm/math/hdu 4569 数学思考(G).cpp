/*
hdu 4569 ��ѧ˼��(G)
f[x] = (a1*x^n + ...... + an+1)
��x��ֵʹf[x]%(M*M)=0

��f[x]%(M*M) = 0  ->  ��f[x]%M = 0 -> f[x+k*M]%M = 0;
����ֻ��Ҫö��[0,M],��������,Ȼ����[i,M*M]֮���ҳ�������ٵ�
��Ϊ������Ҫ����ڣ�����ÿ������M�����û��No Solution

���ȸо�û��ʲô�ر���㷨��������������⡣�������Ƿ���������
����һ�㶼�ǹ������ö��ʲô�ġ�������ö�ٴ𰸵Ļ������ǲ�֪��ʲô
ʱ��ͣ��(û�н��ʱ)�����Ժ��п��������ܴӹ�ʽ�еó��𰸵ķ�Χ�Ӷ�
��С��Χ�ó����

hhh-2016-03-06 17:44:39
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 50;
int a[maxn];
int MOD;
int n;
bool can(ll t,int mod)
{
    ll cnt = 0;
    t %= mod;
    ll q=1;
    for(int i = 0;i <= n;i++)
    {
        cnt =(cnt+q*(a[n-i])%mod+mod)%mod;
        q = q*t;
    }
    return (cnt%mod == 0);
}

int main()
{
    int t,cas=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(int i = 0;i <= n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&MOD);
        int flag =0 ;
        int ans ;
        for(int i =0;i < MOD;i++)
        {
            if(can(i,MOD))
            {
                for(int j = i;j <= MOD*MOD;j += MOD)
                if(can(j,MOD*MOD))
                {
                    ans = j;
                    flag =1;break;
                }
            }
        }
        printf("Case #%d: ",cas++);
        if(flag)
            printf("%d\n",ans);
        else
            printf("No solution!\n");
    }
    return 0;
}

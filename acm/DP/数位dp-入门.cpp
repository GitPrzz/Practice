/*
��λdp-����

����һ�����䣬����������ڵ�����ת����B���ƺ󣬸պ���k��1�ĵ����ж��ٸ���

����Ѷ����ƴӸ�λ����λ�ŵ�����������,����Ԥ�����f[i][j]�ڵ�i����j��1���п���(����iλ��0�����)
�Ӹߵ���λ����ö��,�����1�����f[i][j](��iλȡ0),Ȼ���߹�����Ŀ��1(�������ҵ�iΪȡ1�����)
���������������1,��˵����ǰλ��һֱ��0��������ȡ,���Լ���f[i+1][j]

hhh-2016-04-08 22:00:41
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
const int maxn = 100;
int a,b,k,m;
int f[maxn][maxn];
int bit[maxn];

int cal(int cur,int c,int tot)
{
    int t = 0;
    while(cur)
    {
        bit[t++] = cur%c;
        cur /= c;
    }
    int ans = 0;
    int now = 0;
    for(int i = t-1; i >= 0; i--)
    {
        if(i == 0 && tot == now)
            ans ++;
        if(bit[i] > 1)
        {
            ans += f[i+1][tot-now];
            break;
        }
        if(bit[i] == 1)
        {
            if(i >= tot-now)
                ans += f[i][tot-now];
            now++;
            if(now > tot)
                break;
        }
    }
    return ans;
}

void ini()
{
    f[0][0]=1;
    for (int i=1; i<=31; ++i)
    {
        f[i][0]=f[i-1][0];
        for (int j=1; j<=i; ++j)
            f[i][j]=f[i-1][j]+f[i-1][j-1];
    }
}

int main()
{
    ini();
    while(scanf("%d%d%d%d",&a,&b,&k,&m) != EOF)
    {
        printf("%d\n",cal(b,m,k) - cal(a-1,m,k));
    }
    return 0;
}

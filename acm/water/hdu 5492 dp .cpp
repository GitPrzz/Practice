/*
hdu 5492 dp
����һ������������Ͻ��ߵ����½ǵ���С����
��ͨ����ʽ�Ƶ�������ans[i][j][k]��ʾ�ߵ�[i][j]�ܺ�Ϊkƽ����
�ʼֱ���õ�[i][j]��ʾ��С���ѣ����ǲ���- -��
�о����Լ����ǵò�ȫ��ɣ�(N+M-1)*(a[1]*a[1]....+a[n]*a[n]) - (a[1].....+a[n])^2��������̰�ĵ�˼·�õ���Сֵ
���԰�(a[1]......+a[n])��������������ٽ���ö��  nice
hhh-2016-02-20 00:19:32
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn = 33;
int tmap[maxn][maxn];
int ans[maxn][maxn][2000];
int aver;

int main()
{
    int T,cas,n,m;
    cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        memset(ans,0x3f3f3f3f,sizeof(ans));
        scanf("%d%d",&n,&m);

        for(int i =1; i <= n; i++)
            for(int j = 1; j <= m; j++)
            {
                scanf("%d",&tmap[i][j]);
            }
        int con = (n+m-1);
        ans[1][1][tmap[1][1]] = tmap[1][1]*tmap[1][1];
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(i-1>0)
                {
                    for(int k = tmap[i][j]; k <= 59*30; k++)
                        if(ans[i-1][j][k-tmap[i][j]] != 0x3f3f3f3f)
                            ans[i][j][k] = min(ans[i][j][k],ans[i-1][j][k-tmap[i][j]]+tmap[i][j]*tmap[i][j]);
                }
                if(j-1>0)
                {
                    for(int k = tmap[i][j]; k <= 59*30; k++)
                       if(ans[i][j-1][k-tmap[i][j]] != -0x3f3f3f3f)
                            ans[i][j][k] = min(ans[i][j][k],ans[i][j-1][k-tmap[i][j]]+tmap[i][j]*tmap[i][j]);
                }

            }
        }
        int tans = 10000000;
        for(int i = 1; i <= 59*30; i++)
            if(ans[n][m][i] != 0x3f3f3f3f)
                tans = min(tans,ans[n][m][i]*con-i*i);
        printf("Case #%d: %d\n",cas++,tans);
    }
    return 0;
}

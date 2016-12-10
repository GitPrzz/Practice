/*
hdu 5533 暴力
判断是否能够组成正多边形，可以直接暴力枚举
特判：由于给的整数，所以可以发现只有n==4时才能成功
hhh-2016-02-02 05:07:15
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;
const int maxn= 1005;

int x[maxn];
int y[maxn];
double len[maxn][maxn];

double get(int x1,int y1,int x2,int y2 )
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        double tmin = 0x3f3f3f;
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
            scanf("%d%d",&x[i],&y[i]);
        for(int i = 1; i <= n; i++)
            for(int j = i+1 ; j <= n; j++)
            {
                len[i][j] =get(x[i],y[i],x[j],y[j]);
                tmin = min(tmin,len[i][j]);
            }
        int num = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = i+1; j <= n; j++)
                if(tmin == len[i][j])
                    num++;
        }
        if(num == n)
            printf("YES\n");
        else
            printf("NO\n");
    }
}

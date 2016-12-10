/*
HDU 4494 卡输出
感觉心好痛- -
按最简单的来果断gg，输出的时候保留两位而且要判断末尾是否有0
很大的话cout<<double 会变成科学计数法 QAQ
hhh-2016-03-06 16:34:17
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
int vis[maxn][maxn];
int n,k,r,c;
char str[maxn];

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        double ans = 0;
        double x;
        for(int i =1; i <= 12; i++)
        {
            scanf("%lf",&x);
            ans += x;
        }
        ans /= 12.0;
        sprintf(str,"$%.2f",ans);
        int len=strlen(str);
        if(str[len-1] == '0' && str[len-2] =='0')
            str[len-3] = '\0';
        else if(str[len-1] == '0')
            str[len-1] = '\0';
        printf("%s\n",str);
    }
    return 0;
}

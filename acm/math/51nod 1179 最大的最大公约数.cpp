/*
51nod 1179 最大的最大公约数

给你n个数,求他们两两之间公约数的最大值
求出n个数所有的因子并记录它们出现的次数,然后找到其中 num >= 2(有两个数有这个因子) 的最大值即可

hhh-2016/05/26 21:57
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll maxn = 1000010;
const double PI = 3.1415926;
const double eps = 1e-15;
int n;

int num[maxn];
int ans;

int main()
{
    //freopen("in.txt","r",stdin);
    int n,x;
    scanf("%d",&n);
    int Max = 0;
    for(int t = 0;t < n;t++)
    {
        scanf("%d",&x);
        Max = max(x,Max);
        num[1]++;
        num[x]++;
        for(int i = 2; i*i <= x ; i++)
            if(x %i == 0)
            {
                num[i]++;
                num[x/i]++;
            }
    }
    for(int i = Max;i >= 1;i--)
    {
        if(num[i] >= 2)
        {
            ans = i;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}

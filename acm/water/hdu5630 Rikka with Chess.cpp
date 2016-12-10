/*
BestCoder Round #73 (div.2)
hdu5630 Rikka with Chess
思路：
先每次翻转一列，然后每次翻转一行
hhh-2016-02-25 11:27:16
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
typedef long  double ld;
const int maxn = 65;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        printf("%d\n",n/2 + m/2);
    }
    return 0;
}

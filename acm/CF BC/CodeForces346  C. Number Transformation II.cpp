/*
CodeForces346  C. Number Transformation II

给你两个数a,b
1.每次对于当前的a减去1
2.每次对于当前的a减去 a%(ta[i])

求最少多少次能得到b
类似于贪心,每次减去尽可能多的值。但是一直TLE- -.   后来可以发现a~a-a%ta[i]的所有值
如果减去a%ta[i],都会等于同一个值。  如果当a-a%ta[i] < b时,ta[i]可以说在后面的
搜索就没有作用了.于是乎把ta[i]除去.

hhh-2016-04-16 17:15:20
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <math.h>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 1000000009;
const int maxn = 100040;
int ta[maxn];
int main()
{
    int n;
    while( scanf("%d",&n) != EOF)
    {
        int num = 0;
        int a,b;
        for(int i =0; i < n; i++)
        {
            scanf("%d",&ta[i]);
        }
        sort(ta,ta+n);
        n = unique(ta,ta+n)-ta;
        scanf("%d%d",&a,&b);
        while(a > b)
        {
            int cur = a - 1;
            for(int i =n-1; i >= 0; i--)
            {
                if(a-a%ta[i] >= b)
                    cur = min(a-a%ta[i],cur);
            }
            a = cur;
            num ++;
            if(a == b) break;
            while(n)
            {
                if(a-a%ta[n-1] < b)
                    n--;
                else
                    break;
            }
        }
        printf("%d\n",num);
    }
    return 0;
}

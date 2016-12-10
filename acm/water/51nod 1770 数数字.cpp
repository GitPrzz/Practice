/*
51nod 1770 数数字

problem:
给你a,b,d,n. 求n个a与b相乘后其中d的个数

样例解释：3 3 9 10
3333333333*3=9999999999，里面有10个9


solve:
如果两者相乘小于10,那么和d比较进行判断.
否则进行统计,会发现相乘到某一位时,它的进位会一直不变. 即n个a与b相乘后中间有一串
数字是连续的,只要求到这串连续的开始位置即可.
8 7 2 5
--> 62216
hhh-2016/09/03 12:13:07
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
const int maxn = 20010;
const double PI = acos(-1.0);
int num[10];

int main()
{
    int T,a,b,d,n;
    scanfi(T);
    while(T--)
    {
        clr(num,0);
        scanfi(a),scanfi(b),scanfi(d),scanfi(n);
        if(a * b < 10)
        {
            if(d == a*b)
            {
                printf("%d\n",n);
            }
            else
                printf("0\n");
        }
        else
        {
            int preup = -1,up = 0;
            for(int i = 1; i <= n; i++)
            {
                int leave = (a*b+up)%10;
                up = (a*b+up)/10;
                num[leave] ++ ;
                if(up == preup)
                {
                    num[leave] += (n - i);
                    num[up] ++ ;
                    break;
                }
                if(i == n)
                {
                    num[up] ++ ;
                }
                preup = up;
            }
            printf("%d\n",num[d]);
        }
    }
    return 0;
}
/*
10
8 7 2 5
7 7 4 10
5 2 1 1

3
8
1
*/

/*
5650 so easy

首先尝试了一下奇偶是否有区别,然后发现只要是>1的全为0 - -
然后对n==1进行特判即可

hhh-2016-03-26 22:03:46
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
const int maxn = 20050;
int a[maxn];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        if(n == 1)
            printf("%d\n",a[1]);
        else
        printf("0\n");
    }
    return 0;
}

/*
5650 so easy

���ȳ�����һ����ż�Ƿ�������,Ȼ����ֻҪ��>1��ȫΪ0 - -
Ȼ���n==1�������м���

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

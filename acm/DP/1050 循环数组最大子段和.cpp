/*
1050 ѭ����������Ӷκ�

�ʼ���ǵ��ǰ������ظ�һ��Ȼ���������ҳ����ȳ���n������ֶκͣ����о��е��鷳

Ȼ���ֱ����Ƿֳ�����������ۣ�
1. �������ֶ���[1,n]��,ֱ�����
2. a[n],a[1],a[2]....�������   ���[1,n]����С�ֶ�,Ȼ���ȥ����  (ľ���뵽TAT)

hhh-2016/06/19 10:27:42
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
typedef unsigned int ul;
const int INF = 0x3f3f3f3f;
const int  maxn = 40010;
const int mod = 1e9+7;


ll a[100005];
int main()
{
    int n;
    scanf("%d",&n);
    ll sum = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%I64d",&a[i]);
        sum += a[i];
    }
    ll manx = 0;
    ll minx = 0x3fffffff;
    ll sum_min = 0;
    ll sum_max = 0;
    for(int i = 1; i <= n; i++)
    {
        if(i == 1)
        {
            sum_min = a[i];
            sum_max = a[i];
        }
        else
        {
            if(sum_min > 0)
            {
                sum_min = 0;
            }
            if(sum_max < 0)
            {
                sum_max = 0;
            }
            sum_min += a[i];
            sum_max += a[i];
            manx = max(manx,sum_max);
            minx = min(minx,sum_min);
        }
    }
    printf("%I64d\n",max(manx,sum-minx));
    return 0;
}

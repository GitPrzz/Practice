/*
CodeForces346  C. Number Transformation II

����������a,b
1.ÿ�ζ��ڵ�ǰ��a��ȥ1
2.ÿ�ζ��ڵ�ǰ��a��ȥ a%(ta[i])

�����ٶ��ٴ��ܵõ�b
������̰��,ÿ�μ�ȥ�����ܶ��ֵ������һֱTLE- -.   �������Է���a~a-a%ta[i]������ֵ
�����ȥa%ta[i],�������ͬһ��ֵ��  �����a-a%ta[i] < bʱ,ta[i]����˵�ں����
������û��������.���Ǻ���ta[i]��ȥ.

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

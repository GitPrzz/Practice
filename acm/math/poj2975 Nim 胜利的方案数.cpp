/*
poj2975 Nim ʤ���ķ�����

nim��Ϸ�����Ͳ�Ϊ0��ʱ���Ǳ�ʤ�ġ�
����������Ա��������һ����Ȼ������Ϊ0��Ȼ������ö��٣�����ö��١�
�Ӷ��ﵽ��ʤ�ġ�
1011     ------>      1010
1010     ��һ��       1010

��������ܹ��ж����ֱ�ʤ�ķ�������ʼ�����ͨ��SGֵ�����㣬��������Χ̫��
������Ǵ�nim��ԭ���Ϸ���
������Ǵ�һ�����Ǹ�����һ���֣��Ӷ�ʹʣ�µ����е�����Ϊ0
��ôȡ�� ��һ�ѵ�����    ta[i] > ʣ�������Ե�����
���Կ�������������ж�ʤ���ķ���������

hhh-2016-08-01 20:16:14
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f;
const int maxn = 1000100;

//int vis[22];
//int sg[maxn];
//
//int SG(int cur)
//{
//    memset(vis,0,sizeof(vis));
//    for(int i = 1;i <= cur;i++)
//    {
//        if( (i^cur) < cur)
//        {
//            vis[sg[cur-i]] = true;
//        }
//    }
//    for(int i = 0 ; i <= 20; i++)
//    {
//        if(!vis[i])
//            return i;
//    }
//    return 0;
//}

ll ta[maxn];

int main()
{
    int n ;
    while(scanf("%d",&n) != EOF && n)
    {
        ll ans = 0;
        int tans = 0;
        for(int i = 0;i < n;i++)
        {
            scanf("%I64d",&ta[i]);
            ans ^= ta[i];
        }
        for(int i = 0;i < n;i++)
        {
            if( (ans ^ ta[i]) < ta[i])
                tans ++;
        }
        printf("%d\n",tans);
    }
    return 0;
}

/*
51nod 1682 ��λ������

problem:
����n����,���ÿ�����ڶ��ٸ������������������λ��

solve:
���a[i]������[l,r]����λ��,��ô�����д���a[i]��С��a[i]����һ����. up[r]-up[l] == down[r]-down[l]
--> up[r]-down[r] == up[l]-down[l]. �ͱ���˵�ǰiǰ���ж��ٸ���up-down�������.
���Կ��Դ��м������߼�¼��ͳ��.

hhh-2016/09/03-21:08:16
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
const ll mod = 1000000007;
const int maxn = 8080;
const double PI = acos(-1.0);
int n;
ll num[maxn*2];
int a[maxn];

ll cal(int id)
{
    int upcnt =0 ;
    int docnt = 0;
    memset(num,0,sizeof(num));
    num[8000] = 1;
    for(int i = id-1; i >= 1; i--)
    {
        if(a[i] > a[id]) upcnt++;
        if(a[i] < a[id]) docnt++;
        num[upcnt-docnt+8000] ++;
    }
    ll ans = 0;
    upcnt = docnt = 0;
    for(int i = id; i <= n; i++)
    {
        if(a[i] > a[id]) upcnt++;
        if(a[i] < a[id]) docnt++;
        ans += num[docnt-upcnt+8000];
    }
    return ans;
}

int main()
{
    while(scanfi(n) != EOF)
    {
        for(int i = 1; i<= n; i++)
            scanfi(a[i]);

        for(int i = 1; i<= n; i++)
        {
            printf("%I64d%c",cal(i),i == n ? '\n':' ' );
        }
    }
    return 0;
}

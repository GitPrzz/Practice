/*
Codeforces 651C - Watchmen

����ܶ���a,b  Ȼ��ͨ�����ּ��㷽���жϴ��Ƿ���ͬ
1.  |xi-xj|+|yi-yj|
2. sqrt((xi-xj)*(xi-xj) + (yi-yj)*(yi-yj))

Ȼ����ֻ�е�xi = xj �� yi = yjʱ����ͬ
��ͬʱҪ�ų�(xi,yi)=(xj,yj)�����

hhh-2016-03-07 17:04:24
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 10010;

ll a;
ll b;
map<ll,ll> mp1;
map<ll,ll> mp2;
map< pair<ll,ll>,ll > mp;
int main()
{
    int T,n,m;
    while(scanf("%d",&n) != EOF)
    {
        ll ans = 0;
        ll num = 0;
        mp1.clear();
        mp2.clear();
        mp.clear();
        for(int i = 1; i <= n; i++)
        {
            scanf("%I64d%I64d",&a,&b);

            num += mp[ make_pair(a,b)];
            mp[ make_pair(a,b)] ++;

            if(mp1.find(a) == mp1.end())
                mp1[a] = 1;
            else
            {
                ans += mp1[a];
                mp1[a]++;
            }

            if(mp2.find(b) == mp2.end())
                mp2[b] = 1;
            else
            {
                ans += mp2[b];
                mp2[b]++;
            }
        }
        printf("%I64d\n",(ll)ans-num);
    }
    return 0;
}

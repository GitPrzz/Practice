/*
hdu 5636 搜索 BestCoder Round #74 (div.2)

给你一条链，每两个节点之间的距离是1，然后加上3条边。
m个询问，[l,r]之间的最短路

表示最开始想的是每个询问查找一次最小值，但是思路还是有问题，准确的说只有3
条捷径会对最后的答案造成影响。所以每次我们只需要枚举走过捷径的数目以及进入
的位置，找出最小值即可。


正解：
通过搜索，可以找出走3条捷径的所有情况，然后取出最小值即可

hhh-2016-03-05 21:43:51;
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
#define MID(a,b) (a+((b-a)>>1))
const int maxn=100005;
const int MOD = 1e9+7;

int tx[5],ty[5];
int vis[5],l,r;
ll ans ;

void fin(int now,ll len)
{
    if(len+abs(r-now)<ans) ans = (ll)(len+abs(r-now))%MOD;
    for(int i =1;i <= 3;i++)
    {
        if(!vis[i])
        {
            vis[i] = 1;
            fin(tx[i],abs(len+abs(ty[i]-now))+1);
            fin(ty[i],abs(len+abs(tx[i]-now))+1);
            vis[i] = 0;
        }
    }
}

int main()
{
    int t,n,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        for(int i =1;i <= 3;i++)
        {
            scanf("%d%d",&tx[i],&ty[i]);
        }
        ll sum = 0;
        for(int i =1;i <= q;i++)
        {
            scanf("%d%d",&l,&r);
            ans = abs(l-r);
            fin(l,0);
            sum=(ll)(sum+(ll)(ans*i)%MOD)%MOD;
//            cout << ans <<endl;
        }
        printf("%I64d\n",sum%MOD);
    }
    return 0;
}

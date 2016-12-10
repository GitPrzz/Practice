/*
hdu 5738 Eureka

problem:
求有多少个队列,满足 f(u,v) >= g(u,v,m)

solve:
f(u,v) >= g(u,v,m)  ---->  f(u,v) >= f(u,w) + f(w,v);   f()即求两点间的距离
所以就成了找出有多少点共线. 然后计算对best sets贡献即可.

hhh-2016-08-26 19:08:41
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
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 1004;

ll gcd(ll a,ll b)
{
    if(!a)
        return b;
    if(!b)
        return a;
    while(a % b != 0)
    {
        ll t = a% b;
        a = b;
        b = t;
    }
    return b;
}

struct node
{
    ll x,y;
} pnode[maxn];

bool cmp(node a,node b)
{
    if(a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

map<pair<ll,ll>,int> mp;
ll pow_mod(ll a,ll n)
{
    ll cnt = 1;
    if(n < 0)
        return 0;
    while(n)
    {
        if(n & 1) cnt = cnt*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return cnt;
}
int main()
{
//    freopen("in.txt","r",stdin);
    int T,n;
    ll v,u;
    scanfi(T);
    while(T--)
    {
        scanfi(n);
        for(int i = 0; i < n; i++)
        {
            scanfl(u),scanfl(v);
            pnode[i].x = u,pnode[i].y = v;
        }
        ll ans = 0;
        sort(pnode,pnode+n,cmp);
        for(int i =0; i < n; i++)
        {
            ll cnt = 0;
            mp.clear();
            for(int j = i+1; j < n; j++)
            {
                if(pnode[i].x == pnode[j].x && pnode[i].y == pnode[j].y)
                    cnt++;
                else
                {
                    ll tx = pnode[i].x - pnode[j].x;
                    ll ty = pnode[i].y - pnode[j].y;
                    ll t = gcd(tx,ty);
                    if(t)
                        mp[make_pair(tx/t,ty/t)]++;
                    else
                        mp[make_pair(tx,ty)]++;
                }
            }
            if(cnt )
            {
                ans = (ans+pow_mod(2,cnt)-1)%mod;
            }
            for(map<pair<ll,ll>,int>::iterator it = mp.begin();it != mp.end();it++)
            {
                ll num = (ll)(it->second);
                ans = (ans+pow_mod(2,cnt)*(pow_mod(2,num)-1)%mod)%mod;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

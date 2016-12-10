/*
hihocoder 1391 树状数组

problem:
A,B两个敌对国分别有1W个导弹，每个导弹有各自的发射时间、飞行时间、造成伤害。两国各有一个防御系统，
且分别有各自的持续时间（相当于防御一个时间区间？），开启防御系统时，所有到达该国的导弹按原速度反向。
已知B国在X时间点开启防御系统，问A国最少会受多少的伤害。（以上数值伤害1e4，其余1e8）

solve:
昨天比赛心态爆炸.......Orz
因为导弹可以在两个国家之间互相弹来弹去. 我们可以计算出这个导弹最早攻击到A的时间l和最晚到达A的时间r(假设A防御时间无限)
如果开启防御后无法覆盖[l,r]那么这个导弹总会攻击到A.
然后问题就成了已知很多个区间的价值,完全覆盖是能够得到价值.求长度为len的区间最多能得到多少价值.
所以可以通过树状数组来解决了.
如果从小到大枚举r,找出以当前点为右端点能覆盖多少的值.
那么每次就要将区间的值赋予l,因为只有左端点小于等于l时才覆盖这个区间.

//比赛时少了个判断, 而且求k值错了...卒

hhh-2016-09-25 15:22:55
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <math.h>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
#define mod 1004535809LL

const int maxn = 5e5;
int n,m,k;
ll ta,tb,x;
ll u,v,w,y,tot;

map<ll,ll> mp;
ll sum;
ll mis[100010];
struct node
{
    ll l,r;
    ll w;
} pnode[maxn * 10];

bool cmp(node a,node b)
{
    return a.r< b.r;
}

ll s[maxn*5];
int lowbit(int x)
{
    return x&(-x);
}

void add(int pos,ll val)
{
    if(pos <= 0)
        return ;
    while(pos <= tot)
    {
        s[pos] += val;
        pos += lowbit(pos);
    }
}

ll cal(int pos)
{
    ll cnt = 0;
    if(pos <= 0)
        return 0;
    while(pos > 0)
    {
        cnt += s[pos];
        pos -= lowbit(pos);
    }
    return cnt;
}

int cnt ;
int main()
{
    while(scanf("%lld %lld",&ta,&tb)!=EOF)
    {
        mp.clear();
        sum=0;
        tot=1;
        cnt=1;
        scanf("%lld",&x);
        y=x+tb;
        memset(s,0,sizeof(s));
        scanf("%d %d",&n,&m);
        for(int i=0; i<n; i++)
        {
            scanf("%lld %lld %lld",&u,&v,&w);
            if(u+v>y||u+v<x) continue;
            sum+=w;

            k = (y - u) / v;
            if(k % 2LL == 0LL)
                k-=3LL;
            while(k*v + u <= y) k +=2LL;

            //k=3;
            //while(u+k*v<=y) k+=2;
            pnode[cnt].l = u+2LL*v;
            pnode[cnt].r = u+(k-1LL)*v;
//            cout << pnode[cnt].l << " " <<pnode[cnt].r <<endl;
            mis[tot ++] = u+2LL*v, mis[tot++] = u+(k-1LL)*v;
            pnode[cnt++].w= w;
        }
        for(int i=0; i<m; i++)
        {
            scanf("%lld %lld %lld",&u,&v,&w);
            sum+=w;

            k = (y - u) / v;
            if(k % 2LL == 1LL)
                k-=3LL;
            while(u+k*v<=y) k +=2LL;

            pnode[cnt].l = u+v;
//            if(u + 2*v > y || u+ 2*v < x)
//                pnode[cnt].r = pnode[cnt].l;
//            else{
            pnode[cnt].r =u+(k-1LL)*v;
            mis[tot++] = u+(k-1LL)*v;
//            }
            mis[tot ++] = u+v;
            pnode[cnt++].w= w;
        }

        sort(mis+1,mis+tot);
        int t = unique(mis+1,mis+tot) - mis;
        sort(pnode+1,pnode + cnt,cmp);
        for(int i= 1; i < t; i++)
        {
            mp[mis[i]] = i;
        }

        int cur = 1;
        ll Max = 0;

        for(int i = 1; i < t; i++)
        {
            ll ed = mis[i];
            ll from = ed - ta;

            while(mp[pnode[cur].r] == i && cur < cnt)
            {
                add(mp[pnode[cur].l],pnode[cur].w);
                cur ++;
            }
            int pos = lower_bound(mis+1,mis+t,from) - mis;
            Max =max(Max,cal(i) - cal(pos-1));
        }
//        cout <<Max <<endl;
        printf("%lld\n",sum - Max);
    }
    return 0;
}

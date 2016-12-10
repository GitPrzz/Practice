/*
hihocoder 1391 ��״����

problem:
A,B�����жԹ��ֱ���1W��������ÿ�������и��Եķ���ʱ�䡢����ʱ�䡢����˺�����������һ������ϵͳ��
�ҷֱ��и��Եĳ���ʱ�䣨�൱�ڷ���һ��ʱ�����䣿������������ϵͳʱ�����е���ù��ĵ�����ԭ�ٶȷ���
��֪B����Xʱ��㿪������ϵͳ����A�����ٻ��ܶ��ٵ��˺�����������ֵ�˺�1e4������1e8��

solve:
���������̬��ը.......Orz
��Ϊ������������������֮�以�൯����ȥ. ���ǿ��Լ��������������繥����A��ʱ��l��������A��ʱ��r(����A����ʱ������)
��������������޷�����[l,r]��ô��������ܻṥ����A.
Ȼ������ͳ�����֪�ܶ������ļ�ֵ,��ȫ�������ܹ��õ���ֵ.�󳤶�Ϊlen����������ܵõ����ټ�ֵ.
���Կ���ͨ����״�����������.
�����С����ö��r,�ҳ��Ե�ǰ��Ϊ�Ҷ˵��ܸ��Ƕ��ٵ�ֵ.
��ôÿ�ξ�Ҫ�������ֵ����l,��Ϊֻ����˵�С�ڵ���lʱ�Ÿ����������.

//����ʱ���˸��ж�, ������kֵ����...��

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

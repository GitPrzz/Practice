/*
hdu 5636 ���� BestCoder Round #74 (div.2)

����һ������ÿ�����ڵ�֮��ľ�����1��Ȼ�����3���ߡ�
m��ѯ�ʣ�[l,r]֮������·

��ʾ�ʼ�����ÿ��ѯ�ʲ���һ����Сֵ������˼·���������⣬׼ȷ��˵ֻ��3
���ݾ�������Ĵ����Ӱ�졣����ÿ������ֻ��Ҫö���߹��ݾ�����Ŀ�Լ�����
��λ�ã��ҳ���Сֵ���ɡ�


���⣺
ͨ�������������ҳ���3���ݾ������������Ȼ��ȡ����Сֵ����

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

/*
hdu 5491 ������
��lת���ɽ��ƣ�����һ��������1����Ŀ��[a,b]֮���
���ҳ�С��b�� �������aֱ���������֪��1�������
��Ҫ��ϸ�ڷ����������
�ʼд���� ans += tans[i]*tt������tans��int���Գ˳������������= =
hhh-2016-02-19 21:58:16
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn = 100;
int tans[maxn],tot;
ll get_num(ll x)
{
    ll t = x;
    tot = 0;
    ll ans = 0;
    while(t)
    {
        tans[tot] = t % 2;
        if(t%2)
            ans ++;
        t /= 2;
        tot ++;
//        if(t == 0)
//            break;
    }
    return ans;
}

void prin()
{
    for(int i = 0; i < tot; i++)
        printf("%d",tans[i]);
    printf("\n");
}

int main()
{
    int T,cas,l,a,b;
    cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        memset(tans,0,sizeof(tans));
        scanf("%d%d%d",&l,&a,&b);
        printf("Case #%d: ",cas++);

        ll x = l+1,t;
        while(1)
        {
            t = get_num(x);
            //pri();
            if(t <= b)
                break;
            x++;
        }
        if(t < a)
        {
            int ned = a - t;
            for(int i = 0;i < maxn; i++)
            {
                if(tans[i] == 0)
                {
                    tans[i] = 1;
                    ned--;
                }
                if(!ned)
                    break;

            }
        }
        ll ans = 0;
        ll tt = 1;
        for(int i = 0; i < maxn; i++)
        {
            if(tans[i])
                ans += tt;
            tt <<= 1;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

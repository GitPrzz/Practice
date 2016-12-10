/*
51 nod 1060 最复杂的数
反素数问题
hhh  2016/5/31 20:37
*/
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
int limit = 70;
ll ansNum;
ll ans;
ll n;
ll p[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

void dfs(int dept,ll now,ll num,int pre)
{
    if(now > n)
        return;
    if(dept >= 16) return;
    if(num > ansNum)
    {
        ansNum = num;
        ans = now;
    }
    if(num == ansNum && now < ans)
        ans = now;
    for(int i=1; i<=pre; i++)
    {
        if(now >= n/p[dept])
            break;
        dfs(dept+1,now *= p[dept],num*(i+1),i);
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ans = ansNum = 0;
        scanf("%I64d",&n);
        dfs(0,1,1,64);
        printf("%I64d %I64d\n",ans,ansNum);
    }
    return 0;
}

/*
5
1
10
100
1000
10000

*/

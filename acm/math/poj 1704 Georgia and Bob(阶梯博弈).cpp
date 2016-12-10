/*
poj 1704 Georgia and Bob(阶梯博弈)

一行棋盘，每次可以将一个棋子往左边移动，但是不能跨越棋子
每次移动时，和左边的间距变小了，与右边的间距变大
可以等效于阶梯博弈，每次将一个台阶上的棋子往下移动。 本台阶石子变少，下一个台阶的石子边多
转化一下就好了

hhh-2016-08-02 21:26:32
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
typedef long long ll;
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
const int maxn = 10000+10;

int sg[maxn];
int s[maxn];
int n;

void SG(int now)
{
    if(sg[now] != -1)
        return ;
    int vis[maxn];
    memset(vis,0,sizeof(vis));
    for(int i = 0; i < n; i++)
    {
        int t = now-s[i];
        if(t < 0)
            continue;
        SG(t);
        vis[sg[t]] = 1;
    }

    for(int i = 0;; i++)
    {
        if(!vis[i])
        {
            sg[now] = i;
            break;
        }
    }
}

int main()
{
    int x,m;
    int a[maxn];
//    freopen("in.txt","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n) ;
        for(int i = 0; i < n; i++)
        {
            scanf("%d",&a[i]);
        }
        sort(a,a+n);
        int ans;
        if(n % 2 == 0)
        ans = 0;
        else
            ans = a[0]-1;
        for(int i = n-1; i > 0; i -= 2)
        {
            ans ^= (a[i] - a[i-1] -1);
        }
        if(ans)
            printf("Georgia will win\n");
        else
            printf("Bob will win\n");
    }
    return 0;
}



/*
hdu 5724 SG+状态压缩

感觉上是博弈，而且很久以前就看了看SG，但是并没怎么系统地去学习zzz。
首先可以把棋盘n行看成n个石碓，用1表示有棋子，0表示没有的话，能够用二进制表示出所有的状态：
1000100这个可以转换成 0100100 1000010等等

然后就能利用公式求出每种情况的SG(枚举 1~(1<<20))
得出每一行的状态计算即可

hhh-2016-08-01 17:28:17
学习：
//http://blog.csdn.net/luomingjun12315/article/details/45555495
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f;
const int maxn = 1000100;

int vis[22];
int sg[1<<20];

int SG(int cur)
{
    memset(vis,0,sizeof(vis));
    for(int i = 20; i >= 0; i--)
    {
        if(cur & (1<<i))
        {
            for(int j = i-1; j >= 0; j--)
            {
                if(!(cur & (1 << j)))
                {
                    int tmp = cur;
                    tmp ^= ((1<<i)^(1<<j));
                    vis[sg[tmp]] = true;
                    break;
                }
            }
        }
    }
    for(int i = 0 ; i <= 20; i++)
    {
        if(!vis[i])
            return i;
    }
    return 0;
}

int main()
{
    memset(sg,0,sizeof(sg));
    for(int i = 1; i < (1 << 20); i++)
        sg[i] = SG(i);
    int T,n,x;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int ans = 0;
        for(int i = 1;i <= n;i++)
        {
            int m,cur = 0;
            scanf("%d",&m);
            for(int j = 1;j <= m;j++)
            {
                scanf("%d",&x);
                cur |= 1 << (20-x);
            }
            ans ^= sg[cur];
        }
        if(ans )
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*
hdu 5637 搜索预处理

给你n个数，然后对于x有两种操作：
1.改变x二进制中的一位，即1->0 or 0->1
2.将x与n个数中的t异或得到 x^t
求最后得到y的最小操作数

最开始想到求出x^y，但是不知道怎么处理。如果每个询问都进行一次搜索的话感觉
会TLE,为什么就没想到预处理出来- -！

正解：
先把上面两种操作得到所有情况求出来，然后从x->y也就是异或上(x^y)，而这个值
的最小步数已经处理出来，直接进行O(1)的查询即可

hhh-2016-03-06 12:12:08
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
const int maxn=100500;
const int MOD = 1e9+7;

int a[maxn];
int step[maxn<<2];
int tp[maxn<<2];
int y,n;
int ans ;

void bfs()
{
    memset(step,-1,sizeof(step));
    int star = 0,tail = 0;
    tp[0] = 0,step[0] = 0;
    while(star <= tail)
    {
        int cur = tp[star];
        for(int i =1; i <= n;i++)
        {
            int t = cur^a[i];
            if(step[t] != -1)
                continue;
            tp[++tail] = t;
            step[t] = step[cur]+1;
        }
        for(int i =0;i <= 17;i++)
        {
            int t = cur^(1<<i);
            if(step[t] != -1)
                continue;
            tp[++tail] = t;
            step[t] = step[cur]+1;
        }
        star++;
    }
    return ;
}


int main()
{
    int t,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        bfs();
        int x,y;
        ll sum = 0;
        for(int i = 1;i <= q;i++)
        {
            scanf("%d%d",&x,&y);
            int ans = step[x^y];
            sum = (sum+(ll)(i*ans)%MOD)%MOD;
        }
        printf("%I64d\n",sum%MOD);

    }
    return 0;
}

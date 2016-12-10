/*
51 nod 1406 与查询

problem:
有n个整数。输出他之中和x相与之后结果为x的有多少个。x从0到1000000

solve:
如果x与a[i]相与之后为x,那么x必定是a[i]二进制中1的组合.
所以就成了快速求x中1的所有组合.

最开始是枚举x,然后从高位到低位枚举. cnt[i - (1 << j)] += cnt[i];
但是有的时候会出现重复,比如: 1011.
循环置换一下就好了

hhh-2016/09/09-16:19:21
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1000000007;
const int maxn = 1001000;
const double PI = acos(-1.0);
const int limit = 33;


template<class T> void read(T&num)
{
    char CH;
    bool F=false;
    for(CH=getchar(); CH<'0'||CH>'9'; F= CH=='-',CH=getchar());
    for(num=0; CH>='0'&&CH<='9'; num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p)
{
    if(!p)
    {
        puts("0");
        return;
    }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}

int cnt[maxn];

int main()
{
    int n,Max,x;
    clr(cnt,0);
    read(n);
    Max = 0;
    for(int i = 1; i <=n; i++)
    {
        read(x),Max = max(x,Max);
        cnt[x] ++ ;
    }
    int begi = min(1000001,Max);
//    cnt[0] = n;
    for(int j = 20; j >= 0 ; j --)
    {
        for(int i = 1; i <= begi; i++)
        {
            if(i & (1 << j))
            {
                cnt[i - (1 << j)] += cnt[i];
            }
        }
    }
    cnt[0] = n;
    for(int i = 0;i <= 1000000;i ++)
        print(cnt[i]);
//    for(int i = 0; i <= 10; i ++)
//        print(cnt[i]);
    return 0;
}

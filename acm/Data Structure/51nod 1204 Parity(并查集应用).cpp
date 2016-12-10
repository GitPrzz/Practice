/*
51nod 1204 Parity(并查集应用)

problem:
你可以从中选择一个连续的01子串,然后是q个询问和回答. 表示区间[l,r]中有奇数或者偶数个1. 求第一个出现矛盾的位置

solve:
考虑了下线段树什么的,发现并不怎么靠谱.    没做过类似的,完全没想到并查集,卒.....
如果[l,r]是even,那么[1,l-1]和[1,r]中1的个数都是偶数 or 奇数.
如果[l,r]是odd,那么 [1,l-1] 和 [1,r]的奇偶性不同.

所以用[1,n]表示'相同'关系,[n+1,2*n]虚拟表示'不同'关系.建立两个集合
判断 (l-1+n,r) && (l-1,b+n) 就能确定 l-1和r是否为'相同'关系.  其它同理

hhh-2016/09/06-20:47:14
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
const int maxn = 300050;
const double PI = acos(-1.0);
const int limit = 33;
int pre[maxn];
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

int fin(int x)
{
    if(pre[x ]== x) return x;
    return pre[x] = fin(pre[x]);
}

void unio(int a,int b)
{
    int ta= fin(a);
    int tb = fin(b);
    pre[ta] = tb;
}
char op[10];

int main()
{
//    freopen("in.txt","r",stdin);
    int n,q,flag = 0;
    int a,b;
    read(n);
    read(q);
    for(int i = 0;i <= 2*n;i++)
        pre[i] = i;
    for(int i = 1; i <= q; i++)
    {
        scanf("%d%d%s",&a,&b,op);
        if(flag)
            continue;
        if(op[0] == 'e')
        {
            if(fin(a-1+n) == fin(b) && fin(a-1) == fin(b + n))
            {
                flag = i;
            }
            unio(a-1,b);
            unio(a-1+n,b+n);
        }
        else
        {
            if(fin(a-1) == fin(b) && fin(a-1+n) == fin(b+n))
            {
                flag = i;
            }
            unio(a-1+n,b);
            unio(a-1,b+n);
        }
    }
    if(flag)
        printf("%d\n",flag);
    else
        printf("-1\n");
    return 0;
}

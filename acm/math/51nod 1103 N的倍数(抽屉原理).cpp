/*
51nod 1103 N的倍数(抽屉原理)

problem:
给你n个数,求是否存在几个数和为n

solve:
因为和的是n的倍数,所以对n取模后为0.
先求出所有的前缀和对n取模, 如果为0直接就能得出答案.
取模后[1,n-1]是无解的,但是前缀和总共有n个,所以必定有两个值相等,相减后为0

hhh - 2016/10/01 16:31:04
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <math.h>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 3e6 + 1000;
const int inf = 0x3f3f3f3f;
const ll mod = 1000000007;
const double eps = 1e-7;
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
ll a[maxn];
ll n;
int vis[maxn];
ll x[maxn];
int main()
{
   read(n);
   memset(vis,0,sizeof(vis));
   a[0] = 0;
   int l,r;
   int flag = 0;
   for(int i = 1;i <= n;i++)
   {
       read(x[i]);
       a[i] = (a[i-1] + x[i]) % n;
       if(flag)
        continue;
       if(vis[a[i]] != 0)
       {
           flag = 1;
           l = vis[a[i]] + 1,r = i;
       }
       vis[a[i]] = i;
       if(a[i] == 0)
       {
           flag = 1;
           l = 1,r = i;
       }
   }
   print(r - l + 1);
//   cout << l <<" " << r <<endl;
   for(int i = l;i <= r;i++)
   {
       print(x[i]);
   }
}

/*
51 nod 1421 最大MOD值

problem:
从数组中选择两个数使 a[i]%a[j]最大

solve:
可以发现a[i]越接近a[j]的倍数则越大. 所以枚举a[j]的倍数然后二分查找.
最开始以为这个会T....
M+M/2+...M=O(MlgM)

hhh-2016/09/16-16:33:10
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
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
const ll mod = 1e9+7;
const int maxn = 200010;
const double PI = acos(-1.0);

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
int a[maxn];
int main()
{
    int n;
    read(n);
    for(int i =0; i < n; i++)
    {
        read(a[i]);
    }
    sort(a,a+n);
//    int cnt = unique(a,a+n)-a;
    int ans = 0;
    for(int i =0; i < n; i++)
    {
        if(a[i] == 1)
            continue;
        for(int j = 1;j <= a[n-1]/a[i] + 1; j++)
        {
            int pos = lower_bound(a+i,a+n,j * a[i]) - a;
            pos -- ;
            if(pos > 0 && pos <= n && a[pos] > a[i])
                ans = max(ans, a[pos] % a[i]);
            if(ans == a[i]-1)
                break;
//            cout << j <<" " << pos <<" " <<ans << endl;
        }
    }
    print(ans);
    return 0;
}

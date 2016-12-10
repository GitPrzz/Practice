/*
51 nod 1055 ��Ȳ�����(dp)

problem:
N����ͬ�����������ҳ�����Щ����ɵ���ĵȲ�����

solve:
��dp[i][j]��ʾ���һλ��i,�����ڶ�λ��j�ĵȲ�����.Ȼ��ͨ�����ֵ���ܵõ�������һ��״̬
������ȥ���ܵó����.
�ʼTL,�о���map������. ���С�����Ҽ��˸��жϾͼ����� - -

hhh-2016/09/16-20:34:58
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
const int maxn = 10010;
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
short dp[maxn][maxn];
int a[maxn];
map<int,int> mp;
int main()
{
    int n;
    read(n);
    mp.clear();
    for(int i =1; i <= n; i++)
        read(a[i]);
    sort(a+1,a+n+1);
    for(int i = 1;i <= n;i++)
        mp[a[i]] = i;

    dp[1][1] = 1;
    short ans = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = i-1; j >= 1; j--)
        {
            int t = a[i] - a[j];
            if(t*ans>a[n]-a[1])break;
            int to = a[j]- t;
            if(to < 0 || mp[to] < 1 || mp[to] >= j)
                dp[i][j] = 2;
            else
                dp[i][j] = dp[j][mp[to]] + 1;
            ans = max(ans,dp[i][j]);
        }
    }
    print(ans);
    return 0;
}

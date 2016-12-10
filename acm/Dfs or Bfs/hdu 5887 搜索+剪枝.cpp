/*
hdu 5887 搜索+剪枝

problem:
01背包问题,只是里面的数据达到了1e9

solve:
先对所有的物品按贡献(w/v)进行排序, 当搜到第u个点时,第u+1个在剩下的贡献是最大的. 如果剩下的全部放
u+1物品都无法大于当前的答案,则剪去.

hhh-2016-09-20 20:25:42
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 200100;
const int inf = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

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

struct node
{
    ll v,w;
} p[maxn];

bool cmp(node a,node b)
{
    return 1.0*a.w/a.v > 1.0*b.w/b.v;
}

ll ans = 0,lm;
int n;

bool can_more(int u,ll val,ll &ans,ll limit)
{
    ll t = limit/p[u+1].v + 1;
    if(val + p[u+1].w * t >= ans)
        return true;
    return false;
}

void dfs(int u,ll val,ll limit)
{
    if(val > ans)
        ans = val;
    if(limit <= 0)
        return ;
    if(u < n && can_more(u,val,ans,limit))
    {
        for(int i = u+1; i <= n; i++)
        {
            if(limit >= p[i].v)
                dfs(i,val + p[i].w,limit - p[i].v);
        }
    }
}

void init()
{

}

int main()
{
    init();
    while(scanf("%d%I64d",&n,&lm) != EOF)
    {
        for(int i =1; i <= n; i++)
        {
            read(p[i].v);
            read(p[i].w);
        }
        sort(p+1,p+n+1,cmp);
        ans =0 ;
        dfs(0,0,lm);
        print(ans);
    }
}

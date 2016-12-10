/*
SPOJ DQUERY(hdu3333)线段树or树状数组离线
查询区间内不同数的个数
本来是学习主席树的，发现这方法不会也就写了下，感觉很机智
先将所有查询按区间右端从小到大排序，如果一个数已经出现过就先把以前位置上的删
掉然后在新的位置上插入，像这样在[l,r]中重复的就只计算了一次
hhh-2016-02-18 14:47:11
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ld;
int tot;
map<int , int >mp;
const int maxn = 100010;
int n;
int a[maxn],ans[maxn*2];
int s[maxn];

struct node
{
    int l,r,id;
} qu[maxn*2];

bool cmp(node a,node b)
{
    return a.r < b.r;
}

int lowbit(int x)
{
    return x&(-x);
}


void add(int x,int val)
{
    for(int i = x ; i <= n; i+=lowbit(i))
        s[i] += val;
}

int query(int x)
{
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        sum += s[i];
    return sum;
}

int main()
{
    while(scanf("%d",&n) != EOF)
    {
        mp.clear();
        memset(s,0,sizeof(s));
        for(int i =1 ; i <= n; i++)
            scanf("%d",&a[i]);

        int q;
        scanf("%d",&q);
        for(int i = 1; i <= q; i++)
        {
            scanf("%d%d",&qu[i].l,&qu[i].r);
            qu[i].id = i;
        }
        sort(qu+1,qu+q+1,cmp);
        int t = 1;
        for(int i= 1;i <= q;i++)
        {
            for(;t <= qu[i].r;t++)
            {
                if(mp[a[t]] != 0) add(mp[a[t]],-1);
                mp[a[t]] = t;
                add(t,1);
            }
            ans[qu[i].id] = query(qu[i].r) - query(qu[i].l-1);
        }
        for(int i = 1;i <= q;i++)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}

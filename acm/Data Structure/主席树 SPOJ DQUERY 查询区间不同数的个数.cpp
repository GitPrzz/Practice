/*
主席树 SPOJ DQUERY
查询区间有多少个不同的数。类似于之前树状数组离线的思路，在插入之前先进行判断
如果已经有了，把以前的先删掉再进行插入
hhh-2016-02-18 15:37:48
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;
const int maxn = 100010;
int tot;
int n;
int a[maxn],t[maxn];
int T[maxn],lson[maxn*30],rson[maxn*30],c[maxn*30];

int build(int l,int r)
{
    int root = tot++;
    c[root] = 0;
    if(l != r)
    {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}


//如果那里发生改变则兴建一个节点而非像平常修改那个节点的值
int update(int root,int pos,int val)
{
    int newroot = tot++;
    int tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1,r = n;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        }
        else
        {
            lson[newroot] = lson[root];
            rson[newroot] = tot++;
            newroot = rson[newroot];
            root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int root,int pos)
{
    int l = 1, r = n;
    int ans = 0;
    while(pos > l)
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            ans += c[rson[root]];
            r = mid;
            root = lson[root];
        }
        else
        {
            l = mid+1;
            root = rson[root];
        }
    }
    return ans+c[root];
}

int main()
{
    while(scanf("%d",&n) !=EOF)
    {
        tot = 0;
        map<int,int> mp;
        for(int i = 1; i <= n; i++)
            scanf("%d",&a[i]);
        T[0] = build(1,n);
        for(int i =1; i <= n; i++)
        {
            if(mp.find(a[i]) == mp.end())
                T[i] = update(T[i-1],i,1);
            else
            {
                int tt = update(T[i-1],mp[a[i]],-1);
                T[i] = update(tt,i,1);
            }
            mp[a[i]] = i;
        }

        int q;
        scanf("%d",&q);

        while(q--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",query(T[r],l));
        }
    }
    return 0;
}

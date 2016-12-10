/*
hdu 5919 主席树(区间不同数的个数 + 区间第k大)

problem:
给你n个数字,和m个查询.
将[l,r]之间数第一次出现的位置信息弄成一个新的数组,然后找出其中k/2大的数.(k为位置的数量)

solve:
通过主席树能够找出[l,r]之间有多少个不同的数,然后利用再用一个查询找出第k大的即可.
(都是类似与线段树的操作, T[i]存的是[1,n]的信息, 尽管说的只是[i,n] ,只是[1,i-1]的还没更新而已.  所以查询的时候出了点问题)

hhh-2016-10-07 16:48:19
*/
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
//#define lson  i<<1
//#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))

using namespace std;

const int maxn = 200100;
const int N = maxn * 100;


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

int lson[N],rson[N],c[N];
int a[maxn],T[maxn];
int tot,n,m;

int build(int l,int r)
{
    int root = tot++;
    c[root ] = 0;
    if(l != r)
    {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}

int update(int root,int pos,int val)
{
    int newroot = tot ++ ,tmp= newroot;
    c[newroot] = c[root] + val;
    int l = 1,r = n;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(pos <= mid)
        {
            lson[newroot] = tot++;
            rson[newroot] = rson[root];
            newroot = lson[newroot] ;
            root = lson[root];
            r = mid;
        }
        else
        {
            lson[newroot] = lson[root],rson[newroot] = tot++;
            newroot = rson[newroot],root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}


int query(int root,int pos)
{
    int cnt = 0;
    int l = 1,r = n;
    while(pos < r)
    {
        int mid = (l + r) >> 1;
        if(pos <= mid)
        {
            root = lson[root];
            r = mid;
        }
        else
        {
            cnt += c[lson[root]];
            root = rson[root];
            l = mid + 1;
        }
    }
    return cnt + c[root];
}


int Find(int root,int k)
{
    int l = 1,r = n;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(l == r)
            return l;
        if(c[lson[root]] >= k)
        {
            root = lson[root];
            r = mid;
        }
        else
        {
            k -= c[lson[root]];
            root = rson[root];
            l = mid +1 ;
        }
    }
}

int main()
{
    int t,cas = 1;
//    freopen("in.txt","r",stdin);
    read(t);
    while(t--)
    {
        tot = 0;
        read(n),read(m);
        for(int i = 1; i <= n; i++)
            scanf("%d",&a[i]);
        T[n + 1] = build(1,n);
        map<int,int> mp;
        for(int i = n; i >= 1; i--)
        {
            if(mp.find(a[i]) == mp.end())
            {
                T[i] = update(T[i + 1],i,1);
            }
            else
            {
                int tp = update(T[i+1],mp[a[i]],-1);
                T[i] = update(tp,i,1);
            }
            mp[a[i]] = i;
        }
        int ans = 0;
        int l,r;
        printf("Case #%d:",cas++);
        for(int i = 1; i <= m; i++)
        {
            read(l),read(r);
//            cout << l <<" " <<r << endl;
            l = (l + ans) % n + 1;
            r = (r + ans)%n + 1;
            if(l > r)
                swap(l,r);
            int num = (query(T[l],r)+1) >> 1;
//            if(!num) num = 1;
            ans = Find(T[l],num);
            printf(" %d",ans);
        }
        printf("\n");
    }
    return 0;
}

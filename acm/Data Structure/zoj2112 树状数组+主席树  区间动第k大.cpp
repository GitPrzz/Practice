/*
study
zoj2112 树状数组+主席树  区间动第k大
开始想了一下，如果只用主席树在修改的时候差不多要修改所有的树
然后看了下树状数组套主席树，
相当于我们先照静态第k大建好树，然后把修改操作通过树状数组另外建一个树
于是在查询的时候只要通过树状数组得出增减情况再加上最初的
hhh-2016-02-19 15:03:33
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

const int maxn = 60010;
int n,m;
int a[maxn],t[maxn];
int T[maxn],val[maxn*40],lson[maxn*40],rson[maxn*40];
int tot;

void ini_hash(int num) //排序去重
{
    sort(t,t+num);
    m = unique(t,t+num)-t;
}

int Hash(int x) //获得x在排序去重后的位置
{
    return lower_bound(t,t+m,x) - t;
}

int build(int l,int r)
{
    int root = tot++;
    val[root] = 0;
    if(l != r)
    {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}


//如果那里发生改变则兴建一个节点而非像平常修改那个节点的值
int update(int root,int pos,int va)
{
    int newroot = tot++;
    int tmp = newroot;
    val[newroot] = val[root] + va;
    int l = 0,r = m-1;
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
        val[newroot] = val[root] + va;
    }
    return tmp;
}


int s[maxn];
int cur[maxn];

int lowbit(int x)
{
    return x&(-x);
}

//void add(int x,int pos,int va)
//{
//    while(x < n)
//    {
//        s[x] = update(s[x],pos,va);
//        x += lowbit(x);
//    }
//}

int sum(int x)
{
    int cn = 0;
    while(x>0)
    {
        cn += val[lson[cur[x]]];
        x -= lowbit(x);
    }
    return cn;
}

int query(int lt,int rt,int k)
{

    int l = 0, r = m-1;
    int lroot = T[lt-1];
    int rroot = T[rt];
    for(int i = lt-1; i; i-=lowbit(i)) cur[i] = s[i];
    for(int i = rt; i; i-=lowbit(i)) cur[i] = s[i];
    while(l < r)
    {
        int mid = (l+r)>>1;
        int tmp = sum(rt)-sum(lt-1)+val[lson[rroot]]-val[lson[lroot]];
        if(tmp >= k)
        {
            for(int i = lt-1; i; i-=lowbit(i)) cur[i] = lson[cur[i]];
            for(int i = rt; i; i-=lowbit(i)) cur[i] = lson[cur[i]];
            lroot = lson[lroot];
            rroot = lson[rroot];
            r = mid;
        }
        else
        {
            k -= tmp;
            for(int i = lt-1; i; i-=lowbit(i)) cur[i] = rson[cur[i]];
            for(int i = rt; i; i-=lowbit(i)) cur[i] = rson[cur[i]];
            lroot = rson[lroot];
            rroot = rson[rroot];
            l = mid+1;
        }
    }
    return l;
}

void change(int root,int pos,int va)
{
    while(root <= n)
    {
        s[root] = update(s[root],pos,va);
        root += lowbit(root);
    }
}

struct node
{
    int l,r,kind,k;
} qry[10010];

int main()
{
    int q,cas;
    scanf("%d",&cas);
    while(cas--)
    {
        m = 0;
        tot = 0;
        scanf("%d%d",&n,&q) ;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            t[m++] = a[i];
        }

        char ask[10];
        int l,r,k;
        for(int i = 1; i <= q; i++)
        {
            scanf("%s",ask);

            if(ask[0] == 'Q')
            {
                scanf("%d%d%d",&l,&r,&k);
                qry[i].l = l;
                qry[i].r = r;
                qry[i].k = k;
                qry[i].kind = 0;
            }
            else
            {
                scanf("%d%d",&l,&r);//将l位置的数改为r
                qry[i].l = l;
                qry[i].r = r;
                qry[i].kind = 1;
                t[m++] = qry[i].r;
            }
        }

        ini_hash(m);
        T[0] = build(0,m-1);
        for(int i = 1; i <= n; i++)
            T[i] = update(T[i-1],Hash(a[i]),1);

        for(int i =1; i <= n; i++)
        {
            s[i] = T[0];
        }
        for(int i =1; i <= q; i++)
        {
            if(qry[i].kind == 0)
            {
                printf("%d\n",t[query(qry[i].l,qry[i].r,qry[i].k)]);
            }
            else
            {
                change(qry[i].l,Hash(a[qry[i].l]),-1);
                change(qry[i].l,Hash(qry[i].r),1);
                a[qry[i].l] = qry[i].r;
            }
        }
    }
    return 0;
}

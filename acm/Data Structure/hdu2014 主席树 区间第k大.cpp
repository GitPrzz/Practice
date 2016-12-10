/*
hdu-2104
��ϯ��
��T�б������ǰi�������߶����������ƽ�������������׳���MLE������i�͵�i+1��
�����ԣ������߶�����һ��������ͬ�ġ����Ƕ�����ͬ�Ĳ�����������ָ��ָ��ȥ��
��ͬ�ĵط������½���
���Ҫ�������[l,r] --> T[r]-T[l-1]��
hhh-2016-02-18 13:09:24
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;
const int maxn = 100010;
int tot;
int n,m;
int a[maxn],t[maxn];
int T[maxn],lson[maxn*30],rson[maxn*30],c[maxn*30];

int build(int l,int r)
{
    int root = tot++;
    if(l != r)
    {
        int mid = (l+r)>>1;
        lson[root] = build(l,mid);
        rson[root] = build(mid+1,r);
    }
    return root;
}

void ini_hash()  //����ȥ��
{
    for(int i = 1;i <= n;i++)
        t[i] = a[i];
    sort(t+1,t+n+1);
    m = unique(t+1,t+n+1)-(t+1);
}

int Hash(int x) //�õ�λ��
{
    return lower_bound(t+1,t+m+1,x)-t;
}

//������﷢���ı����˽�һ���ڵ������ƽ���޸��Ǹ��ڵ��ֵ
int update(int root,int pos,int val)
{
    int newroot = tot++;
    int tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1,r = m;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if(pos <= mid)
        {
            lson[newroot] = tot++;rson[newroot] = rson[root];
            newroot = lson[newroot]; root = lson[root];
            r = mid;
        }
        else
        {
            lson[newroot] = lson[root]; rson[newroot] = tot++;
            newroot = rson[newroot]; root = rson[root];
            l = mid+1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int lt,int rt,int k)
{
    int l = 1, r = m;
    while(l < r)
    {
         int mid = (l+r)>>1;
         if(c[lson[rt]] - c[lson[lt]] >= k)
         {
             r = mid;
             lt = lson[lt];
             rt = lson[rt];
         }
         else
         {
             l = mid+1;
             k -= (c[lson[rt]] - c[lson[lt]]);
             lt = rson[lt];
             rt = rson[rt];
         }
    }
    return l;
}

int main()
{
    int q;
    while(scanf("%d%d",&n,&q) !=EOF)
    {
        tot = 0;
        for(int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        ini_hash();
        T[0] = build(1,m);
        for(int i = 1;i <= n;i++)
        {
            int pos = Hash(a[i]);
            T[i] = update(T[i-1],pos,1);
        }
        while(q--)
        {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            printf("%d\n",t[query(T[l-1],T[r],k)]);
        }
    }
    return 0;
}

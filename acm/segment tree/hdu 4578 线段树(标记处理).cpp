/*
hdu 4578 �߶���(��Ǵ���)

����n����ʼ��Ϊ0�����������²�����
1 x y c ��[x,y]�ϵ���ȫ����c     add
2 x y c ��[x,y]�ϵ���ȫ����c     mult
3 x y c ��[x,y]�������ȫ��Ϊc   same
4 x y c ��ѯ[x,y]����������c�η��ĺ�,Ȼ���10007ȡģ

�������ǿ��Է��� �ӷ��ͳ˷����޷�ֱ��ά��������Ҫ�ĵ���������,������same����
sum = (r-l+1)*(tree[i].same^p).
���ÿ�β�ѯ���Ƕ����ҵ�����,�м���Ŀ���TLE�����Կ��ǲ�ѯ��ʱ��ֱ�Ӳ���same���,����pҲ��С��
Ȼ�������δ���add,mult,same��������ǵĳ�ͻ.
����same����,���µ�һ�����䣬��ô��ǰ��������ϵ����б�Ƕ�������
����add��mult�����Ի��ͻ,�������㲢����֪�����ȴ���add����mult.����
add��mult����ͬʱ����һ������,������ǰ����ı��Ҫ�ȸ�����ȥ.

���Ƕ���add��mult��3�����:  //��add����
1.�����ǰ������same,�����ظ���same�ͺ���
2.�����ǰ������mult,���ȶԵ�ǰ�������update_down,��mult����ȸ�����ȥ
3.���ֻ��add������,��ô����һ�¼���

�о��ͱ���·��ⷽ��,��Ҫ��ע�����໥֮���Ӱ�졣
hhh-2016-04-04 09:41:07
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 10007;
const int maxn = 100050;
struct node
{
    int l,r;
    ll mult,add,same;
    int mid()
    {
        return (l+r)>>1;
    }
    int len()
    {
        return (r-l+1) ;
    }
} tree[maxn<<2];

void update_up(int i)
{
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].mult=1;
    tree[i].add=0;
    tree[i].same = -1;
    if(l == r)
    {
        tree[i].same = 0;
        return ;
    }
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    update_up(i);
}

void update_down(int i)
{
    if(tree[i].same != -1)
    {
        tree[lson].add = tree[rson].add  = 0;
        tree[lson].mult= tree[rson].mult = 1;
        tree[lson].same = tree[rson].same = tree[i].same;
        tree[i].same = -1;
    }
    if(tree[i].add)
    {
        if(tree[lson].same != -1)
            tree[lson].same = (tree[lson].same+tree[i].add)%mod;
        else if(tree[lson].mult > 1)
        {
            update_down(lson);
            tree[lson].add = tree[i].add;
        }
        else
            tree[lson].add = (tree[lson].add+tree[i].add)%mod;
        if(tree[rson].same != -1)
            tree[rson].same = (tree[rson].same+tree[i].add)%mod;
        else if(tree[rson].mult > 1)
        {
            update_down(rson);
            tree[rson].add = tree[i].add;
        }
        else
            tree[rson].add = (tree[rson].add+tree[i].add)%mod;
        tree[i].add = 0;
    }
    if(tree[i].mult > 1)
    {
        if(tree[lson].same != -1)
            tree[lson].same = (tree[lson].same*tree[i].mult)%mod;
        else if(tree[lson].add)
        {
            update_down(lson);
            tree[lson].mult = tree[i].mult;
        }
        else
            tree[lson].mult = (tree[lson].mult*tree[i].mult)%mod;
        if(tree[rson].same != -1)
            tree[rson].same = (tree[rson].same*tree[i].mult)%mod;
        else if(tree[rson].add)
        {
            update_down(rson);
            tree[rson].mult = tree[i].mult;
        }
        else
            tree[rson].mult = (tree[rson].mult*tree[i].mult)%mod;
        tree[i].mult = 1;
    }
}

void update(int i,int l,int r,int flag,ll val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        if(flag == 1)
        {
            if(tree[i].same != -1)
                tree[i].same = (tree[i].same+val)%mod;
            else if(tree[i].mult > 1)
            {
                update_down(i);
                tree[i].add = val;
            }
            else
                tree[i].add =(tree[i].add+val)%mod;
        }
        else if(flag == 2)
        {
            if(tree[i].same != -1)
                tree[i].same = (tree[i].same*val)%mod;
            else if(tree[i].add)
            {
                update_down(i);
                tree[i].mult = val;
            }
            else
                tree[i].mult = (tree[i].mult * val) %mod;
        }
        else if(flag == 3)
        {
            tree[i].same = val;
            tree[i].same %= mod;
            tree[i].add = 0;
            tree[i].mult = 1;
        }
        return ;
    }
    int mid = tree[i].mid();
    update_down(i);
    if(l <= mid)
        update(lson,l,r,flag,val);
    if(r > mid)
        update(rson,l,r,flag,val);
    update_up(i);
}

ll query(int i,int l,int r,int p)
{
    if(tree[i].l == tree[i].r)
    {
        ll ans = 1;
        for(int j =1; j <= p; j++)
            ans =(ll)(ans*tree[i].same)%mod;
        return ans%mod;
    }
    if(tree[i].l >= l && tree[i].r <= r && tree[i].same != -1)
    {
        ll ans = 1;
        for(int j =1; j <= p; j++)
            ans =(ll)(ans*tree[i].same)%mod;
        ans = (ll)ans*(tree[i].len()%mod)%mod;
        return ans%mod;
    }
    ll all = 0;
    update_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        all =(all+query(lson,l,r,p))%mod;
    if(r > mid)
        all = (all+query(rson,l,r,p))%mod;
    return all;
}



int main()
{
    int t,n,m;
    while(scanf("%d%d",&n,&m) && n && m)
    {
        build(1,1,n);
        for(int i = 1; i <= m; i++)
        {
            int op,x,y;
            ll c;
            scanf("%d%d%d%I64d",&op,&x,&y,&c);
            if(op <= 3)
                update(1,x,y,op,c);
            else
                printf("%I64d\n",query(1,x,y,c));
        }
    }
    return 0;
}

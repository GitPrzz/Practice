/*
hdu 4747 �߶��� ˼·

��ʾ��ʼ����ͷ�����ܾ��ú��߶���������ʲô��ϵ- -

����Ҫ�����mex[i,j](i~j�в����ڵ���С�Ǹ�����)�ĺͣ��۲���Է��ֶ���1~n,
mex[1,i]�ǵ�����,��Ϊ�㵱ǰmexֵ�����ں������

Ȼ�����ȥ��a[1],���Է�����a[1]�ٴγ���֮ǰ.mexֵ����a[1]�Ķ�����a[1]
1 0 2 0 1  -> 0 2 3 3 3
ȥ��a[1]   ->   1 1 1 3

Ȼ�������˼·Ū���ɣ��ȴ����mex[1,i]������������߶���,Ȼ�����a[i]�´�
���ֵ�λ�á� �����߶������������a[i]�ٴγ���֮ǰ��a[i]�����Сλ�ã������
ȫ����Ϊa[i](�Ͼ���������ǵ�����),���ܿ��������.

hhh-2016-03-24 18:15:48
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 500550;
struct node
{
    int l,r;
    ll num;
    int Max,add;
    int mid()
    {
        return ((l+r)>>1);
    };
} tree[maxn<<2];

int a[maxn],nex[maxn],mex[maxn];
map<int,int> mp;

void update_up(int i)
{
    tree[i].num = tree[lson].num+tree[rson].num;
    tree[i].Max = max(tree[lson].Max,tree[rson].Max);
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].add = 0;
    if(l == r)
    {
        tree[i].num = mex[l];
        tree[i].Max = mex[l];
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    update_up(i);
}

void update_down(int i)
{
    if(tree[i].add)
    {
        tree[lson].add = 1;
        tree[rson].add = 1;
        tree[lson].num = (ll)tree[i].Max*(tree[lson].r-tree[lson].l+1);
        tree[rson].num = (ll)tree[i].Max*(tree[rson].r-tree[rson].l+1);
        tree[lson].Max= tree[i].Max;
        tree[rson].Max= tree[i].Max;
        tree[i].add = 0;
    }
}
void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && r >=  tree[i].r)
    {
        tree[i].num = (ll)(tree[i].r-tree[i].l+1)*val;
        tree[i].Max = val;
        tree[i].add = 1;
        return;
    }
    update_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    update_up(i);
}
int cur;
void get_k(int i,int k)
{
    if(tree[i].l ==  tree[i].r)
    {
        cur = tree[i].l;
        return ;
    }
    update_down(i);
    //int mid = tree[i].mid();
    if(k < tree[lson].Max)
        get_k(lson,k);
    else
        get_k(rson,k);
    update_up(i);
}

ll query(int i,int l,int r)
{
    if(tree[i].l >= l && r >= tree[i].r)
    {
        return tree[i].num;
    }
    update_down(i);
    int mid = tree[i].mid();
    ll ad = 0;
    if(l <= mid)
       ad += query(lson,l,r);
    if(r > mid)
       ad += query(rson,l,r);
    update_up(i);
    return ad;
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF && n)
    {
        int flag=  0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }

        int t = 0;
        mp.clear();
        for(int i = 1; i <= n; i++)
        {
            mp[a[i]] = 1;
            //cout << mp[t] <<endl ;
            while(mp.find(t) != mp.end()) t++;
            mex[i] = t;
        }

        build(1,1,n);
        mp.clear();
        for(int i = n; i >= 1; i--)
        {
            if(mp[a[i]] == 0) nex[i] = n+1;
            else nex[i] = mp[a[i]];
            mp[a[i]] = i;
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++)
        {
            int nx = nex[i];
            ans += query(1,i,n);
            //cout << ans <<endl;
            if(tree[1].Max > a[i])
            {
                get_k(1,a[i]);
                if(cur < nx)
                    Insert(1,cur,nx-1,a[i]);
                // cout << cur <<" "<<nx << " " << a[i] <<endl;
            }
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

/*
Sample Input
3
0 1 3
5
1 0 2 0 1
0


Sample Output
5
24
*/

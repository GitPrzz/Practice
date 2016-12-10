/*
hdu3333 线段树+思路不错GGGGG
好烦，记得做过类似的题，但这题还是没做出来--
先将所有查询按区间右端从小到大排序，如果一个数已经出现过就先把以前位置上的删
掉然后在新的位置上插入，像这样在[l,r]中重复的就只计算了一次
hhh-2016-02-29 20:58:20
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
using namespace std;
typedef long long ll;
const int maxn = 200050;

struct node
{
    int l,r;
    ll sum;
} tree[maxn*100];

struct e
{
    int l,r;
    int id;
} opr[maxn];

ll a[maxn];
ll tans[maxn];

bool cmp(e a,e b)
{
    return a.r < b.r;
}

void push_up(int r)
{
    int lson = r<<1;
    int rson = r<<1|1;
    tree[r].sum = (ll)(tree[lson].sum+tree[rson].sum);
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].sum = 0;
    if(l == r)
        return;
    int mid = (l+r)>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    push_up(i);
}

void update(int i,int k,ll c)
{
    if(tree[i].l == k && tree[i].r == k)
    {
        tree[i].sum += c;
        return ;
    }
    int mid = (tree[i].l+tree[i].r)>>1;
    if(k <= mid)update(i<<1,k,c);
    else update(i<<1|1,k,c);
    push_up(i);
}

ll query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].sum;
    int mid = (tree[i].l+tree[i].r)>>1;
    ll ans = 0;
    if(l <= mid)
        ans += query(i<<1,l,r);
    if(r > mid)
        ans += query(i<<1|1,l,r);
    return ans ;
}

int main()
{
    int n;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        build(1,1,n);
        for(int i =1; i <= n; i++)
            scanf("%I64d",&a[i]);
        int m;
        scanf("%d",&m);
        for(int i =1; i <= m; i++)
        {
            scanf("%d%d",&opr[i].l,&opr[i].r);
            opr[i].id = i;
        }

        map<ll,ll>mp;
        mp.clear();
        sort(opr+1,opr+m+1,cmp);
        for(int i =1,t = 1; i <= m; i++)
        {
            for(; t <= opr[i].r; t++)
            {
                if(mp[a[t]] != 0) update(1,mp[a[t]],-a[t]);
                mp[a[t]] = t;
                update(1,t,a[t]);
            }
            tans[opr[i].id] =query(1,opr[i].l,opr[i].r);
        }
        for(int i = 1; i <= m; i++)
        {
            printf("%I64d\n",tans[i]);
        }
    }
    return 0;
}

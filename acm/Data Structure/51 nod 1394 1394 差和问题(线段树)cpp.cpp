/*
51 nod 1394 1394 差和问题(线段树)

problem:
有一个多重集合S（即里面元素可以有重复），初始状态下有n个元素，对他进行如下操作：
1、向S里面添加一个值为v的元素。输入格式为1 v
2、向S里面删除一个值为v的元素。输入格式为2 v
3、询问S里面的元素两两之差绝对值之和。输入格式为3

solve:
每次向序列中添加数x时. 会对总体贡献: a[i]-x (a[i] > x), x-a[i] (a[i] < x)
就比x小的数而言, 会贡献 val - num*x (val:小于x的数的和  num:小于x的数的个数)
而删除操作就等同于将添加反过来弄一下
于是就成了计算序列中小于(大于)x的数的个数以及它们的总价值,线段树能实现.
但是数能达到1e9,而n却只有1e6,离散化处理一下

hhh-2016/09/06-17:09:25
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
const ll mod = 1000000007;
const int maxn = 200050;
const double PI = acos(-1.0);
const int limit = 33;
ll bin[maxn];
map<ll,int>mp;

template<class T> void read(T&num) {
    char CH; bool F=false;
    for(CH=getchar();CH<'0'||CH>'9';F= CH=='-',CH=getchar());
    for(num=0;CH>='0'&&CH<='9';num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p) {
    if(!p) { puts("0"); return; }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}

struct node
{
    int l,r;
    ll num,val;
} tree[maxn << 2];

void push_up(int i)
{
    tree[i].val = tree[lson].val + tree[rson].val;
    tree[i].num = tree[lson].num + tree[rson].num;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].val=  tree[i].num = 0;
    if(l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    build(lson,l,mid);
    build(rson,mid+1,r);
}
int ed;
void update(int i,int k,ll va)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        tree[i].num += va;
        if(va == 1)
            tree[i].val += bin[k];
        else
            tree[i].val -= bin[k];
        return ;
    }
    int mid = (tree[i].l+tree[i].r )>> 1;
    if(k <= mid)
        update(lson,k,va);
    else
        update(rson,k,va);
    push_up(i);
}
ll tval,tnum;
void query(int i,int l,int r)
{
    if(l > r)
    {
        tval = tnum = 0;return;
    }
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tval += tree[i].val;
        tnum += tree[i].num;

        return ;
    }
    int mid = (tree[i].l + tree[i].r ) >> 1;
    if(l <= mid)
        query(lson,l,r);
    if(r > mid)
        query(rson,l,r);
    push_up(i);
}
ll a[maxn/2];
int num[maxn];
struct Query
{
    int id;
    ll x;
} qry[maxn/2];

int main()
{
//    freopen("in.txt","r",stdin);
    int n,q,op;
    while(scanfi(n)!=EOF)
    {
//        clr(num,0);
        mp.clear();
        int cnt = 0;
        read(q);
        for(int i = 1; i <= n; i++)
        {
            read(a[i]);
            bin[cnt++] = a[i];
//            update(1,x,1);
        }
//        cout << q <<endl;
        for(int i = 0; i < q; i++)
        {
            read(qry[i].id);
            if(qry[i].id == 1 || qry[i].id == 2)
                read(qry[i].x),bin[cnt++] = qry[i].x;
        }
        sort(bin,bin+cnt);
        ed = unique(bin,bin+cnt)-bin;
        for(int i = 0; i < ed; i++)
            mp[bin[i]] = i,num[i] = 0;
        build(1,0,ed);
        ll ans = 0;
        for(int i = 1; i <= n; i++)
        {
//            cout << mp[a[i]] <<endl;
            update(1,mp[a[i]],1);
            tval = 0,tnum  = 0;
            query(1,0,mp[a[i]]-1);
            ans =ans-tval+tnum*a[i];
            tval = 0,tnum  = 0;
            query(1,mp[a[i]]+1,ed-1);
            ans = ans+tval-tnum*a[i];
            num[mp[a[i]]] ++ ;
        }
//        cout << ans <<endl;
        for(int i = 0; i < q; i++)
        {
            if(qry[i].id == 1)
            {
                tval = 0,tnum  = 0;
                query(1,0,mp[qry[i].x]-1);
                ans =ans-tval+tnum*qry[i].x;
//                cout <<tval << tnum <<endl;
                tval = 0,tnum  = 0;
                query(1,mp[qry[i].x]+1,ed-1);
                ans = ans+tval-tnum*qry[i].x;
                update(1,mp[qry[i].x],1);
                num[mp[qry[i].x]]++;
//                cout << ans <<endl;
            }
            else if(qry[i].id == 2)
            {
                if(num[mp[qry[i].x]] == 0){
                    printf("-1\n");
                    continue;
                }
                tval = 0,tnum  = 0;
                query(1,0,mp[qry[i].x]-1);
                ans =ans+tval-tnum*qry[i].x;
//                cout <<tval << tnum <<endl;
                tval = 0,tnum  = 0;
                query(1,mp[qry[i].x]+1,ed-1);
                ans = ans-tval+tnum*qry[i].x;
                update(1,mp[qry[i].x],-1);
//                cout << ans <<endl;
                num[mp[qry[i].x]]--;
            }
            else
            {
                print(ans);
            }
        }
    }
    return 0;
}

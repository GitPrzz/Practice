/*
hdu 5700���佻(�߶���)

problem:
����һ�������Լ�m�����䣬Ȼ��ѡ�����е�k������ʹ�����ཻ����ĺ����

solve:
�ʼ����Ƕ��ִ�Ȼ���ж��ܷ��ҳ�k������ʹ��ĺʹﵽ,�����������ŷ��ֺ���ǰ���������߶������������������
ö��������Ҷ˵�,Ȼ���ҳ�����ĸ��˵�ʹ��պø��ǵ�k������,Ȼ����ֵȡ���ֵ
������Ҫά����˵ĸ���,�Լ����ҳ���kС����˵�,���߶������.
��Ϊö�ٵ����Ե�ǰ��Ϊ����������Ҷ˵�,���Գ��ֹ�������Ҫ��ȥ(��ɾ��������˵�).

hhh-2016-08-13 15:15:56
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
typedef unsigned int ul;
const int INF = 0x3f3f3f3f;
const int  maxn = 100000+10;
const int mod = 1e9+7;

struct Tree
{
    int l,r;
    int lval,mid;
} tree[maxn<<2];

void push_up(int i)
{
    tree[i].lval = tree[lson].lval+tree[rson].lval;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r,tree[i].lval = 0;
    if(l == r)
        return;
    tree[i].mid= (l+r) >>1;
    int mid = tree[i].mid;
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void Insert(int i,int k,int val)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        tree[i].lval += val;
//        cout <<"pos: " << tree[i].l <<" val: "<<tree[i].lval<< endl;
        return ;
    }
//    cout <<tree[i].l << " "<< tree[i].r << "k "<<k <<" val: "<<val<< endl;
    int mid = tree[i].mid;

    if(k <= mid)
        Insert(lson,k,val);
    else
        Insert(rson,k,val);
    push_up(i);
//    cout <<tree[i].l << " "<< tree[i].r <<" val: "<<tree[i].lval<< endl;
}

int query(int i ,int k)
{
//    cout << tree[i].lval << " " <<tree[i].l << " "<< tree[i].r <<endl;
    if(tree[i].l == tree[i].r)
        return tree[i].l;
    if(k <= tree[lson].lval)
        return query(lson,k);
    else
       return  query(rson,k-tree[lson].lval);
    push_up(i);
}

int query_num(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].lval;
    }
    int num = 0;
    if(l <= tree[i].mid)
        num += query_num(lson,l,r);
    if(r > tree[i].mid)
        num += query_num(rson,l,r);
    return num;
}

struct node
{
    int l,r;
} pnode[maxn];

ll Max(ll a,ll b)
{
    if(a < b)
        return b;
    return a;
}

bool cmp(node a,node b)
{
    if(a.r != b.r)
        return a.r < b.r;
    else
        return a.l < b.l;
}
ll num[maxn];
int main()
{
    int n,k,m;
    while(scanf("%d%d%d",&n,&k,&m) != EOF)
    {
        num[0] = 0;
        build(1,1,n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%I64d",&num[i]);
            num[i] += num[i-1];
        }
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d",&pnode[i].l,&pnode[i].r);
            Insert(1,pnode[i].l,1);
        }
        sort(pnode+1,pnode+m+1,cmp);

        int now = 1;
        ll ans = 0;
        for(int i = 1; i <= n && now <= m; i++)
        {
            if(i == pnode[now].r)
            {
//                cout << "r:"<<pnode[now].r << endl;
                int t = query_num(1,1,i);
                if(t >= k)
                {
                    int l = query(1,k);
//                     cout<<"l:" << l << endl;
                    ans = Max(ans,num[i]-num[l-1]);
                }
//                cout<<"ans:"<<ans <<"  t:" << t << endl;
            }
            while(now <= m && pnode[now].r == i)
            {
                Insert(1,pnode[now].l,-1);
                now ++;
            }
        }
        cout << ans <<endl;
    }
    return 0;
}

/*
5 2 3
1 2 3 4 5
1 2
3 4
5 5
*/

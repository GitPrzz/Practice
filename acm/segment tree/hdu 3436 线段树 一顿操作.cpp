/*
hdu 3436 线段树 一顿操作

这个题以前用splay树做过,但是最近练习线段树中(据说线段树能解决splay树中的很多操作)
Top:     将第x个数移动到队首
Query:   查询x的位置
Rank:    找出排第x的数

top想的数之间在线段树前面预留一部分,于是线段树最多需要2e5.对于Rank可以直接查找
主要是对于Query没想到什么办法.最后直接是用数组来保存每个数的位置,然后利用求和便能得到
某数在这个队列中的位置

hhh-2016-04-12 19:20:16
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
typedef long long ll;
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;

const int maxn = 1e6+10;

struct node
{
    int l,r;
    int sum,val;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];
int T,n,m;
int a[maxn];
int ano[maxn];
int st[maxn],en[maxn];
int pos[maxn];
char op[maxn][6];
int tot,TOT;

void push_up(int i)
{
    tree[i].sum = tree[lson].sum + tree[rson].sum;
}

void build(int i ,int l,int r)
{
    tree[i].l =l ,tree[i].r = r;
    tree[i].sum = 0;
    tree[i].val = 0;
    if(l == r)
    {
        if(tree[i].l > m)
        {
            int t = tree[i].l-m;
            tree[i].val = t;
            tree[i].sum = en[t]-st[t]+1;
        }
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void update(int i,int k,int val)
{
    if(tree[i].l == tree[i].r )
    {
        if(!val) tree[i].sum = 0,tree[i].val = 0;
        else tree[i].sum = en[val]-st[val]+1,tree[i].val = val;
        return ;
    }
    int mid = tree[i].mid();
    if(k <= mid)
        update(lson,k,val);
    else
        update(rson,k,val);
    push_up(i);
}

int sum(int i,int l,int r)
{
    if(tree[i].l>=l && tree[i].r <= r)
        return tree[i].sum;
    int mid = tree[i].mid();
    int su = 0;
    if(l <= mid)
        su += sum(lson,l,r);
    if(r > mid)
        su += sum(rson,l,r);
    push_up(i);
    return su;
}

int get_k(int i,int k)
{
    if(tree[i].l == tree[i].r && k <= en[tree[i].val]-st[tree[i].val]+1)
        return st[tree[i].val]+k-1;
    int mid = tree[i].mid();

    if(k <= tree[lson].sum)
        return get_k(lson,k);
    else
        return get_k(rson,k-tree[lson].sum);
    push_up(i);
}


int bin(int key)
{
    int l = 1,r = tot-1;
    while(l <= r)
    {
        int mid = (l+r)>>1;
        if(st[mid]<=key && en[mid]>=key)
            return mid;
        else if(key < st[mid])
            r = mid - 1;
        else
            l = mid + 1;
    }
}

int main()
{
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        tot = 0;
        for(int i = 1; i <= m; i++)
        {
            scanf("%s%d",op[i],&a[i]);
            if(op[i][0] == 'T' || op[i][0] == 'Q')
                ano[tot++] = a[i];
        }
        ano[tot++] = 1,ano[tot++] = n;
        sort(ano,ano+tot);
//        for(int i = 0;i < tot;i++)
//            cout << ano[i] <<" ";
//        cout << endl;
        TOT = tot;
        tot = 1;
        st[tot] = ano[0],en[tot] = ano[0];
        tot++;
        printf("Case %d:\n",cas++);
        for(int i = 1; i < TOT; i++)
        {
            if(ano[i] != ano[i-1])
            {
                if(ano[i] - ano[i-1] > 1)
                {
                    st[tot] = ano[i-1]+1;
                    en[tot++] = ano[i]-1;
                }
                st[tot] = ano[i];
                en[tot] = ano[i];
                tot++;
            }
        }
//        for(int i = 1;i < tot;i++)
//            cout <<st[i] << " "<<en[i] <<endl;
        build(1,1,m+tot-1);
        memset(ano,0,sizeof(ano));
        int cur = m;
        for(int i = 1; i <= m; i++)
        {
            int tp = bin(a[i]);
            //cout << "val:" << a[i] << " "<<tp<<endl;
            if(op[i][0] == 'T')
            {
                if(ano[tp])
                {
                    update(1,pos[tp],0);
                    update(1,cur,tp);
                    pos[tp] = cur;
                    cur --;
                }
                else
                {
                    update(1,m+tp,0);
                    update(1,cur,tp);
                    pos[tp] = cur;
                    cur--;
                    ano[tp] = 1;
                }
            }
            else if(op[i][0] == 'Q')
            {
                if(ano[tp])
                {
                    printf("%d\n",sum(1,1,pos[tp]));
                }
                else
                {
                    printf("%d\n",sum(1,1,m+tp));
                }
            }
            else
            {
                printf("%d\n",get_k(1,a[i]));
            }
        }
    }
    return 0;
}

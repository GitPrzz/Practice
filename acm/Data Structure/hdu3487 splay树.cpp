/*
hdu3487 splay树
cut是将一串数字复制到另外一个位置，flip是将一串数字逆序
cut直接进行一次删除插入即可，flip则是给个转换标记然后更新
hhh-2016-02-20 06:50:15
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
typedef long  double ld;
#define key_value ch[ch[root][1]][0]
const int maxn = 300010;

int ch[maxn][2];
int rev[maxn],a[maxn];
int pre[maxn],key[maxn],siz[maxn];
int root,TOT,cnt,n;

void push_up(int r)
{
    int lson = ch[r][0],rson = ch[r][1];
    siz[r] = siz[lson] + siz[rson] + 1;
}

void update_rev(int r)
{
    if(!r) return ;
    swap(ch[r][0],ch[r][1]);
    rev[r] ^= 1;
}

void push_down(int r)
{
    if(rev[r])
    {
        update_rev(ch[r][0]);
        update_rev(ch[r][1]);
        rev[r] = 0;
    }
}

void inOrder(int r)
{
    if(!r)return;
    push_down(r);
    inOrder(ch[r][0]);
    if(cnt >=1 && cnt <= n)
    {
        printf("%d",key[r]);
        if(cnt < n)printf(" ");
        else printf("\n");
    }
    cnt++;
    inOrder(ch[r][1]);
}

void debug()
{
    cnt = 0;
    inOrder(root);
}

void NewNode(int &r,int far,int k)
{
    r = ++TOT;
    pre[r] = far;
    ch[r][0] = ch[r][1] = 0;
    key[r] = k;
    siz[r] = 1;
    rev[r] = 0;
}


void rotat(int x,int kind)
{
    int y = pre[x];
    push_down(y);
    push_down(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if(pre[y])
        ch[pre[y]][ch[pre[y]][1]==y] = x;
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    push_up(y);
}

void build(int &x,int l,int r,int far)
{
    if(l > r) return ;
    int mid = (l+r) >>1;
    NewNode(x,far,mid);
    build(ch[x][0],l,mid-1,x);
    build(ch[x][1],mid+1,r,x);
    push_up(x);
}

void splay(int r,int goal)
{
    push_down(r);
    while(pre[r] != goal)
    {
        if(pre[pre[r]] == goal)
        {
            push_down(pre[r]);
            push_down(r);
            rotat(r,ch[pre[r]][0] == r);
        }
        else
        {
            push_down(pre[pre[r]]);
            push_down(pre[r]);
            push_down(r);
            int y = pre[r];
            int kind = ch[pre[y]][0] == y;
            if(ch[y][kind] == r)
            {
                rotat(r,!kind);
                rotat(r,kind);
            }
            else
            {
                rotat(y,kind);
                rotat(r,kind);
            }
        }
    }
    push_up(r);
    if(goal == 0)
        root = r;
}

int get_kth(int r,int k)
{
    push_down(r);
    int t = siz[ch[r][0]]+1;
    if(t == k) return r;
    if(t > k) return get_kth(ch[r][0],k);
    else return  get_kth(ch[r][1],k-t);
}


int CUT(int l,int r,int b)
{
    splay(get_kth(root,l),0);
    splay(get_kth(root,r+2),root);
    int tmp = key_value;
    pre[key_value] = 0;
    key_value = 0;
    push_up(ch[root][1]);
    push_up(root);

    splay(get_kth(root,b+1),0);
    splay(get_kth(root,b+2),root);
    pre[tmp] = ch[root][1];
    key_value = tmp;
    push_up(ch[root][1]);
    push_up(root);
    //debug();
}

void Reverse(int l,int r)
{
    splay(get_kth(root,l),0);
    splay(get_kth(root,r+2),root);
    update_rev(key_value);
    push_up(ch[root][1]);
    push_up(root);
    //debug();
}


void ini(int n)
{
    TOT = root = 0;
    ch[root][0] = ch[root][1] = pre[root] = siz[root] = 0;
    rev[root] = 0;
    NewNode(root,0,-1);
    NewNode(ch[root][1],root,-1);
    build(key_value,1,n,ch[root][1]);
    //inOrder(root);
     //printf("\n");
    push_up(ch[root][1]);
    push_up(root);
}

int main()
{
    int q;
    while(scanf("%d%d",&n,&q) != EOF)
    {

        if(n == -1 && q == -1)
            break;
        ini(n);
        for(int i =1; i <= q; i++)
        {
            char qry[10];
            scanf("%s",qry);
            int a,b,len;
            if(qry[0] == 'C')
            {
                scanf("%d%d%d",&a,&len,&b);
                CUT(a,len,b);
            }
            else
            {
                scanf("%d%d",&a,&b);
                Reverse(a,b);
            }
        }
        cnt = 0;
        inOrder(root);
    }
    return 0;
}

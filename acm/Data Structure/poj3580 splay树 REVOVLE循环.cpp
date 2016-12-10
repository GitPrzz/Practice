/*
poj3580 splay树 REVOVLE循环
给定一个数列:a1,a2,.... an
进行以下6种操作：
ADD x y D : 给第x个数到第y个数加D
REVERSE x y : 反转[x,y]
REVOVLE x y T : 对[x,y]区间的数循环右移T次  (这个最开始没想到这么弄)
(先把T对长度取模，然后相当于把[y-T+1,y]放到[x,y-T] 的前面)
INSERT x P  : 在第x个数后面插入P
DELETE x : 删除第x个数
 MIN x y  : 查询[x,y]之间的最小的数

像min，add是参照rev，size来写。然后就只有第三个操作可以一开始想不到，其它大致就是各种基本操作的组合了
好像删点有多个写法，最开始写错del导致TLE几次

hhh-2016-02-21 03:06:02
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
const int maxn = 200010;

int ch[maxn][2];
int pre[maxn],siz[maxn],num[maxn];
int rev[maxn],key[maxn];
int add[maxn];
int Min[maxn],a[maxn];
int tot;
int root;
void push_up(int r)
{
    int lson = ch[r][0],rson = ch[r][1];
    siz[r] = siz[lson] + siz[rson] + 1;
    Min[r] = min(key[r],min(Min[lson],Min[rson]));
}

void update_add(int r,int val)
{
    if(!r) return;
    key[r] += val;
    add[r] += val;
    Min[r] += val;
}

void update_rev(int r)
{
    if(!r)return ;
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
    if(add[r])
    {
        update_add(ch[r][0],add[r]);
        update_add(ch[r][1],add[r]);
        add[r] = 0;
    }
}


void NewNode(int &r,int far,int k)
{
    r = ++tot;      //不能为0
    pre[r] = far;
    ch[r][0] = ch[r][1] = 0;
    siz[r] = 1;
    Min[r] = k;
    key[r] = k;
    rev[r] = 0;
    add[r] = 0;
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
    NewNode(x,far,a[mid]);
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
    int t = siz[ch[r][0]] + 1;
    if(k == t)return r;
    if(t > k) return get_kth(ch[r][0],k);
    else return get_kth(ch[r][1],k-t);
}

int get_next(int r)
{
    push_down(r);
    if(ch[r][1] == 0)return -1;
    r = ch[r][1];
    while(ch[r][0])
    {
        r = ch[r][0];
        push_down(r);
    }
    return r;
}

void Reverse(int l,int r)
{
    splay(get_kth(root,l),0);
    splay(get_kth(root,r+2),root);
    update_rev(key_value);
    push_up(ch[root][1]);
    push_up(root);
}

void Add(int l,int r,int val)
{
    splay(get_kth(root,l),0);
    splay(get_kth(root,r+2),root);
    update_add(key_value,val);
    push_up(ch[root][1]);
    push_up(root);
}

void ini(int n)
{
    tot = root = 0;
    ch[root][0] = ch[root][1] = pre[root] = siz[root] = num[root] = 0;
    Min[root] = 0x3f3f3f3f;
    rev[root] = add[root] = 0;
    NewNode(root,0,-1);
    NewNode(ch[root][1],root,-1);
    for(int i=1; i <= n; i++)
    {
        scanf("%d",&a[i]);
    }
    build(key_value,1,n,ch[root][1]);

    push_up(ch[root][1]);
    push_up(root);
}

int get_min(int r)
{
    push_down(r);
    while(ch[r][0])
    {
        r = ch[r][0];
        push_down(r);
    }
    return r;
}

void Delete(int r)
{
    splay(get_kth(root,r+1),0);
    if(ch[root][0] == 0 || ch[root][1] == 0)
    {
        root = ch[root][0] + ch[root][1];
        pre[root] = 0;
        return;
    }
    int k = get_min(ch[root][1]);
    splay(k,root);
    ch[ch[root][1]][0] = ch[root][0];
    root = ch[root][1];
    pre[ch[root][0]] = root;
    pre[root] = 0;
    push_up(root);
}

void Insert(int x,int y)
{
    splay(get_kth(root,x+1),0);
    splay(get_kth(root,x+2),root);
    NewNode(key_value,ch[root][1],y);
    push_up(ch[root][1]);
    push_up(root);
}

int MIN(int x,int y)
{
    splay(get_kth(root,x),0);
    splay(get_kth(root,y+2),root);
    push_up(ch[root][1]);
    push_up(root);
    return Min[key_value];
}

void Revovle(int x,int y,int T)
{
    splay(get_kth(root,y-T+1),0);
    splay(get_kth(root,y+2),root);
    int tmp = key_value;
    //pre[key_value] = 0;
    key_value = 0;
    push_up(ch[root][1]);
    push_up(root);

    splay(get_kth(root,x),0);
    splay(get_kth(root,x+1),root);
    key_value = tmp;
    pre[key_value] = ch[root][1];
    push_up(ch[root][1]);
    push_up(root);
}

int main()
{
    int n,p;
    while(scanf("%d",&n) != EOF)
    {
        ini(n);
        scanf("%d",&p);
        char opr[20];
        int x,y,z;
        while(p--)
        {
            scanf("%s",opr);
            if(strcmp(opr,"ADD") == 0)
            {
                scanf("%d%d%d",&x,&y,&z);
                Add(x,y,z);
            }
            else if(strcmp(opr,"INSERT") == 0)
            {
                scanf("%d%d",&x,&y);
                Insert(x,y);
            }
            else if(strcmp(opr,"DELETE") == 0)
            {
                scanf("%d",&x);
                Delete(x);
            }
            else if(strcmp(opr,"MIN") == 0)
            {
                scanf("%d%d",&x,&y);
                printf("%d\n",MIN(x,y));
//                for(int i =1;i <= 5;i++)
//                    printf("%d\n",Min[i]);
            }
            else if(strcmp(opr,"REVERSE") == 0)
            {
                scanf("%d%d",&x,&y);
                Reverse(x,y);
            }
            else if(strcmp(opr,"REVOLVE") == 0)
            {
                scanf("%d%d%d",&x,&y,&z);
                int t = (y-x+1);
                z = (z%t+t)%t;
                Revovle(x,y,z);
            }
        }
    }
    return 0;
}

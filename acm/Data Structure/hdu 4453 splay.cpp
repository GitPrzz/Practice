/*
hdu 4453 splay
把环换成链然后进行splay即可
主要是move那个操作开始想复杂了，只需要直接进行删除插入
add、reverse、insert、delete、query
move 1：把第n+1个点删除，然后放入第一个点之后。
move 2：把第2个点删除，然后放入第n+1个点后。
hhh-2016-02-21 07:01:08
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
int tot,tp;
int root,n;
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

void inOrder(int r)
{
    if(!r)
        return;
    inOrder(ch[r][0]);
    printf("%d ",key[r]);
    inOrder(ch[r][1]);
}

void debug()
{
    inOrder(root);
    cout <<endl;
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
    r = ++tot;
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

int Delete(int r)
{
    int t = get_kth(root,r+1);
    splay(t,0);
    if(ch[root][0] == 0 || ch[root][1] == 0)
    {
        root = ch[root][0] + ch[root][1];
        pre[root] = 0;
        return key[t];
    }
    int k = get_min(ch[root][1]);
    splay(k,root);
    ch[ch[root][1]][0] = ch[root][0];
    root = ch[root][1];
    pre[ch[root][0]] = root;
    pre[root] = 0;
    push_up(root);
    n--;
    return key[t];
}

void Insert(int x,int y)
{
    splay(get_kth(root,x),0);
    splay(get_kth(root,x+1),root);
    NewNode(key_value,ch[root][1],y);
    push_up(ch[root][1]);
    push_up(root);
    n++;
}

void Move(int x)
{
   if(x == 1)
   {
       int t = Delete(n);
       Insert(1,t);
//       debug();
   }
   else
   {
       int t = Delete(1);
       Insert(n+1,t);
   }
}


int main()
{
    int p,k1,k2;
    int cas = 1;
    while(scanf("%d%d%d%d",&n,&p,&k1,&k2) != EOF)
    {
        if(!n && !p && !k1 && !k2)
            break;
        printf("Case #%d:\n",cas++);
        ini(n);
        char opr[10];
        int x;
        for(int i =1; i <= p; i++)
        {
            scanf("%s",opr);
            if(opr[0] == 'a')
            {
                scanf("%d",&x);
                Add(1,k2,x);
            }
            else if(opr[0] == 'm')
            {
                scanf("%d",&x);
                Move(x);
            }
            else if(opr[0] == 'r')
            {
                Reverse(1,k1);
            }
            else if(opr[0] == 'q')
            {
                printf("%d\n",key[get_kth(root,2)]);
            }
            else if(opr[0] == 'i')
            {
                scanf("%d",&x);
                Insert(2,x);
            }
            else if(opr[0] == 'd')
            {
                Delete(1);
            }
        }
    }
    return 0;
}

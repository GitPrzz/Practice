/*
hdu 3436 splay树+离散化*
本来以为很好做的，写到中途发现10^8,GG
然后参考了下，把操作不用的区间缩点离散化处理
然后就是删除点，感觉自己开始写的太麻烦了，将要删除的点移动到根，如果没有儿子直接删掉，
否则将右树的最小点移到ch[r][1]使右树没有左子树，然后把根的左树接到右树上
hhh-2016-02-20 22:22:22
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
int pre[maxn],key[maxn],siz[maxn],num[maxn];

int root,tot,cnt,n,TOT;
int posi[maxn];
char qry[maxn][10];
int op[maxn];
int te[maxn];
int s[maxn],e[maxn];

void Treaval(int x) {
    if(x) {
        Treaval(ch[x][0]);
        printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,key = %2d   num= %2d \n",x,ch[x][0],ch[x][1],pre[x],siz[x],key[x],num[x]);
        Treaval(ch[x][1]);
    }
}
void debug() {printf("%d\n",root);Treaval(root);}

void push_up(int r)
{
    int lson = ch[r][0],rson = ch[r][1];
    siz[r] = siz[lson] + siz[rson] + num[r];
}

void push_down(int r)
{

}

void inOrder(int r)
{
    if(!r)return;
    inOrder(ch[r][0]);
    printf("%d ",key[r]);
    inOrder(ch[r][1]);
}


void NewNode(int &r,int far,int k)
{
    r = ++tot;
    posi[k] = r;
    key[r] = k;
    pre[r] = far;
    ch[r][0] = ch[r][1] = 0;
    siz[r] = num[r] = e[k]-s[k]+1;
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

int Bin(int x)
{
    int l = 0,r = TOT-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(s[mid]<=x&&e[mid]>=x)
            return mid;
        if(e[mid]<x)
            l=mid+1;
        else
            r=mid-1;
    }
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

int get_kth(int r,int k)
{
    int t = siz[ch[r][0]];
    if(k<=t)
        return get_kth(ch[r][0],k);
    else if(k<=t+num[r])
        return s[key[r]]+(k-t)-1;
    else
        return get_kth(ch[r][1],k-t-num[r]);
}

void delet()
{
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


int top(int t)
{
    int r = Bin(t);
    r = posi[r];
    splay(r,0);
    delet();
    splay(get_min(root),0);
    ch[r][0] = 0;
    ch[r][1] = root;
    pre[root] = r;
    root = r;
    pre[root] = 0;
    push_up(root);
//    debug();
}

int Query(int x)
{
    int r = Bin(x);
    r = posi[r];
    splay(r,0);
    return siz[ch[r][0]]+1;
}

int get_rank(int x,int k)
{
    int t = siz[ch[x][0]];
    if(k <= t)
        return get_rank(ch[x][0],k);
    else
        return get_rank(ch[x][1],k-t);
}


void ini(int n)
{
    tot = root = 0;
    ch[root][0] = ch[root][1] = pre[root] = siz[root] = num[root] = 0 ;
    build(root,0,n-1,0);

    push_up(ch[root][1]);
    push_up(root);
    //inOrder(root);
}


int main()
{
    int q,T;
    int cas =1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&q) ;
        if(n == -1 && q == -1)
            break;

        int tcn = 0;
        printf("Case %d:\n",cas++);
        for(int i =1; i <= q; i++)
        {
            scanf("%s%d",qry[i],&op[i]);
            if(qry[i][0] == 'T' || qry[i][0] == 'Q')
                te[tcn++] = op[i];
        }
        te[tcn++] = n;
        te[tcn++] = 1;
        sort(te,te+tcn);
        TOT= 0;
        s[TOT] = te[0],e[TOT] = te[0],TOT++;
        for(int i = 1; i < tcn; i++)
        {
            if(te[i] != te[i-1] && i)
            {
                if(te[i] - te[i-1] > 1)
                {
                    s[TOT] = te[i-1]+1;
                    e[TOT] = te[i]-1;
                    TOT++;
                }
                s[TOT] = te[i];
                e[TOT] = te[i];
                TOT++;
            }
        }
        ini(TOT);
        //debug();
        for(int i = 1; i <= q; i++)
        {
            if(qry[i][0]=='T')
                top(op[i]);
            else if(qry[i][0]=='Q')
                printf("%d\n", Query(op[i]));
            else
                printf("%d\n",get_kth(root,op[i]));
        }
        //debug();
    }
    return 0;
}

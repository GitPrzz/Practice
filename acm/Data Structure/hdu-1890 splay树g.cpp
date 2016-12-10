/*
hdu-1890 splay��g
��ʼ������չ�������ֵ��Ȼ�����������ͬ�Ľ����˽�����Ȼ�������ֵ��������
3 3 2 1 -> 4 2 4 4 ���ҵ���4 2 4 3����Ϊ��ÿ����ȥ�ҵ�ĳ��ֵ��λ�ã���ֵͬ�Ļ��Ϳ����ҵ���С�Ǹ�ֵȥ��
���������b[3] = b[4]= 3�����ȴ���b[3],Ȼ��b[3],b[4]����������b[4]ʱ�ͳ�����bug��Ȼ��GG
׼ȷ˵�Ƕ����������ϳ����ˣ���ȻӢ����O__O "��

���������������꽨�������ڷ�תget_kth�ҵ����е�k��λ�ã�Ȼ��get_next�ҳ�������i��ĺ����Ǹ���Ȼ����Ǽ���.
������λ�ã�ֱ�Ӱ��������ת������Ȼ���������ӵĴ�С����һ����

hhh-2016-02-21 01:10:21
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
int pre[maxn],siz[maxn],num[maxn];
int rev[maxn];
int root,tot,cnt,n;
struct Node
{
    int val,id;
}node[maxn];

bool cmp(Node a,Node b)
{
    if(a.val != b.val) return a.val < b.val;
    else return a.id < b.id;
}

void push_up(int r)
{
    int lson = ch[r][0],rson = ch[r][1];
    siz[r] = siz[lson] + siz[rson] + 1;
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
}


void NewNode(int &r,int far,int k)
{
    r = k;
    pre[r] = far;
    ch[r][0] = ch[r][1] = 0;
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



void ini(int n)
{
    root = 0;
    ch[root][0] = ch[root][1] = pre[root] = siz[root] = num[root] = 0 ;
    NewNode(root,0,n+1);
    NewNode(ch[root][1],root,n+2);
    build(key_value,1,n,ch[root][1]);

    push_up(ch[root][1]);
    push_up(root);
}


int main()
{
    int q,T;
    int cas =1;
    while(scanf("%d",&n) != EOF)
    {
        if(!n)
            break;
        for(int i=1; i <= n; i++)
        {
            scanf("%d",&node[i].val);
            node[i].id = i;
        }
        sort(node+1,node+n+1,cmp);
        ini(n);
        for(int i = 1; i <= n; i++)
        {
           splay(node[i].id,0);
           printf("%d",siz[ch[root][0]]);
           if(i != n) printf(" ");
           else printf("\n");
           splay(get_kth(root,i),0);
           splay(get_next(node[i].id),root);
           update_rev(key_value);
        }
    }
    return 0;
}

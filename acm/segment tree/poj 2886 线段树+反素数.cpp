/*
poj 2886 线段树+反素数
反素数：
（1）给定一个数，求一个最小的正整数，使得的约数个数为
（2）求出中约数个数最多的这个数

反素数以前也大概学习过，但是做这个题的时候并没有想到优化方法
问题很严重- -

给你n个数围成一圈，然后每个人对应一个数字
如果x是正数，则下一个人是左边第x个。如果x为负数，则下一个人是
右边第-x个

大致思路是没啥问题，但是开始是将所有数进行预处理，求出第i个数
的f[i]，然后同过线段树判断左右两边的剩余人数，然后TLE

后来发现别人都是先反素数打表，rprim[0]表示有rprim[1]个因子时的最
大值,然后便能1-n中f[]最大值p的位置。然后只需从1模拟到p求出这时对
应的人即可

hhh-2016-03-23 23:50:13
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
int rprim[35][2] =
{
    498960,200,332640,192,277200,180,221760,168,166320,160,
    110880,144,83160,128,55440,120,50400,108,45360,100,
    27720,96,25200,90,20160,84,15120,80,10080,72,
    7560,64,5040,60,2520,48,1680,40,1260,36,
    840,32,720,30,360,24,240,20,180,18,
    120,16,60,12,48,10,36,9,24,8,
    12,6,6,4,4,3,2,2,1,1
};
struct node
{
    int l,r;
    int num;
    int mid()
    {
        return ((l+r)>>1);
    };
} tree[maxn<<2];


void update_up(int i)
{
    tree[i].num = tree[lson].num + tree[rson].num;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;

    if(l == r)
    {
        tree[i].num = 1;
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    update_up(i);
}

void update_down(int i)
{

}
int cur;
void Insert(int i,int k)
{
    if(tree[i].l ==  tree[i].r)
    {
        cur = tree[i].l;
        tree[i].num = 0;
        return ;
    }
    update_down(i);
    int mid = tree[i].mid();
    if(k <= tree[lson].num)
        Insert(lson,k);
    else
        Insert(rson,k-tree[lson].num);
    update_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
        return tree[i].num;
    update_down(i);
    int mid = tree[i].mid();
    int all = 0;
    if(l <= mid)
        all += query(lson,l,r);
    if(r > mid)
        all += query(rson,l,r);
    return all;
}

char nam[maxn][13];
int a[maxn];

int main()
{
    int k,n,t,m,nex;
    while(scanf("%d%d",&n,&k) != EOF)
    {
        t = 0;
        while(n < rprim[t][0])
            t++;
        int x = rprim[t][0];
        for(int i = 1; i <= n; i++)
        {
            scanf("%s%d",nam[i],&a[i]);
        }
        build(1,1,n);
        cur = k,m = n;
        for(int i = 1; i < x; i++)
        {
            //cout << cur << endl;
            Insert(1,cur);
           //cout << cur <<endl;
            nex = a[cur];
            m--;
            if(nex%m == 0)
            {
                if(nex < 0) nex = 1;
                else nex = m;
            }
            else
            {
                nex %= m;
                if(nex < 0) nex += (m+1);
            }
            int leftnum = query(1,1,cur);
            int rightnum = m - leftnum;
            if(nex <= rightnum) cur = leftnum + nex;
            else cur = nex-rightnum;
        }
        Insert(1,cur);
        printf("%s %d\n",nam[cur],rprim[t][1]);
    }
    return 0;
}

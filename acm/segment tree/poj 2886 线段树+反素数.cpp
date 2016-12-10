/*
poj 2886 �߶���+������
��������
��1������һ��������һ����С����������ʹ�õ�Լ������Ϊ
��2�������Լ���������������

��������ǰҲ���ѧϰ����������������ʱ��û���뵽�Ż�����
���������- -

����n����Χ��һȦ��Ȼ��ÿ���˶�Ӧһ������
���x������������һ��������ߵ�x�������xΪ����������һ������
�ұߵ�-x��

����˼·��ûɶ���⣬���ǿ�ʼ�ǽ�����������Ԥ���������i����
��f[i]��Ȼ��ͬ���߶����ж��������ߵ�ʣ��������Ȼ��TLE

�������ֱ��˶����ȷ��������rprim[0]��ʾ��rprim[1]������ʱ����
��ֵ,Ȼ�����1-n��f[]���ֵp��λ�á�Ȼ��ֻ���1ģ�⵽p�����ʱ��
Ӧ���˼���

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

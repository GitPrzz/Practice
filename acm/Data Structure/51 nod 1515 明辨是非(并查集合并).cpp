/*
51 nod 1515 �����Ƿ�(���鼯�ϲ�)

problem:
���ֲ�����
x y 1: �����x,��y����������ͬ,�����YES,����������ͬ. �������NO
x y 0: �����x,��y�������Բ���ͬ ......

solve:
��ͬ�����ò��鼯��ά��.  ���ǲ�ͬ����, ���a,b��ͬ, b,c��ͬ.����a,c������ͬ. ��ʼ���ӳ��˶��ò��鼯 ��...
��set��¼һ��ÿ�������䲻ͬ��������Щ. Ȼ���ж��������Ƿ����ʱֱ�ӽ��в���.��Ҫ�ж����Ǹ������ڵĲ��鼯
�ϲ���ʱ���ٰ�set����һ�¾ͺ�. printfһֱTL,����putsAC.

hhh-2016/09/04-17:18:40
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
const int maxn = 200010;
const double PI = acos(-1.0);
struct node
{
    int x,y,kind;
} qry[maxn];
int id[maxn];
set<int>q[maxn];
map<int,int> mp;
set<int>::iterator it;
int par[maxn];

int fin(int x)
{
    if(par[x] == x) return x;
    return par[x] = fin(par[x]);
}

void unio(int x,int y)
{
    if(x == y)
        return ;
    if(q[x].size() > q[y].size())
    {
        int t = x;
        x = y;
         y = t ;
    }
    par[x] = y;
    for(it = q[x].begin(); it != q[x].end(); it++)
    {
        q[y].insert(*it);
    }
}


int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n;
    scanfi(n);
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        par[i] = i;
        scanfi(qry[i].x),scanfi(qry[i].y);
        scanfi(qry[i].kind);
        id[cnt++] = qry[i].x,id[cnt++] = qry[i].y;
    }
    sort(id,id+cnt);
    int total = unique(id,id+cnt)-id;
    for(int i = 0; i < total; i++)
        mp[id[i]] = i;
//        cout << total <<endl;
//        for(int i = 0;i <= total;i++)
//            cout <<id[i] <<" " ;
//        cout <<endl;
    for(int i =1 ; i <= n; i++)
    {
//            cout << qry[i].x <<" " <<qry[i].y << " "<<qry[i].kind <<endl;
        int x = mp[qry[i].x];
        int y =  mp[qry[i].y];
        int tx = fin(x),ty = fin(y),flag =0;
        if(qry[i].kind == 1)
        {
//                cout << x <<" " <<y <<endl;
            if(q[tx].size() > q[ty].size())
            {
                it = q[ty].find(tx);
                if(it != q[ty].end())
                    flag = 1;
                for(it = q[ty].begin(); !flag && it != q[ty].end(); it++)
                {
                    if(fin(*it) == tx)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            else
            {
                it = q[tx].find(ty);
                if(it != q[tx].end())
                    flag = 1;
                for(it = q[tx].begin(); !flag &&it != q[tx].end(); it++)
                {
                    if(fin(*it) == ty)
                    {
                        flag = 1;
                        break;
                    }
                }
            }
            if(flag)
                puts("NO");
            else
            {
                puts("YES");
                unio(tx,ty);
            }
        }
        else
        {
            if(tx == ty)
                puts("NO");
            else
            {
                puts("YES");
                q[tx].insert(ty);
                q[ty].insert(tx);
            }
        }
    }


    return 0;
}

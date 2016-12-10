/*
51 nod 1515 明辨是非(并查集合并)

problem:
两种操作：
x y 1: 如果第x,第y个数可以相同,则输出YES,并令他们相同. 否则输出NO
x y 0: 如果第x,第y个数可以不相同 ......

solve:
相同可以用并查集来维护.  但是不同则不行, 如果a,b不同, b,c不同.但是a,c可以相同. 开始脑子抽了都用并查集 卒...
先set记录一下每个数与其不同的数有哪些. 然后判断两个数是否不相等时直接进行查找.并要判断他们各自所在的并查集
合并的时候再把set处理一下就好. printf一直TL,换成putsAC.

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

/*
hdu 5444
二叉树的模拟题，但是GG了两次。
主要是没注意到直接模拟会爆掉- -，进行下处理就好了
hhh-2016-02-02 04:42:01
*/
#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <Map>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;

const int maxn = 1005;
int a[maxn];
int lroot[maxn];
int rroot[maxn];
int cnt ;
void add(int x,int root)
{
    if(a[root] == -1)
    {
        a[root] = x;
        return ;
    }
    else if(x < a[root])
    {
        if(lroot[root] != -1)
            add(x,lroot[root]);
        else
        {
            lroot[root] = ++cnt;
            add(x,lroot[root]);
        }
    }
    else if(x > a[root])
    {
        if(rroot[root] != -1)
            add(x,rroot[root]);
        else
        {
            rroot[root] = ++cnt;
            add(x,rroot[root]);
        }
    }
    return ;
}

void qurey(int x ,int root)
{
    if(x == a[root])
        return ;
    else if(x < a[root])
    {
        printf("E");
        qurey(x,lroot[root]);
    }
    else if(x > a[root])
    {
        printf("W");
        qurey(x,rroot[root]);
    }
}

int main()
{
    int T,n,x,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        cnt = 1;
        memset(a,-1,sizeof(a));
        memset(lroot,-1,sizeof(lroot));
        memset(rroot,-1,sizeof(rroot));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&x);
            add(x,1);
        }
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d",&x);
            qurey(x,1);
            printf("\n");
        }
    }
}

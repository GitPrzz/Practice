/*
hdu5336 Tire树
给你一串数，求(a[i] + a[j])^a[k]的最大值
思路：先把所有数插入树中，每次枚举删除i，j，然后在树种查找匹配a[i]+a[j]的最大值
查完后把i，j插入
hhh-2016-02-03 23:19:32
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
typedef long long ll;
typedef long double ld;
const int inf = 0x3f3f3f3f;
const int maxn = 1000005;
int tot;
int root = 0;
int a[maxn];
struct node
{
    int next[2];
    int num;
} tree[maxn];

void add(int x)
{
    int t = root;
    for(int i = 30; i >= 0; i--)
    {
        int dir;
        if(x&(1<<i)) dir = 1;
        else dir = 0;
        if(tree[t].next[dir] == 0)
            tree[t].next[dir] = ++tot;
        t = tree[t].next[dir];
        tree[t].num++;
    }
}

void delet(int x)
{
    int t = root;
    for(int i = 30; i >= 0; i--)
    {
        int dir;
        if(x&(1<<i)) dir = 1;
        else dir = 0;
        t = tree[t].next[dir];
        tree[t].num--;
    }
}

int match(int x)
{
    int t = root;
    for(int i = 30; i >= 0; i--)
    {
        int dir;
        if(x&(1<<i)) dir = 1;
        else dir = 0;
        if(dir == 1)
        {
            int tp = tree[t].next[0];
            if(tree[tp].num > 0 && tp) t = tree[t].next[0];
            else
            {
                t = tree[t].next[1];
                x ^= (1<<i);
            }
        }
        else
        {
            int tp = tree[t].next[1];
            if(tree[tp].num > 0 && tp)
            {
                t = tree[t].next[1];
                x ^= (1<<i);
            }
            else
            {
                t = tree[t].next[0];
            }
        }
    }
    return x;
}

void ini()
{
    tot = 0;
}

int main()
{
    int n,T;
    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d",&n);
        int ans = 0;
        for(int i =1 ; i <= n; i++)
        {
            scanf("%d",&a[i]);
            add(a[i]);
        }
        for(int i =1; i <= n; i++)
        {
            delet(a[i]);
            for(int j = i +1; j <= n; j++)
            {
                delet(a[j]);
                ans = max(ans,match(a[i]+a[j]));
                add(a[j]);
            }
            add(a[i]);
        }
        printf("%d\n",ans);
        for(int i = 0;i < tot;i++)
        {
            tree[i].num = 0;
            tree[i].next[0] = tree[i].next[1] = 0;
        }
    }
    return 0;
}

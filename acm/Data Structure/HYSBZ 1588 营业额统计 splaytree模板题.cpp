/*
HYSBZ 1588 营业额统计 splaytree模板题
求解营业额波动，即今天销售额 与 前面所有每日销售额中差值最小的数，然后求它们的和
伸展树通过伸展操作可以将你添加的旋转到根节点，而且他还是二叉排序树，所以可以
快速地求出根节点 左边最大值 和 右边最小值
hhh-2016-02-03 00:19:07
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;

using namespace std;
const int maxn = 100005;
int pre[maxn];
int child[maxn][2];
int root,tot;
int val[maxn];

void newnode(int &x,int far,int k)
{
    x = ++tot;
    pre[x] = far;
    val[x] = k;
    child[x][0] = child[x][1] = 0;
}

//kind=0左旋  kind=1右旋
void rotat(int x,int kind)
{
    int y = pre[x];
    child[y][!kind] = child[x][kind];
    pre[child[x][kind]]= y;
    if(pre[y])
        child[pre[y]][child[pre[y]][1] == y] = x;
    pre[x] = pre[y];
    child[x][kind] = y;
    pre[y] = x;

}

void splay(int x,int goal)
{
    while(pre[x] != goal)
    {
        if(pre[pre[x]] == goal)
        {
            rotat(x,child[pre[x]][0] == x);
        }
        else
        {
            int y = pre[x];
            int kind = child[pre[y]][0] == y;
            if(child[y][kind] == x)
            {
                rotat(x,!kind);
                rotat(x,kind);
            }
            else
            {
                rotat(y,kind);
                rotat(x,kind);
            }
        }
    }
    if(goal == 0)
        root = x;
}

int Insert(int x)
{
    int t = root;
    while(child[t][x>val[t]])
    {
        if(val[t] == x)
        {
            splay(t,0);
            return 0;
        }
        t = child[t][x > val[t]];
    }
    newnode(child[t][x > val[t]],t,x);
    splay(child[t][x > val[t]],0);
    return 1;
}

int getPre(int x)
{
    int t = child[x][0];
    if(t == 0) return 0x3f3f3f;
    while(child[t][1])
    {
        t = child[t][1];
    }
    return val[x] - val[t];
}

int getNext(int x)
{
    int t = child[x][1];
    if(t == 0) return 0x3f3f3f;
    while(child[t][0])
    {
        t = child[t][0];
    }
    return val[t]-val[x];
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        root = tot = 0;
        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            int x;
            if(scanf("%d",&x) == EOF) x = 0;
            int flag = Insert(x);
            if(!flag) continue;
            if(i == 1)
                ans += x;
            else
                ans += min(getPre(root),getNext(root));
        }
        printf("%d\n",ans);
    }
}

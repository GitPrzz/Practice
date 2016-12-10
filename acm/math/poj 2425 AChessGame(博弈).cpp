/*
poj 2425 AChessGame(博弈)

给你一个有向的图，上面的棋子可以移动到下一个节点，如果当前无法移动则失败

可以同dfs求出所有节点的sg值，然后进行计算即可

hhh-2016-08-02 16:50:29

4
2 1 2
0
1 3
0
1 0
2 0 2
0

4
1 1
1 2
0
0
2 0 1
2 1 1
3 0 1 3
0

*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>
typedef long long ll;
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;



const int maxn = 1000+10;

int sg[maxn];
int Map[maxn][maxn];
int n;
void dfs(int now)
{
    int vis[maxn] = {0};
    for(int i = 0; i < n; i++)
    {
        if(Map[now][i])
        {
            if(sg[i] == -1)
                dfs(i);
            vis[sg[i]] = 1;
        }

    }
    for(int i = 0; i < n; i++)
    {
        if(!vis[i])
        {
            sg[now] = i;
            break;
        }
    }
}

int main()
{
    int x,m;
    while(scanf("%d",&n) != EOF && n)
    {
        memset(sg,-1,sizeof(sg));
        memset(Map,0,sizeof(Map));
        for(int i = 0; i < n; i++)
        {
            scanf("%d",&m);
            for(int j = 1; j <= m; j++)
            {
                scanf("%d",&x);
                Map[i][x] = 1;
            }
        }
        for(int i = 0; i < n; i++)
        {
            if(sg[i] == -1)
                dfs(i);
        }
        while(scanf("%d",&m)!=EOF && m)
        {
            int ans = 0;
            for(int i = 0; i < m; i++)
            {
                scanf("%d",&x);
                ans ^= sg[x];
            }
            if(ans)
                printf("WIN\n");
            else
                printf("LOSE\n");
        }
    }
    return 0;
}



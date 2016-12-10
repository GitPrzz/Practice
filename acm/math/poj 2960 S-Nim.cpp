/*
poj 2960 S-Nim

先给你一个集合，然后是类似于NIM游戏，但是你每次只能从这些石碓中取出集合中的个数，
搞出SG值然后进行计算即可
而且这题 sort什么的会RE.

hhh-2016-08-02 18:16:21
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
const int maxn = 10000+10;

int sg[maxn];
int s[maxn];
int n;

void SG(int now)
{
    if(sg[now] != -1)
        return ;
    int vis[maxn];
    memset(vis,0,sizeof(vis));
    for(int i = 0; i < n; i++)
    {
        int t = now-s[i];
        if(t < 0)
            continue;
        SG(t);
        vis[sg[t]] = 1;
    }

    for(int i = 0;; i++)
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
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n) != EOF && n)
    {
        for(int i = 0; i < n; i++)
            scanf("%d",&s[i]);
        //sort(s,s+n);
        memset(sg,-1,sizeof(sg));
        sg[0] = 0;
        scanf("%d",&m);
        while(m--)
        {
            int ans = 0,cnt;
            scanf("%d",&cnt);
            for(int i = 0; i < cnt; i++)
            {
                scanf("%d",&x);
                if(sg[x] == -1)
                    SG(x);
                ans ^= sg[x];
            }
            if(ans)
                printf("W");
            else
                printf("L");
        }
        printf("\n");

    }
    return 0;
}



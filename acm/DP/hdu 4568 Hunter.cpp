/*
hdu 4568 Hunter 最短路+dp

problem:
给你一个n*m的地图,每走一个格子会有一定的花费.求拿到所有宝藏的最小花费

solve:
想了很久感觉没什么思路TAT
后来看别人题解可以把这个问题转换一下.
因为总共只有13个宝藏,所以我们可以处理出每个宝藏之间的最短路(即最小花费).
在弄出每个宝藏到边界的最小距离. 那么就可以看成13个点的图.找出遍历所有点的最小花费
13个点的状态可以用二进制保存,所以dp就好.

hhh-2016-08-26 21:43:38
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
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 220;

struct NODE
{
    int id,len;
    NODE() {}
    NODE(int i,int d):id(i),len(d) {}
    bool operator <(const NODE &a) const
    {
        return len >  a.len;
    }
};
int n,m;
int dx[4]= {-1,1,0,0};
int dy[4]= {0,0,-1,1};
int from[maxn][maxn];
int vis[maxn*maxn],tmap[maxn][maxn],tp[maxn][maxn],out[maxn];
int pos[maxn*maxn],dis[maxn*maxn];
void dij(int st,int fp)
{
    memset(vis,0,sizeof(vis));
    memset(dis,inf,sizeof(dis));
    priority_queue<NODE> q;
    q.push(NODE(st,0));
    dis[st] = 0;
    while(!q.empty())
    {
        NODE t = q.top();
        q.pop();
        int cur = t.id;
        if(vis[cur]) continue;
        vis[cur] = 1;
        int x = cur/m,y = cur%m;
        if(tp[x][y] != -1)
            from[fp][tp[x][y]] = dis[cur];
        if(x == n-1 || x == 0 || y == m-1 || y == 0)
        {
            out[fp]= min(out[fp],dis[cur]);
        }
        for(int i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if(tmap[tx][ty] == -1) continue;
            if(tx >= n || tx < 0 || ty >= m || ty < 0)
                continue;
            if(dis[tx*m + ty] > dis[cur] + tmap[tx][ty])
            {
                dis[tx*m + ty] = dis[cur] + tmap[tx][ty];
                q.push(NODE(tx*m + ty, dis[tx*m + ty] ));
            }
        }
    }
    return ;
}

int dp[20][1 << 14];
void init()
{
    memset(from,0,sizeof(from));
    memset(out,inf,sizeof(out));
    memset(tp,-1,sizeof(tp));
    memset(dp,inf,sizeof(dp));
}


int main()
{
//    freopen("in.txt","r",stdin);
    int T,x,y;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanfi(n),scanfi(m);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                scanfi(tmap[i][j]);
        }
        int q;
        scanfi(q);
        for(int i = 0; i < q; i++)
        {
            scanfi(x),scanfi(y);
            tp[x][y] = i;
            pos[i] = x*m + y;
        }
        for(int i = 0; i < q; i++)
        {
            from[i][i] = 0;
            dij(pos[i],i);
        }
        for(int i = 0; i < q; i++)
        {
            dp[i][1 << i] = out[i]+tmap[pos[i]/m][pos[i]%m];
        }
//        for(int i = 0;i < q;i++)
//        {
//            cout << "i"<<i<<":" <<out[i] <<endl;
//            for(int j = i;j < q;j++)
//                cout << i <<"----"<<j<<" :" <<from[i][j]<<endl;
//        }
//        cout <<endl;
        for(int i = 0; i < (1 << q); i++)
        {
            for(int j = 0; j < q; j++)
            {
                if( ((1 << j) & i) && i != (1 << j))
                {
                    for(int k = 0; k < q; k++)
                    {
                        if( (i & (1 << k)) && j != k && i != (1<< k))
                            dp[j][i] = min(dp[k][i-(1 << j)]+from[k][j],dp[j][i]);
                    }
                }
            }
        }
        int ans = inf;
        for(int i = 0; i < q; i++)
        {
            ans = min(ans,dp[i][(1<<q)-1] + out[i]);
//            cout << ans <<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}

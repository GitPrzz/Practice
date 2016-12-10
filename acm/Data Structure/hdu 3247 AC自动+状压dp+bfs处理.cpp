/*
hdu 3247 AC自动+状压dp+bfs处理

给你n个正常子串,m个病毒子串,求出最短的字符串(包含所有正常子串,不包含病毒串)

因为正常子串只有十个,所以考虑二进制来记录。
即dp[i][j]表示 包含的正常串的状态为i,最后一步的状态为j的最短情况.
然后试了下发现超内存 卒~

然后膜拜大神,发现我们可以预处理出来正常串之间的最短距离. 像这样我们只需要枚举所有的
正常串. 而我原先那个思路需要枚举所有的节点总共需要dp[1<<10][60040].  而对于通过bfs优化后
我们只需要枚举正常串 最多有11个 ->  dp[1<<10][11].

hhh-2016-04-30 14:34:51
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef unsigned long long ll;
typedef unsigned int ul;
const int mod = 20090717;
const int INF = 0x3f3f3f3f;
const int N = 100050;
int cnt;
int n,m;
int dp[1<<10][205];
int G[205][205];
int pos[205];
struct Tire
{
    int nex[N][2],fail[N],ed[N];

    int root,L;
    int newnode()
    {
        for(int i = 0; i < 2; i++)
            nex[L][i] = -1;
        ed[L++] = 0;
        return L-1;
    }

    void ini()
    {
        L = 0,root = newnode();
    }

    void inser(char buf[],int val)
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = buf[i]-'0';
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        if(val < 0)
        ed[now] = val;
        else
            ed[now] = (1<<val);
    }

    void build()
    {
        queue<int >q;
        fail[root] = root;
        for(int i = 0; i < 2; i++)
            if(nex[root][i] == -1)
                nex[root][i] = root;
            else
            {
                fail[nex[root][i]] = root;
                q.push(nex[root][i]);
            }
        while(!q.empty())
        {
            int now = q.front();
            q.pop();
            if(ed[fail[now]] < 0)
                ed[now] = ed[fail[now]];
            else if(ed[now] == 0)
                ed[now] = ed[fail[now]];
            for(int i = 0; i < 2; i++)
            {
                if(nex[now][i] == -1)
                    nex[now][i] = nex[fail[now]][i];
                else
                {
                    fail[nex[now][i]] = nex[fail[now]][i];
                    q.push(nex[now][i]);
                }
            }
        }
    }
    int dis[N];
    void Path(int k)
    {
        int now;
        queue<int >q;
        q.push(pos[k]);
        memset(dis,-1,sizeof(dis));
        dis[pos[k]] = 0;
        while(!q.empty())
        {
            now = q.front();
            q.pop();
            for(int i =0;i < 2;i++)
            {
                int t = nex[now][i];
                if(dis[t] < 0 && ed[t] >= 0)
                {
                    dis[t] = dis[now]+1;
                    q.push(t);
                }
            }
        }
        for(int i = 0;i < cnt;i++)
        {
            G[k][i] = dis[pos[i]];
        }
    }

    int Min(int a,int b)
    {
        if(a < 0)
            return b;
        else if(b < 0)
            return a;
        else
            return min(a,b);
    }

    void solve()
    {
        memset(dp,-1,sizeof(dp));
        dp[0][0] = 0;

        for(int i = 0;i < (1<<n);i++)
        {
            for(int j = 0;j < cnt;j++)
            {
                if(dp[i][j] < 0)
                    continue;
                for(int k = 0;k < cnt;k++)
                {
                    if(G[j][k] < 0)
                        continue;
                    int t = (i|ed[pos[k]]);
                    dp[t][k] = Min(dp[i][j] + G[j][k],dp[t][k]);
                }
            }
        }
        int ans = -1;
        for(int i = 0;i < cnt;i++)
        {
            ans = Min(ans,dp[(1<<n)-1][i]);
        }
        cout << ans <<"\n";
    }
};

Tire ac;
char buf[N];
int main()
{
    while(scanf("%d%d",&n,&m)==2 && n && m)
    {
        ac.ini();
        for(int i = 0; i < n; i++)
        {
            scanf("%s",buf);
            ac.inser(buf,i);
        }
        for(int i =0 ; i < m; i++)
        {
            scanf("%s",buf);
            ac.inser(buf,-1);
        }
        ac.build();
        pos[0] = 0;
        cnt = 1;
        for(int i = 0; i < ac.L; i++)
        {
            if(ac.ed[i] > 0)
                pos[cnt++] = i;
        }
        memset(G,-1,sizeof(G));
        for(int i = 0; i < cnt; i++)
            ac.Path(i);
        ac.solve();
    }
    return 0;
}

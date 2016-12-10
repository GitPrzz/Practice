/*
hdu 2457 AC自动机+dp

给你n个子串和一个主串. 对主串最少修改多少次后使其不包含子串
通过AC自动机能够处理出 一个状态转移图
用dp[i][j]表示长度为i,当前位置为j的最小修改数. nex[j][k] 状态k的节点编号
如果当前位置与主串相同则不需要修改, 否则 +1
而且通过ed数组我们判断当前是否已经走到任意子串的结尾.
那么 dp[i][nex[j][k]] = min(dp[i][nex[j][k]],dp[i-1][j] + (k == str[i]? 0:i));

hhh-2016-04-24 11:23:59
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
const int INF = 0x3f3f3f3f;
int tot;
int dp[2][1010];

//struct Matrix
//{
//    int len;
//    int ma[1010][1010];
//    Matrix() {}
//    Matrix(int L)
//    {
//        len = L;
//    }
//};

struct Tire
{
    int nex[1010][4],fail[1010],ed[1010];
    int root,L;
    int newnode()
    {
        for(int i = 0; i < 4; i++)
            nex[L][i] = -1;
        ed[L++] = 0;
        return L-1;
    }

    void ini()
    {
        L = 0,root = newnode();
    }

    int cal(char ch)
    {
        if(ch == 'A')
            return 0;
        else if(ch == 'C')
            return 1;
        else if(ch == 'G')
            return 2;
        else if(ch == 'T')
            return 3;
    }

    void inser(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = cal(buf[i]);
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        ed[now]  ++;
    }

    void build()
    {
        queue<int >q;
        fail[root] = root;
        for(int i = 0; i < 4; i++)
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
            if(ed[fail[now]])
                ed[now] = 1;
            for(int i = 0; i < 4; i++)
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

//    Matrix to_mat()
//    {
//        Matrix mat(L);
//        memset(mat.ma,0,sizeof(mat.ma));
//        for(int i = 0; i < L; i++)
//        {
//            for(int j = 0; j < 4; j++)
//            {
//                if(!ed[nex[i][j]])
//                    mat.ma[i][nex[i][j]] ++;
//            }
//        }
//        return mat;
//    }
};



//Matrix mat;
Tire ac;
char str[1100];
char buf[22];
int main()
{
    int n;
    int cas = 1;
    while(scanf("%d",&n) != EOF && n)
    {
        ac.ini();
        for(int i = 1; i <= n; i++)
        {
            scanf("%s",buf);
            ac.inser(buf);
        }
        ac.build();
//        mat = ac.to_mat();
        for(int i = 0; i < ac.L; i++)
            dp[0][i] = INF;
        dp[0][0] = 0;
        int cur = 0;
        scanf("%s",str);
        for(int i = 0; i < (int)strlen(str); i++)
        {
            cur ^= 1;
            for(int i = 0; i < ac.L; i++)
                dp[cur][i] = INF;
            for(int j = 0; j < ac.L; j++)
            {
                for(int k = 0; k < 4; k++)
                {
                    if(dp[cur^1][j] != INF && !ac.ed[ac.nex[j][k]])
                        dp[cur][ac.nex[j][k]] = min(dp[cur][ac.nex[j][k]] , dp[cur^1][j] + (k == ac.cal(str[i]) ? 0:1));
                }
            }


        }
        int ans = INF;
        for(int i = 0; i < ac.L; i++)
                ans = min(ans,dp[cur][i]);
        printf("Case %d: ",cas++);
        if(ans == INF)
            cout << -1 <<"\n";
        else
            cout << ans <<"\n";
    }
    return 0;
}

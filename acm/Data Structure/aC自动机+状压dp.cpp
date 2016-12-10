/*
hdu 2825 aC自动机+状压dp

给你m个子串,求长度为n的主串中至少出现k个子串的方案数
首先通过AC自动机构建关系图. 然后用dp解决状态转移,需要知道用过哪些子串
因为k比较小,我们直接转换成二进制来记录当前状态包含了哪些子串。用ed对各子串进行标记

dp[i][j][t]就表示长度为i,当前位置上是j时,所包含子串的情况t

hhh-2016-04-24 17:13:36
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
int tot;
int dp[30][111][1<<10];

struct Matrix
{
    int len;
    int ma[111][111];
    Matrix() {};
    Matrix(int L)
    {
        len = L;
    }
};

struct Tire
{
    int nex[110][26],fail[110],ed[110];
    int root,L;
    int newnode()
    {
        for(int i = 0; i < 26; i++)
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

    void inser(char buf[],int id)
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = buf[i] - 'a';
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        ed[now]  |= (1<<id);
    }

    void build()
    {
        queue<int >q;
        fail[root] = root;
        for(int i = 0; i < 26; i++)
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
                ed[now] |= ed[fail[now]];
            for(int i = 0; i < 26; i++)
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

    Matrix to_mat()
    {
        Matrix mat(L);
        memset(mat.ma,0,sizeof(mat.ma));
        for(int i = 0; i < L; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(!ed[nex[i][j]])
                    mat.ma[i][nex[i][j]] ++;
            }
        }
        return mat;
    }
};



//Matrix mat;
Tire ac;
char buf[22];

void debug()
{
    Matrix t = ac.to_mat();
    for(int i = 0; i < t.len; i++)
    {
        for(int j = 0; j < 26; j++)
        {
            printf("%d ",t.ma[i][ac.nex[i][j]]);
        }
        printf("\n");
    }
}

int num[1<<10];

int main()
{
    for(int i=0; i<(1<<10); i++)
    {
        num[i] = 0;
        for(int j = 0; j < 10; j++)
            if(i & (1<<j))
                num[i]++;
    }
    int n,m,p;
    while(scanf("%d%d%d",&n,&m,&p) != EOF)
    {
        if(!n && !m && !p)
            break;
        ac.ini();
        for(int i = 0; i < m; i++)
        {
            scanf("%s",buf);
            ac.inser(buf,i);
        }
        ac.build();
        for(int i = 0; i <= n; i++)
        {
            for(int j = 0; j <ac.L; j++)
            {
                for(int k = 0; k < (1<<m); k++)
                    dp[i][j][k] = 0;
            }
        }
        dp[0][0][0] = 1;
        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < ac.L; j++)
            {
                for(int t = 0; t < (1<<m); t++)
                {
                    if(dp[i][j][t] > 0)
                        for(int k = 0; k < 26; k++)
                        {
                            int nexi = i+1;
                            int nexj = ac.nex[j][k];
                            int nexk = (t|ac.ed[nexj]);
                            dp[nexi][nexj][nexk] = (dp[nexi][nexj][nexk] + dp[i][j][t])%mod;

                        }
                }
            }
        }
        int ans = 0;
        for(int j = 0; j < (1<<m); j++)
        {
            if(num[j] < p)
                continue;
            for(int i = 0; i < ac.L; i++)
                ans = (ans+dp[n][i][j])%mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}

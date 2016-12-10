/*
hdu 2296 aC自动机+dp(得到价值最大的字符串)

给你m个子串,每个子串有自己的价值,让你求出长度为小于等于n的价值最大的字符串.
要求字符串的长度尽可能的小,长度相同时字典序最小即可

在生成状态转换图之后用,dp的思想解决.
用dp[i][j]记录长度为i时且状态为j时的最大值,与此同时用str[i][j][55]记录这个字符串
当价值相同时,对字符串进行比较即可.

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
const int N = 12*105;
int tot;
int n,m;
char tp[55];
int dp[55][N];
char ans[55][N][55];

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

int Compare(char a[],char b[])
{
    int len1 = strlen(a);
    int len2 = strlen(b);
    if(len1 != len2) return len1 > len2;
    return strcmp(a,b);
}

struct Tire
{
    int nex[N][26],fail[N],ed[N];
    int root,L;
    int newnode()
    {
        for(int i = 0; i < 26; i++)
            nex[L][i] = -1;
        ed[L++] = -1;
        return L-1;
    }

    void ini()
    {
        L = 0,root = newnode();
        memset(ed,-1,sizeof(ed));
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

    void inser(char buf[],int val)
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
        ed[now] = val;
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
//            if(ed[fail[now]])
//                ed[now] = ed[fail[now]];
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

    void solve()
    {
        for(int j = 0; j <= n; j++)
        {
            for(int i = 0; i < N; i++)
                dp[j][i] = -1;
        }
        dp[0][0] = 0;
        char tan[55] = {""};
        int tMax = 0;
        strcpy(ans[0][0],"");
        strcpy(tp,"");
        for(int i = 1; i <= n; i++)
            for(int j = 0; j < N; j++)
            {
                if(dp[i-1][j] >= 0)
                {
                    strcpy(tp,ans[i-1][j]);
                    int len = strlen(tp);
                    for(int k = 0; k < 26; k++)
                    {
                        int t= dp[i-1][j];
                        if(ed[nex[j][k]] > 0)
                            t += ed[nex[j][k]];
                        tp[len] = 'a'+k;
                        tp[len+1] = 0;
                        if(t > dp[i][nex[j][k]] || (t == dp[i][nex[j][k]] && Compare(ans[i][nex[j][k]],tp) > 0))
                        {
                            strcpy(ans[i][nex[j][k]],tp);
                            dp[i][nex[j][k]] = t;

                        }
                        if(t >tMax || (tMax == t && Compare(tan,tp) > 0))
                        {
                            tMax = t;
                            strcpy(tan,tp);
                        }
                    }
                }
            }
       // printf("%d\n",tMax);
        printf("%s\n",tan);
    }
};



Tire ac;
char buf[105][12];


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        ac.ini();
        for(int i = 0; i < m; i++)
        {
            scanf("%s",buf[i]);
        }
        int x;
        for(int i = 0; i < m; i++)
        {
            scanf("%d",&x);
            ac.inser(buf[i],x);
        }
        ac.build();
        ac.solve();
    }
    return 0;
}

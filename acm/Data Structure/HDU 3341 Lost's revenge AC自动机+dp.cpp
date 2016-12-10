/*
HDU 3341 Lost's revenge AC�Զ���+dp

��n���Ӵ���һ���ַ���str,str�е�λ�ÿ���������.�������ܰ������ٸ��Ӵ�
������ʹ��dp,�����ڱ���״̬��ʱ���������. ��Ϊ��AGCT�ĸ�,��ô�����Ҫ���ڴ�
����40*40*40*40 ���ڴ�

��ʵ������str���ܳ���Ϊ40,�� A+C+G+T�ĸ���Ϊ40,��ô�����Ҫ�ڴ��Ҳ����10*10*10*10
�����Ļ�dp[i][j]������ ��ǰ�ڵ�Ϊi,AGCT��ʹ��״̬Ϊjʱ�����ֵ;   //dp��Ӳ��TAT
Ȼ������ظ����Ӵ�ҲҪ�ظ����㡣

hhh-2016-04-27 22:11:06
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
const int N = 505;
int tot;
int n;
int dp[N][11*11*11*11+10];
int tal[10];
int num[4];
int can(int id,int wt)
{
    if(wt == 0)
        return id/1000000;
    else if(wt == 1)
        return id/10000%100;
    else if(wt == 2)
        return id/100%100;
    else if(wt == 3)
        return id%100;
}

struct Tire
{
    int nex[N][4],fail[N],ed[N];
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
        ed[now]++;
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
            ed[now] += ed[fail[now]];
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

    void solve(int len)
    {
        memset(dp,-1,sizeof(dp));
        dp[0][0] = 0;
        num[0] = (tal[3]+1)*(tal[1]+1)*(1+tal[2]);
        num[1] = (tal[2]+1)*(tal[3]+1);
        num[2] = tal[3]+1;
        num[3] = 1;
        for(int t0 = 0; t0 <= tal[0]; t0++)
            for(int t1 = 0; t1 <= tal[1]; t1++)
                for(int t2 = 0; t2 <= tal[2]; t2++)
                    for(int t3 = 0; t3 <= tal[3]; t3++)
                        for(int i = 0; i < L; i++)
                        {
                            int tn = t1*num[1]+t2*num[2]+t3+t0*num[0];
                            if(dp[i][tn] >= 0)
                                for(int k = 0; k < 4; k++)
                                {
                                    int ta = nex[i][k];
                                    if(k == 0 && t0 == tal[0])continue;
                                    if(k == 1 && t1 == tal[1])continue;
                                    if(k == 2 && t2 == tal[2])continue;
                                    if(k == 3 && t3 == tal[3])continue;
                                    dp[ta][tn+num[k]] = max(dp[ta][tn+num[k]],dp[i][tn] + ed[ta]);
                                }
                        }


        int ans = 0;
        int ta = num[0]*tal[0]+num[1]*tal[1]+num[2]*tal[2]+num[3]*tal[3];
        for(int i =0 ; i < L; i++)
        {
            ans = max(ans,dp[i][ta]);
        }
        printf("%d\n",ans);
    }
};



Tire ac;
char buf[50];

int main()
{
    int cas = 1;
    while(scanf("%d",&n)==1 && n)
    {
        ac.ini();

        for(int i = 0; i < n; i++)
        {
            scanf("%s",buf);
            ac.inser(buf);
        }
        ac.build();
        scanf("%s",buf);
        memset(tal,0,sizeof(tal));
        for(int i = 0; i < (int)strlen(buf) ; i++)
        {
            tal[ac.cal(buf[i])]++;
        }
        printf("Case %d: ",cas++);
        ac.solve(strlen(buf));
    }
    return 0;
}

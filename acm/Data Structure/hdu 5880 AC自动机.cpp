/*
hdu 5880 AC自动机

problem:
给你一些子串，然后在文章中将这些子串屏蔽掉.

solve:
用AC自动机扫一扫,然后给需要屏蔽的地方打下标记

hhh-2016-09-17 20:51:55
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
const int maxn = 1001000;

char s[maxn];
int dis[maxn];
int ans[maxn];

struct Tire
{
    int nex[1001000][27],fail[1001000],ed[1001000];
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

    int cha(char x)
    {
        return x-'a';
    }

    void inser(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = cha(buf[i]);
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        ed[now] = 1;
        dis[now] = len;
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
//            if(ed[fail[now]])
//                ed[now] = 1;
            q.pop();
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

    void solve(char* str)
    {
        int cur = root;
        int len = strlen(str);
        int index;
        for(int i = 0; i < len; i++)
        {
            if(str[i]>='A'&&str[i]<='Z')
            {
                index = str[i] - 'A';
            }
            else if(str[i]>='a'&&str[i]<='z')
            {
                index = str[i] - 'a';
            }
            else
                continue;
            cur = nex[cur][index];
            int tp = cur;

            while(tp != root)
            {
                if(ed[tp]){
                    ans[i+1] -= 1;
                    ans[i - dis[tp]+1] += 1;
                    break;
                }
                tp = fail[tp];
            }
        }
    }
};

Tire ac;

int main()
{
    int t;
    int n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        ac.ini();
        for(int i=0; i<n; i++)
        {
            scanf("%s", s);
            ac.inser(s);
        }
        ac.build();
        getchar();
        gets(s);
//        puts(s);
        memset(ans, 0, sizeof(ans));
        ac.solve(s);
        int len = strlen(s);
        long long int tans = 0;

        for(int i=0; i<len; i++)
        {
            tans += ans[i];
            if(tans <= 0) printf("%c", s[i]);
            else printf("*");

        }
        printf("\n");
    }
    return 0;
}

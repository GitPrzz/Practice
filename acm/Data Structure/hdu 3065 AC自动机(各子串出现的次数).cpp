/*
hdu 3065 AC自动机(各子串出现的次数)

给你m个子串,然后从一个字符串中查找这些子串哪些出现过,出现了多少次
在用ed对子串进行标记。 查询过程中遇到ed则对在相应的子串上 +1

hhh-2016-04-23 21:08:09
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
typedef long long ll;
typedef unsigned int ul;
const int  maxn = 40010;
const int mod = 10007;
int ans[1005];
int tot;
struct Tire
{
    int nex[1000*55][130],fail[1000*55],ed[1000*55];
    int root,L;
    int newnode()
    {
        for(int i = 0; i < 130; i++)
            nex[L][i] = -1;
        ed[L++] = 0;
        return L-1;
    }

    void ini()
    {
        L = 0,root = newnode();
    }

    void inser(char buf[],int id)
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = buf[i];
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        ed[now] = id;
    }

    void build()
    {
        queue<int >q;
        fail[root] = root;
        for(int i = 0; i < 130; i++)
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
            for(int i = 0; i < 130; i++)
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

    void query(char buf[])
    {
        tot = 0;
        int cur = root;
        int len = strlen(buf);
        for(int i = 0; i < len; i++)
        {
            cur = nex[cur][(int)buf[i]];
            int tp = cur;

            while(tp != root)
            {
                if(ed[tp])
                    ans[ed[tp]]++;
                tp = fail[tp];
            }
        }
    }
};

Tire ac;
char buf[1005][55];
char to[2000100];
int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        ac.ini();
        for(int i = 1; i <= n; i++)
        {
            scanf("%s",buf[i]);
            ac.inser(buf[i],i);
        }
        ac.build();
        memset(ans,0,sizeof(ans));
        scanf("%s",to);
        ac.query(to);

        for(int i = 1; i <= n; i++)
        {
            if(ans[i] > 0)
            {
                printf("%s: %d\n",buf[i],ans[i]);
            }
        }
    }
    return 0;
}

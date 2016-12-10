/*
hdu 2896 病毒侵袭 AC自动机(查找包含哪些子串)

ed表示一个子串的尾节点,用它记录当前子串是第i个
在匹配的过程中，如果遇到一个子串的尾节点，就把它添加入答案中。排序输出即可

hhh-2016-04-23 20:57:12
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
int ans[200];
int tot;
struct Tire
{
    int nex[500*210][130],fail[500*210],ed[500*210];
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
            cur = nex[cur][buf[i]];
            int tp = cur;

            while(tp != root)
            {
                if(ed[tp])
                    ans[tot++] = ed[tp];
                tp = fail[tp];
            }
        }
    }
};

Tire ac;
char buf[10005];
int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {
        ac.ini();
        for(int i = 1; i <= n; i++)
        {
            scanf("%s",buf);
            ac.inser(buf,i);
        }
        ac.build();
        scanf("%d",&n);
        int num = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%s",buf);
            ac.query(buf);
            sort(ans,ans+tot);
            for(int h = 0; h < tot; h++)
            {
                if(h == 0)
                    printf("web %d: ",i),num++;
                printf("%d%c",ans[h],h == tot-1 ? '\n':' ');
            }
        }
        printf("total: %d\n",num);
    }
    return 0;
}

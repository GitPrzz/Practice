/*
hdu 3065 AC�Զ���(���Ӵ����ֵĴ���)

����m���Ӵ�,Ȼ���һ���ַ����в�����Щ�Ӵ���Щ���ֹ�,�����˶��ٴ�
����ed���Ӵ����б�ǡ� ��ѯ����������ed�������Ӧ���Ӵ��� +1

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

/*
ZOJ 3228 Searching the String(AC自动机)

给你几个子串,然后在字符串中查询它们出现的次数.但是0表示可以重复,1表示不可以
重复.

在开始想的是建两个然后分别查询.但是发现完全可以一次查询解决 TAT
abababac
2
0 aba
1 aba

就这一组数据而言.
建成：
                        root
                       /
                    ①a
                     /
                  ②b
                   /
                 ③a

对于可以重复的部分,直接进行查找就行. 因为叶子节点的a的nex[a][b]就是它的父亲
b节点
//可以参考’飘过的小牛‘的总结,主要是fail指针的理解

所以导致 a① -> b② -> a③ -> b② -> a③ 时又走到了叶子节点a.
而且只有到走到一个字符串的终点的时候才可能 +1
于是乎在每次走完一个子串的时候(通过ed判断) 判断一下它最近一次出现的位置
两个的差是否大于子串的长度即可

hhh-2016-04-26 20:19:35
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef unsigned long long ll;
typedef unsigned int ul;
const int mod = 20090717;
const int INF = 0x3f3f3f3f;
const int N = 100005*6;
int pos[100005];
char str[100005];
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
    int nex[N][26],fail[N],ed[N];
    int dep[N];
    int tan[N][2];
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
        L = 0;
        root = newnode();
        dep[root] = 0;
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

    int inser(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = buf[i] - 'a';
            if(nex[now][ta] == -1)
            {
                nex[now][ta] = newnode();
                dep[nex[now][ta]] = i+1;
            }
            now = nex[now][ta];
        }
        ed[now] ++;
        return now;
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
    int last[N];
    void query(char buf[])
    {
        int len = strlen(buf);
        int cur = root;
        memset(tan,0,sizeof(tan));
        memset(last,-1,sizeof(last));
        for(int i = 0;i < len;i++)
        {
            int ta = buf[i]-'a';
            cur = nex[cur][ta];
            int t = cur;
            while(t != root)
            {
                if(ed[t])
                {
                    tan[t][0]++;
                    if(i-last[t] >= dep[t])
                    {
                        last[t] = i;
                        tan[t][1] ++;
                    }
                }
                t = fail[t];
            }
        }
        return ;
    }
};

Tire ac;
char s[10];
int ty[100004];
int main()
{
    int cas = 1;
    int n;
    while(scanf("%s",str) != EOF)
    {
        scanf("%d",&n);
        ac.ini();
        printf("Case %d\n",cas++);
        for(int i = 0; i < n; i++)
        {
            scanf("%d%s",&ty[i],s);
            pos[i] = ac.inser(s);
        }
        ac.build();
        ac.query(str);
//        for(int i = 0;i < n;i++)
//            cout << pos[i] <<" ";
//        cout <<endl;
        for(int i = 0;i < n;i++)
        {
            printf("%d\n",ac.tan[pos[i]][ty[i]]);
        }
        printf("\n");
    }
    return 0;
}

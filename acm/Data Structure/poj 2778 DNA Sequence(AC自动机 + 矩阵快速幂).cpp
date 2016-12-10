/*
poj 2778 DNA Sequence(AC自动机 + 矩阵快速幂)

已知一个长度为n的字符串Str由A,T,G,C组成,给你m个子串.  求不包含这些子串的Str有多少种

AC自动机建立可以构建一个关系图。然后将这个关系图转换到矩阵上面,然后利用矩阵快速幂便能
求出从a到b的方案数。

大致就是 子串中没有出现的字符都会被指向root节点。即不停地在图中查找子串，于是我们只要在
路径上不经过ed标记的危险节点即可(每个子串的最后一个节点)。

对于agc、c而言，如果我zou过 a-g-c-d 这个路径。
                          root
                         /    \
                        a      c
                       /
                      g
                     /
                    c
                   /
                  d
由上面这个图可知 左边的d 和 右边的c都是危险节点。  但漏掉了左边上的c
所以如果fail指针指向那个节点是危险节点的话,那么当前节点也是危险节点

AC自动机：http://blog.csdn.net/niushuai666/article/details/7002823
hhh-2016-04-23 15:59:53
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int  maxn = 40010;
const int mod = 100000;
struct Matrix
{
    int len;
    int ma[105][105];
    Matrix() {}
    Matrix(int L)
    {
        len = L;
    }
};

Matrix mult(Matrix ta,Matrix tb)
{
    Matrix tc;
    tc.len = ta.len;
    for(int i = 0; i < ta.len; i++)
    {
        for(int j = 0; j < ta.len; j++)
        {
            tc.ma[i][j] = 0;
            for(int k = 0; k < ta.len; k++){
                tc.ma[i][j] = tc.ma[i][j]+(ll)ta.ma[i][k]*tb.ma[k][j]%mod;
                tc.ma[i][j] %= mod;
            }
        }
    }
    return tc;
}

Matrix pow_mat(Matrix a,ll n)
{
    Matrix cnt;
    cnt.len = a.len;
    memset(cnt.ma,0,sizeof(cnt.ma));
    for(int i = 0 ; i < cnt.len; i++)
        cnt.ma[i][i] = 1;

    while(n)
    {
        if(n&1) cnt = mult(cnt,a);
        a = mult(a,a);
        n >>= 1;
    }
    return cnt;
}

struct Tire
{
    int nex[105][4],fail[105],ed[105];
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

    int cha(char x)
    {
        if(x == 'A')
            return 0;
        else if(x == 'C')
            return 1;
        else if(x == 'T')
            return 2;
        else if(x == 'G')
            return 3;
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
            if(ed[fail[now]])
                ed[now] = 1;
            q.pop();
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

    Matrix to_mat()
    {
        Matrix ta(L);
        memset(ta.ma,0,sizeof(ta.ma));
        for(int i = 0; i < L; i++)
        {
            for(int j = 0; j < 4; j++)
                if(!ed[nex[i][j]])
                    ta.ma[i][nex[i][j]]++;
        }
        return ta;
    }
};
Tire ac;
char buf[20];
int main()
{
    int m;
    ll n;
    while(scanf("%d%I64d",&m,&n) != EOF)
    {
        ac.ini();
        for(int i = 0; i < m; i++)
        {
            scanf("%s",buf);
            ac.inser(buf);
        }
        ac.build();
        Matrix ta = ac.to_mat();
        int ans = 0;
        ta = pow_mat(ta,n);
        for(int i = 0;i < ta.len;i++)
        {
            ans = (ans+ta.ma[0][i])%mod;
        }
        printf("%d\n",ans);
    }
    return 0;
}

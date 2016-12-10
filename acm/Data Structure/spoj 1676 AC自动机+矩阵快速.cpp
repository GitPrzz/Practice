/*
spoj 1676 AC自动机+矩阵快速

给你m个串,求包含任意个数这些串的长度为n的字符串的种类
通过AC自动+矩阵可以快速求出不包含这些串的种类数。  再用快速幂求出总的可能数然后减去
这些即可

hhh-2016-04-23 20:20:22
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
typedef unsigned int ul;
const int  maxn = 40010;
const int mod = 10007;
struct Matrix
{
    int len;
    ul ma[70][70];
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
                tc.ma[i][j] = tc.ma[i][j]+ta.ma[i][k]*tb.ma[k][j];
            }
            tc.ma[i][j] %= mod;
        }
    }
    return tc;
}

Matrix pow_mat(Matrix a,int n)
{
    Matrix cnt = a;
    n--;
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
    int nex[70][30],fail[70],ed[70];
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

    void inser(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            int ta = buf[i]-'A';
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
            if(ed[fail[now]])
                ed[now] = 1;
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

    Matrix to_mat()
    {
        Matrix mat(L);
        memset(mat.ma,0,sizeof(mat.ma));

        for(int i = 0;i < L;i++)
        {
            for(int j = 0;j < 26;j++)
            {
                if(!ed[nex[i][j]])
                    mat.ma[i][nex[i][j]]++;
            }
        }
        return mat;
    }
};

int pow_mod(int a,int n)
{
    a%=mod;
    int cnt = 1;
    while(n)
    {
        if(n&1) cnt =cnt*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return cnt;
}

Tire ac;
char buf[20];
int main()
{
    int m;
    int n;
    while(scanf("%d%d",&m,&n) != EOF)
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
            ans = ans+(int)ta.ma[0][i];
        }
        ans = pow_mod(26,n)-ans;
        while(ans < 0)
            ans += mod;
        printf("%d\n",ans%mod);
    }
    return 0;
}

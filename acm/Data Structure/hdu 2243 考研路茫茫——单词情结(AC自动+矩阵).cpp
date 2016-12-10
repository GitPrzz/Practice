/*
hdu 2243 考研路茫茫——单词情结(AC自动+矩阵)

给你m个子串,求包含至少一个子串的长度不大于n的字符串的种类数
所有可能： 26+26^2 + .... + 26^n
而且前面也求过一个子串都不包含的情况。即把他们的关系转换成矩阵mat
一个都不包含的情况： mat + mat^2 +..... + mat^n
对于求 次方和.  mat+... mat^6 = mat+mat^2+mat^3 + mat^3*(mat+mat^2+mat^3)
于是求出两个的值然后减去即可

// 矩阵求a走m步到b的方案数 + A + A^2 + A^3 + ... + A^k的结果(两个矩阵的经典应用)
hhh-2016-04-23 22:33:39
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
const int  maxn = 40010;
int tot;

struct Matrix
{
    int len;
    ll ma[50][50];
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
                tc.ma[i][j] = tc.ma[i][j]+(ll)ta.ma[i][k]*tb.ma[k][j];
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

Matrix Add(Matrix ta,Matrix tb)
{
    Matrix tc;
    tc.len = ta.len;
    for(int i = 0;i < tc.len;i++)
    {
        for(int j = 0;j < tc.len;j++)
        {
            tc.ma[i][j] = (ta.ma[i][j]+tb.ma[i][j]);
        }
    }
    return tc;
}

struct Tire
{
    int nex[50][26],fail[50],ed[50];
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
            int ta = buf[i]-'a';
            if(nex[now][ta] == -1)
                nex[now][ta] = newnode();
            now = nex[now][ta];
        }
        ed[now]  ++;
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
                ed[now] = 1;
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
                    mat.ma[i][nex[i][j]] ++;
            }
        }
        return mat;
    }
};



Matrix mat;

Matrix cal(int n)
{
    if(n == 1)
        return mat;
    Matrix tp = cal(n/2);
    if(n & 1)
    {
        Matrix t = pow_mat(mat,n/2+1);
        tp = Add(tp,mult(t,tp));
        tp = Add(tp,t);
    }
    else
    {
        Matrix t = pow_mat(mat,n/2);
        tp = Add(tp,mult(t,tp));
    }
    return tp;
}

ll pow_mod(ll a,int n)
{
    ll cnt = 1;
    while(n)
    {
        if(n&1) cnt = cnt*a;
        a = a*a;
        n >>= 1;
    }
    return cnt;
}

ll ca(int n)
{
    if(n == 1)
        return 26;
    ll tp = ca(n/2);
    if(n & 1)
    {
        ll t = pow_mod(26,n/2+1);
        tp = tp+t+tp*t;
    }
    else
    {
       ll t = pow_mod(26,n/2);
       tp = tp+t*tp;
    }
    return tp;
}

Tire ac;
char buf[20];
int main()
{
    int n,m;
    while(scanf("%d%d",&m,&n) != EOF)
    {
        ac.ini();
        for(int i = 1; i <= m; i++)
        {
            scanf("%s",buf);
            ac.inser(buf);
        }
        ac.build();
        mat = ac.to_mat();
        Matrix ans = cal(n);
        ll tans = ca(n);
        ll t = 0;
        for(int i = 0;i < ans.len;i++)
        {
            t += ans.ma[0][i];
        }
        printf("%I64u\n",tans-t);
    }
    return 0;
}

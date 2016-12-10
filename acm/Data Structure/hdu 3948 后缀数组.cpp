/*
hdu 3948 后缀数组

problem：
给你一个字符串，问其中不同回文子串的个数

solve：
通过长度的奇偶性能够找出所有的回文子串(类似求最长回文子串),但是其中有很多重复的一直不知道怎么处理
有的较短的回文子串包含在一个长的里面，有的是两个回文有重复的部分。
最开始尝试的是通过枚举字符串所有的位置，类似于manacher求出所有位置的回文长度.但是发现完全没法解决重复的问题

参考别人的方法：
首先height数组可以知道两个回文子串的关系，所以枚举height.
通过ta记录当前位置与上一个回文串的公共前缀，当遇到下个回文串就能知道两个回文串的公共部分.即需要减去的重复部分
ta = min(ta,height[i]);
而且枚举height不知道当前回文串是否处理过，所以用vis记录一下

hhh-2016-08-11 13:51:03
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
const int INF = 0x3f3f3f3f;
const int  maxn = 200000+10;
const int mod = 1e9+7;

int t1[maxn],t2[maxn],c[maxn];
bool cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b] &&r[l+a] == r[l+b];
}

void get_sa(int str[],int sa[],int Rank[],int height[],int n,int m)
{
    n++;
    int p,*x=t1,*y=t2;
    for(int i = 0; i < m; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[x[i] = str[i]]++;
    for(int i = 1; i < m; i++) c[i] += c[i-1];
    for(int i = n-1; i>=0; i--) sa[--c[x[i]]] = i;
    for(int j = 1; j <= n; j <<= 1)
    {
        p = 0;
        for(int i = n-j; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i]-j;
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) c[x[y[i]]]++ ;
        for(int i = 1; i < m; i++) c[i] += c[i-1];
        for(int i = n-1; i >= 0; i--)  sa[--c[x[y[i]]]] = y[i];

        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],j)? p-1:p++;
        if(p >= n) break;
        m = p;
    }
    int k = 0;
    n--;
    for(int i = 0; i <= n; i++)
        Rank[sa[i]] = i;
    for(int i = 0; i < n; i++)
    {
        if(k) k--;
        int j = sa[Rank[i]-1];
        while(str[i+k] == str[j+k]) k++;
        height[Rank[i]] = k;
    }

}

int mm[maxn];
int dp[20][maxn];

int Rank[maxn],height[maxn];
int sa[maxn];
char str[maxn];
int r[maxn];

void ini_RMQ(int n)
{
    mm[0] = -1;
    for(int i = 1; i <= n; i++)
        mm[i] = (((i & (i-1)) == 0) ? mm[i-1]+1:mm[i-1]);

    for(int i =1; i <= n; i++)
        dp[0][i] = height[i];
    for(int i = 1; i <= mm[n]; i++)
    {
        for(int j = 1; j+(1<<i)-1 <= n; j++)
        {
            int a = dp[i-1][j];
            int b = dp[i-1][j+(1<<(i-1))];
            dp[i][j] = min(a,b);
        }
    }
}

int askRMQ(int a,int b)
{
    int t = mm[b-a+1];
    b -= (1<<t)-1;
    return min(dp[t][a],dp[t][b]);
}


int fin(int a,int b)
{
    a = Rank[a],b = Rank[b];
    if(a > b) swap(a,b);
    return askRMQ(a+1,b);
}
int vis[maxn];

int main()
{
    int T;
    int cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str);
        int len = strlen(str);
        for(int i= 0; i < len; i++)
            r[i] = str[i];
        r[len] = 1;
        for(int i = 0; i < len; i++)
            r[len+1+i] = str[len-1-i];
        r[2*len+1] = 0;
        get_sa(r,sa,Rank,height,len*2+1,128);
        ini_RMQ(2*len+1);
        int ans = 0;
        int n = len+len+1;
        int ta=0;
        memset(vis,0,sizeof(vis));
        for(int i = 2; i <= n; i++)
        {
            ta = min(height[i],ta);
            if(!sa[i])
                continue;
            if(vis[n-sa[i]])
            {
                int t = fin(sa[i],n-sa[i]);
                if(t > ta)
                {
                    ans += t-ta;
                    ta = t;
                }
            }
            else
                vis[sa[i]] = 1;
        }
        ta= 0 ;
        memset(vis,0,sizeof(vis));
        for(int i = 2; i <= n; i++)
        {
            ta= min(ta,height[i]);
            if(vis[n-sa[i]-1])
            {
                int t = fin(sa[i],n-sa[i]-1);
                if(t > ta)
                {
                    ans += t-ta;
                    ta = t;
                }
            }
            else
                vis[sa[i]] = 1;
        }
        printf("Case #%d: ",cas++);
        printf("%d\n",ans);
    }
}

/*
hdu 3518 后缀数组

problem:
给你一个字符串，问它有多少种出现两次且不重叠的子串

solve:
因为总长度为1000，所以考虑通过枚举子串的长度来计算每种长度有多少种子串。
但是感觉不知道怎么区分相同长度的不同串 T_T
后来发现最开始思路有问题，对height分组讨论的时候。每一组height在同一长度下只可能有一种子串
所以通过 枚举+判断 就能得出结果

hhh-2016-08-12 10:29:23
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
#include <set>
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

int Rank[maxn],height[maxn];
int sa[maxn];
char str[maxn];
int r[maxn];

int cal(int len,int n)
{
    int cnt = 0;
    int minx = 100000,maxx = 0;
    for(int i = 2;i <= n;i++)
    {
        if(height[i] >= len)
        {
            minx = min(minx,sa[i]),minx = min(minx,sa[i-1]);
            maxx = max(maxx,sa[i]),maxx = max(maxx,sa[i-1]);
//            cout << "max:" <<maxx << " " <<"min:" << minx <<endl;
        }
        else
        {
            if(maxx - minx >= len)
                cnt ++;
              minx = 100000;maxx = 0;
        }
    }
     if(maxx - minx >= len)
                cnt ++;
   // cout << len << " " <<cnt <<endl;
    return cnt;
}

int main()
{
    while(scanf("%s",str) != EOF && str[0] != '#')
    {
        int len = strlen(str);
        for(int i = 0;i < len;i++)
            r[i] = str[i] - 'a'+1;
        r[len] = 0;
        get_sa(r,sa,Rank,height,len,128);

        int ans = 0;
        for(int i = 1;i <= len/2+1;i++)
            ans += cal(i,len);
        printf("%d\n",ans);
    }
}

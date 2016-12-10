/*
SPOJ - DISUBSTR 多少个不同的子串

求一个串中有多少个不同的子串

每个子串一定是某个后缀的前缀，那么原问题等价于求所有后缀之间的不相
同的前缀的个数。
height表示的公共前缀的长度 = 相同串的个数
所以  总数-sum(height[])即可
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 1005;

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
int a[maxn];
int n;

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int tot = 0;
        scanf("%s",str);
        int len = strlen(str);
        for(int i = 0;i < len; i++)
            a[i] = str[i];
        a[len] = 0;
        get_sa(a,sa,Rank,height,len,200);

        int ans = len*(len+1)/2;
        for(int i = 2; i <= len; i++)
        {
            //printf("%d ",height[i]);
            ans -= height[i];
        }
        cout << ans <<endl;
    }
    return 0;
}

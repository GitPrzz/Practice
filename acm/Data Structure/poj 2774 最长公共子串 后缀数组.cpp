/*
poj 2774 最长公共子串 后缀数组

相当于求两个字符串所有后缀的最长公共前缀
所以我们可以把两个字符串用一个特殊字符间隔连起来
然后找出最大的height,同时通过sa数组判断一下它们是否
是同一个串中的即可

hhh-2016-03-15 20:04:24
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <functional>
#include <algorithm>
typedef long long ll;
using namespace std;

const int N = 100010;
const int maxn = 2*N;

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
int Rank[maxn],height[maxn];
int sa[maxn],str[maxn];
char s1[N];
char s2[N];
int len1,len2;

bool judge(int i,int j)
{
    if(i > j)swap(i,j);
    if(i < len1 && j > len1)
        return 1;
    return 0;
}

int main()
{
    while(scanf("%s",s1) != EOF)
    {
        scanf("%s",s2);
        int tot = 0;
        len1 = strlen(s1),len2 = strlen(s2);
        for(int i = 0;s1[i]!='\0';i++)
            str[tot++] = s1[i];
        str[tot++] = 1;
        for(int i = 0;s2[i]!='\0';i++)
            str[tot++] = s2[i];
        str[tot] = 0;
        get_sa(str,sa,Rank,height,tot,300);

        int ans = 0;

        for(int i =2;i <= tot;i++)
        {
            if(judge(sa[i-1],sa[i]))
                ans = max(ans,height[i]);
        }
        cout << ans << endl;
    }
    return 0;
}

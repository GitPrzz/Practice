/*
POJ 3261 可重叠的k次最长重复子串

给你一串数字，求其中出现k次的最长子串

最开始想的是二分最长长度，然后判断一下是否有k个子串
但是在判断的时候2b了，并没有判断它们是否是同一个子串，于是乎
应该进行分组讨论，因为是height中存的是排过序后的最长前缀
假设height[] = 0 0 1 4 4 4 3 2 4 4
只有前3个4是同一个子串(排序后一段连续子串是相似的)

所以成了找出height连续大于等于mid的长度sum，判断sum+1是否>=k

hhh-2016-03-11 21:29:00
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
const int maxn = 100050;

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
int sa[maxn],str[maxn];
int a[maxn];
int n;

bool judge(int ans,int k)
{
    int i =2;
    while(1)
    {
        while(height[i] < ans && i <= n) i++;
        int num = 0;
        if(i > n) break;
        while(height[i] >= ans && i <= n){num++;i++;}
        if(num+1 >= k)return 1;
    }
    return 0;
}
map<int,int> mp;
int main()
{
    int k,cas = 1;
    while(scanf("%d%d",&n,&k) != EOF)
    {
        int tot = 1,x;
        mp.clear();
        for(int i  = 0; i < n; i++)
        {
            scanf("%d",&x);
            if(!mp[x])
                mp[x] = tot++;
            a[i] = mp[x];
        }
        a[n] = 0;

        get_sa(a,sa,Rank,height,n,n+1);
        int ans = 0;
        int l=1,r=n;
//        for(int i =2;i <= n;i++)
//            printf("%d %d\n",sa[i],height[i]);
//        cout <<endl;
        while(l <= r)
        {
            int mid = (l+r)>>1;
            if(judge(mid,k))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}

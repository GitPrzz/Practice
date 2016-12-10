/*
POJ 1743  后缀数组

给你一串数字，求它们最长的重复(公差相同)子序列，且两个子序列不想交

表示第一次用后缀数组
我们可以得到
sa[i]:表示排名第i个的首字母位置
Rank[i]:第i个数的排名
Height[i]:sa[i]和sa[i-1]的最长公共前缀


于是我们先求出相邻两个数之间的差，然后二分来枚举长度
如果在当前长度下能找到两个并且相距合适的就记录下来
因为最后得到的是间距的个数  所以ans+1

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
const int maxn = 20050;

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
int a[maxn];

bool judge(int len,int n)
{
    for(int i = 2; i <= n; i++)
    {
        if(height[i] < len)
            continue;
        for(int j = i-1; j >= 2; j--)
        {
            if(abs(sa[i] - sa[j]) >= len)
                return true;
            if(height[j] < len)
                break;
        }
    }
    return false;
}

int main()
{
    int n;
    while(scanf("%d",&n) != EOF)
    {

        if(!n)
            break;
        for(int i = 0; i < n; i++)  scanf("%d",&a[i]);
        for(int i = 0; i < n; i++)
            a[i] = a[i+1]-a[i]+90;
        a[n-1] = 0;
        if(n < 10)
        {
            printf("0\n");
            continue;
        }
        get_sa(a,sa,Rank,height,n-1,200);

        int l = 0,r = n;
        int ans ;
        while(l <= r)
        {
            int mid = (l+r) >>1;
            if(judge(mid,n))
            {
                ans = mid;
                l = mid+1;
            }
            else
                r = mid-1;
        }
        if(ans < 4)
            printf("0\n");
        else
            printf("%d\n",ans+1);
    }
    return 0;
}

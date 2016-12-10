/*
hdu  5558  后缀数组

从[1,n]对于每个i，求suff[j](j < i)与suff[i]的最长公共前缀，
如果有多个，取最小的那个

我们可以通过后缀数组先求出，如果i-1和i，i和i+1都有公共前缀，
那么i-1和i+1也有公共前缀，所以可以先处理出每个i的左右界限。然后对于i左右扫描一下即可

然后枚举i，从pre[i]-nex[i]找到合适的结果即可

hhh-2016-03-10 18:17:04
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
const int maxn = 150050;

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

int pre[maxn],nex[maxn];
int Rank[maxn],height[maxn];
int sa[maxn],str[maxn];
char a[maxn];
int len;

int main()
{
    int T,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a);
        int len = 0;
        for(int i =0;a[i] != '\0'; i++)
        {
            str[len++] = a[i]-'a'+1;
        }
        str[len] = 0;
        get_sa(str,sa,Rank,height,len,30);

        for(int i = 1; i <= len; i++)
        {
            if(height[i] == 0)
                pre[i] = i;
            else
                pre[i] = pre[i-1];
        }

        for(int i = len; i >= 1; i--)
        {
            if(height[i+1] == 0 || i == len) nex[i] = i;
            else nex[i] = nex[i+1];
        }

        int i = 0;
         printf("Case #%d:\n",cas++);
        while(i < len)
        {
            int now = Rank[i];   //i的排名
            int k = 0,t = i;
            int mi = height[now];
            for(int j = now-1; j >= pre[now]; j--)
            {
                mi = min(mi,height[j+1]);
                if(mi < k)
                    break;
                if(sa[j] < i)
                {
                    if(mi > k || (mi==k && sa[j] < t))
                    {
                        k = mi;
                        t = sa[j];
                    }
                }
            }
            if(now+1 <= nex[now]) mi = height[now+1];
            for(int j = now+1; j <= nex[now]; j++)
            {
                mi = min(mi,height[j]);
                if(mi < k)
                    break;
                if(sa[j] < i)
                {
                    if(mi > k || (mi==k && sa[j] < t))
                    {
                        t = sa[j];
                        k = mi;
                    }
                }
            }

            if(k == 0) printf("-1 %d\n",a[i]);
            else printf("%d %d\n",k,t);
            if(k) i+=k;
            else i++;
        }
    }
    return 0;
}

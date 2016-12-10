/*
POJ 3415 不小于k的公共子串的个数(思路)

给你两个子串求长度不小于k的公共子串的个数

因为每次枚举一个子串就要和前面所有另一个串的所有已经出现情况取一个最小值
如果每次都把所有的扫描一遍的话很浪费时间,而且是与前面的所有取min,所有用栈保存的话
栈顶的肯定是最大值,所以栈内元素就成单调增的了。  每次只需要更新比当前值大的情况就好了

从头到尾枚举height,如果当前是属于A串,则加上前面所有属于B串的height-k+1.对于B串同理.
两个串之间的公共前缀是它们之间所有的最小值,所以用栈维护一下，保证栈里是单调递增的，
这样对于新增的串只需要处理其中height大于它的一部分即可

hhh-2016-03-15 23:25:42
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
const int maxn = 200050;

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

int Rank[maxn];
int sa[maxn];
int str[maxn],mark[4],height[maxn];
char s1[maxn],s2[maxn];
ll num[4],ans[maxn];

ll solve(int len,int n,int k)
{
    int top = 0;
    ll sum = 0;
    num[1] = num[2] = 0;
    for(int i = 1; i <= n; i++)
    {
        if(height[i] < k)
            top = num[1] = num[2] = 0;
        else
        {
            for(int j = top; ans[j] > height[i]+1-k && j; j--)
            {
                num[mark[j]] += (height[i]-k+1-ans[j]);
                ans[j] = height[i]-k+1;
            }
            ans[++top] = height[i]-k+1;
            if(sa[i-1]<len) mark[top] = 1;
            if(sa[i-1]>len) mark[top] = 2;
            num[mark[top]] += height[i]-k+1;
            if(sa[i] < len) sum += num[2];
            if(sa[i] > len) sum += num[1];
        }
    }
    return sum;
}

int main()
{
    int k;
    while(scanf("%d",&k) != EOF && k)
    {
        scanf("%s",s1);
        scanf("%s",s2);
        int tot = 0;
        int len1 = strlen(s1);
        for(int i = 0; s1[i]!='\0'; i++)
            str[tot++] = s1[i];
        str[tot++] = 1;
        for(int i = 0; s2[i]!='\0'; i++)
            str[tot++] = s2[i];
        str[tot] = 0;
        get_sa(str,sa,Rank,height,tot,200);
//        for(int i = 2;i <= tot;i++)
//            printf("%d ",height[i]);
//        printf("\n");
        cout << solve(len1,tot,k) <<endl;
    }
    return 0;
}

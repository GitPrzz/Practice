/*
SPOJ PHRASES 每个字符串至少出现两次且不重叠的最长子串

因为是求的最长子串，所以考虑二分长度len
然后我们需要对其进行判断，对于每一个连续大于等于len的height[](分组讨论)
记录各个串中的情况，因为要判断不是重叠的，所以对于每个串，我们记录
它满足height>=len的最大最小位置
如果所有串的max-min >= len 则说明存在长度为len的子串在
每个串都有出现两次且不重叠

感觉思路没什么问题，主要是最开始代码写得不够简洁，而且WR

hhh-2016-03-21 23:01:01
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
const int maxn = 101000;

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
int str[maxn],height[maxn];
char s[maxn];
int id[maxn];
struct node
{
    int Min;
    int Max;
    int flag;
} anspos[15];


void ini()
{
    for(int i = 0; i <= 12; i++)
        anspos[i].Min = 0x3f3f3f3f,anspos[i].Max = -1;
}

bool can(int len,int n,int num)
{
    int l = 2,r = 2;
    ini();
    for(int i = 2; i <= n; i++)
    {
        if(height[i] >= len)
        {
            int id1=id[sa[i-1]];
            int id2=id[sa[i]];

            anspos[id1].Max=max(anspos[id1].Max,sa[i-1]);
            anspos[id1].Min=min(anspos[id1].Min,sa[i-1]);

            anspos[id2].Max=max(anspos[id2].Max,sa[i]);
            anspos[id2].Min=min(anspos[id2].Min,sa[i]);
            int t;
            for(t = 0; t < num; t++)
                if(anspos[t].Max - anspos[t].Min < len)
                    break;
            if(t == num)
                return 1;
        }
        else
        {
            for(int j = 0; j <= 10; j++)
                anspos[j].Min = 0x3f3f3f3f,anspos[j].Max = -1;
        }
    }
    for(int i = 0; i < num; i++)
        if(!anspos[i].flag)
            return 0;
    return 1;
}

int main()
{
    int k,n,t;
    scanf("%d",&t);
    while(t--)
    {
        ini();
        int tot = 0,len = 0x3f3f3f3f;
        scanf("%d",&n);
        for(int i = 0; i < n; i++)
        {
            scanf("%s",s);
            for(int j = 0; s[j]!='\0'; j++)
            {
                id[tot] = i;
                str[tot++] = s[j]-'a'+10;
            }
            id[tot] = i;
            str[tot++] = i;
            len = min(len,(int)strlen(s));
        }
        str[tot] = 0;
        get_sa(str,sa,Rank,height,tot,100);
        int l = 0,r = len;
        int ans = 0;
        while(l <= r)
        {
            int mid = (l+r)>>1;
            if(can(mid,tot,n))
            {
                ans = mid;
                l = mid+1;
            }
            else
                r = mid-1;
        }
        printf("%d\n",ans);
    }
    return 0;
}

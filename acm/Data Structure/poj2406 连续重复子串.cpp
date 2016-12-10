/*
poj2406 连续重复子串

给你一个字符串，请问最多能由任意字符串重复多少次得到

最开始用的是DA算法
想的是枚举长度然后进行一下判断即可,只需要判断Rank[0]和Rank[k]是否为n-k
(因为如果相等，0~k = k+1~2*k+1 .... 递推下去 整个串是0~k的子串不断
 重复得到)
但是MLE.估计是处理RMQ时有问题,而且看了别人报告才发现这并不是最优方法。
因为我们求的是所有数到Rank[0],所以直接从rank[0]的位置往两边扫一遍就行了
但是DA算法nlog(n)好像会TLE- -
于是乎重新去搞了DC3的算法，才搞定 2600ms

而且感觉kmp更适合这个(看比人代码很短的样子)

hhh-2016-03-13 18:11:02
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 2000001;

#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wsf[maxn],wa[maxn],wb[maxn],wv[maxn],sa[maxn],Rank[maxn],
height[maxn],f[maxn];
int str[maxn];

int c0(int *r,int a,int b)
{
    return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];
}
int c12(int k,int *r,int a,int b)
{
    if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
    else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];
}
void sort(int *r,int *a,int *b,int n,int m)
{
    int i;
    for(i=0; i<n; i++) wv[i]=r[a[i]];
    for(i=0; i<m; i++) wsf[i]=0;
    for(i=0; i<n; i++) wsf[wv[i]]++;
    for(i=1; i<m; i++) wsf[i]+=wsf[i-1];
    for(i=n-1; i>=0; i--) b[--wsf[wv[i]]]=a[i];
    return;
}
void dc3(int *r,int *sa,int n,int m)
{
    int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
    r[n]=r[n+1]=0;
    for(i=0; i<n; i++) if(i%3!=0) wa[tbc++]=i;
    sort(r+2,wa,wb,tbc,m);
    sort(r+1,wb,wa,tbc,m);
    sort(r,wa,wb,tbc,m);
    for(p=1,rn[F(wb[0])]=0,i=1; i<tbc; i++)
        rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
    if(p<tbc) dc3(rn,san,tbc,p);
    else for(i=0; i<tbc; i++) san[rn[i]]=i;
    for(i=0; i<tbc; i++) if(san[i]<tb) wb[ta++]=san[i]*3;
    if(n%3==1) wb[ta++]=n-1;
    sort(r,wb,wa,ta,m);
    for(i=0; i<tbc; i++) wv[wb[i]=G(san[i])]=i;
    for(i=0,j=0,p=0; i<ta && j<tbc; p++)
        sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
    for(; i<ta; p++) sa[p]=wa[i++];
    for(; j<tbc; p++) sa[p]=wb[j++];
    return;
}
void getheight(int *r,int n)//n不保存最后的0
{
    int i,j,k=0;
    for(i=1; i<=n; i++)  Rank[sa[i]]=i;
    for(i=0; i<n; i++)
    {
        if(k)
            k--;
        else
            k=0;
        j=sa[Rank[i]-1];
        while(r[i+k]==r[j+k])
            k++;
        height[Rank[i]]=k;
    }
}
int rm[maxn];
char ts[maxn];

void iniRMQ(int len)
{
    int to = Rank[0];
    rm[to] = maxn;
    for(int i = to - 1;i >= 0;i--)
    {
        if(height[i+1] < rm[i+1]) rm[i] = height[i+1];
        else rm[i] = rm[i+1];
    }

    for(int i = to+1;i <= len;i++)
    {
        if(height[i] < rm[i-1]) rm[i] = height[i];
        else rm[i] = rm[i-1];
    }
}

int solve(int len)
{
    for(int i = 1;i <= len/2;i++)
    {
        if(len % i) continue;
        if(rm[Rank[i]] == len-i) return len/i;
    }
    return 1;
}

int main()
{
    while(scanf("%s",ts) != EOF)
    {
        if(ts[0] == '.')
            break;
        int len = strlen(ts);
        for(int i = 0; i < len; i++)
            str[i] = ts[i];
        str[len] = 0;

        dc3(str,sa,len+1,300);
        getheight(str,len);
        iniRMQ(len);
        printf("%d\n",solve(len));
    }
    return 0;
}

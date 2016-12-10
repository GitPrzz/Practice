/*
poj 3693 ��׺���� �ظ��������������ظ��Ӵ�

����һ���ַ������������ظ����������ַ���,��
ccabababc  -> ababab = 3   ababa = 1

��ʾ���������˼·��û��������Ҫ���ǲο�����д�õĴ����
���ȣ�ö��l(�����ظ��ĳ���),�ж�suff[i],suff[i+l]
�������ǰ׺k%l != 0,��˵��������Ȳ�����,�޸ĺ��ٽ����жϡ�
���ǿ���k%i,���Կ��ɺ������k%l���ַ�,�����Կ���ǰ������m = l-k%l
���ַ������ǳ����� l-i-m,l-m�����������֮ǰ�Ľ��ȡ�ϴ�ֵ����
Ȼ���¼������cnt�ͷ������������н�a[]

�������жϣ���ΪҪ���ֵ�����С�����Դ�sa[1]��ʼ�жϣ����
su[sa[i]]��su[sa[i]+a[j]]�Ĺ���ǰ׺���ڵ���(cnt-1)*a[j]
��˵������

hhh-2016-03-13 21:37:55
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
const int maxn = 100100;

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
int sa[maxn],str[maxn];
char ts[maxn];

void ini_RMQ(int n)
{
    mm[0] = -1;
    for(int i = 1;i <= n;i++)
        mm[i] = (((i & (i-1)) == 0) ? mm[i-1]+1:mm[i-1]);

    for(int i =1;i <= n;i++)
        dp[0][i] = height[i];
    for(int i = 1;i <= mm[n];i++)
    {
        for(int j = 1;j+(1<<i)-1 <= n;j++)
        {
            int a = dp[i-1][j];
            int b = dp[i-1][j+(1<<(i-1))];
            dp[i][j] = min(a,b);
        }
    }
}

int askRMQ(int a,int b)
{
    if(a > b) swap(a,b);
    a++;
    int t = mm[b-a+1];
    b -= (1<<t)-1;
    return min(dp[t][a],dp[t][b]);
}
int a[maxn];
int main()
{
    int cas = 1;
    while(scanf("%s",ts) != EOF)
    {
        if(ts[0] == '#')
            break;
        int len = strlen(ts);
        for(int i = 0; i < len; i++)
            str[i] = ts[i];
        str[len] = 0;
        printf("Case %d: ",cas++);
        get_sa(str,sa,Rank,height,len,150);
        ini_RMQ(len);
        int cnt = 0,tot = 0;
        for(int i = 1;i <= len;i++)
        {
            for(int j = i;j < len;j+=i)
            {
                int tk = askRMQ(Rank[j-i],Rank[j]);
                int m = i - tk%i;

                if(j > i && tk%i) tk = max(tk,askRMQ(Rank[j-i-m],Rank[j-m]));
                if(tk % i) tk = 0;
                if(tk) tk = tk/i+1;
                if(tk > cnt)
                    cnt = tk,tot=0,a[tot++]=i;
                else if(tk == cnt && a[tot-1] != i)
                    a[tot++] = i;
            }
        }
       // cout <<cnt <<endl;
        int flag = 0;
        for(int i = 1;i < len && !flag;i++)
        {
            for(int j = 0;j < tot && !flag;j++)
            {
                if(askRMQ(Rank[sa[i]],Rank[sa[i]+a[j]])>=a[j]*(cnt-1))
                {
                    ts[sa[i]+a[j]*cnt] = '\0';
                    printf("%s\n",ts+sa[i]);
                    flag = 1;
                }
            }
        }
    }
    return 0;
}

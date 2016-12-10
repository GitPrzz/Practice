/*
POJ 3294 n����������һ��Ĵ������������Ӵ�

�����������Ӵ������Կ��� ���ִ�len+�ж�
��ΪҪ�ж��Ƿ�Ϊx�����������Զ�height���з���,��height�����и���������len
�ļ��ϣ�Ȼ���ÿ��������ж�,��������ҵ�x+1����ͬ����Դ��
���������ͼ�¼ �Ӵ�����ʼλ�úͳ���

1.��֮��ļ�����Ų�����ͬ
2.��Ϊ��100����,�����Ѿ�ռ����0-99,�����ַ�������Ϣת����int��ʱ��
�����Ǵ�100��ʼ

hhh-2016-03-17 19:04:50
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
char s[1010];
char allstr[maxn];
int anslen,anspos[maxn];
int ansnum,vis[110];
int id[maxn];

bool judge(int len,int k,int n,int l,int r)
{
    int num = 0;
    memset(vis,0,sizeof(vis));
    for(int i = l; i <= r; i++)
    {
        if(height[i] >= len)
        {
            if(!vis[id[sa[i-1]]])
            {
                vis[id[sa[i-1]]] = 1;
                num ++;
            }
            if(!vis[id[sa[i]]])
            {
                vis[id[sa[i]]] = 1;
                num ++;
            }
            if(num > k)
                return 1;
        }
    }
    return 0;
}

bool can(int len,int k,int n)
{
    int l=2,r=2;
    int flag = 0;
    ansnum = 0;
    for(int i = 2; i <= n; i++)
    {
        if(height[i]>=len)
            r++;
        else
        {
            if(judge(len,k,n,l,r))
            {
                anspos[ansnum++] = sa[l];
                flag =1;
            }
            l = i,r = i;
        }
    }
    if(judge(len,k,n,l,r) && l < r)
    {
        anspos[ansnum++] = sa[l];
        flag =1;
    }
    return flag;
}

int main()
{
    int k,n;
    while(scanf("%d",&n) != EOF && n)
    {
        int len=0;
        int tot = 0;
        for(int i = 0; i< n; i++)
        {
            scanf("%s",s);
            for(int j = 0; s[j]!='\0'; j++)
            {
                id[tot] = i;
                allstr[tot] = s[j];
                str[tot++] = s[j]-'a'+100;
            }
            len=max(len,(int)strlen(s));
            id[tot] = i,allstr[tot]='$';
            str[tot++]=i;
        }
        str[tot] = 0;
        get_sa(str,sa,Rank,height,tot,128);
        int k = n/2;
        int ans = 0;
        int l=1,r=len;
        while(l <= r)
        {
            int mid =(l+r)>>1;
            if(can(mid,k,tot))
            {
                l = mid+1;
                anslen = mid;
                ans = ansnum;
            }
            else
                r = mid-1;
        }

        if(!ans)
            printf("?\n");
        else
        {
            //cout<<ans<<endl;
            for(int i = 0; i < ans; i++)
            {
                for(int j = 0; j<anslen; j++)
                    printf("%c",allstr[anspos[i]+j]);
                printf("\n");
            }
        }
        printf("\n");
    }
    return 0;
}

/*
hdu 5008 �����ֵ����kС���Ӵ�

problem:
����һ���ַ�����ÿ��Ѱ���ֵ����kС���Ӵ�(��ͬ��)�Ŀ�ʼ,��β���ꡣ

solve:
���ȿ���֪��height������ǰ��ֵ�����Ū��,����sa[i-1]��sa[i]����ֻҪ��ȥ
���ǵĹ������ּ�height[i],���ǲ�ͬ���Ӵ�.
���Խ�˴������[1,n]�����ֵ����i��ĺ�׺ʱ�ܹ��ж��ٸ���ͬ���Ӵ�.Ȼ��
���ö��ֲ��Ҿ����ҵ�λ��
��Ҫע����ǵ��ж����ʱ�������С��λ��,�����жϵ�ǰ�Ӵ��Ƿ��ǹ���ǰ׺��
һ����.����ö���ҳ���С��λ�ü���
a
aa
aaa
����Ҫ����С�Ĵ�aʱ���ܻ��ҵ� 3 3.��Ϊ��Ҳ��aa,aaa��һ����,������Ҫö��һ��

hhh-2016-08-12 19:24:38
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
typedef unsigned int ul;
const int INF = 0x3f3f3f3f;
const int  maxn = 100000+10;
const int mod = 1e9+7;

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
int r[maxn];
ll num[maxn];
int lpos,rpos;
int len ;


void fin(ll x)
{
    int l =1 ,r = len;
    int cur = 0;
    while(l <= r)
    {
        int mid = (l+r) >> 1;
        if(num[mid] >= x)
        {
            cur = mid;
            r = mid-1;
        }
        else
            l = mid+1;
    }
//    cout << "cur:" <<cur <<endl;
    x = x - num[cur-1];
    lpos = sa[cur]+1;
    rpos = sa[cur]+height[cur]+x;
    int tlen = rpos-lpos+1;
    if(cur+1 <= len && tlen <= height[cur+1])
    {
        for(int i = cur + 1; i <= len; i++)
        {
            if(height[i] >= tlen)
            {
                if(lpos > sa[i]+1)
                {
                    lpos = sa[i]+1;
                    rpos = lpos+tlen-1;
                }
            }
            else
                break;
        }
    }
    return ;
}

int main()
{
    while(scanf("%s",str) != EOF)
    {
        len = strlen(str);
        for(int i = 0; i <len; i ++)
        {
            r[i] = str[i];
        }
        r[len] = 0;
        num[0] = 0;
        get_sa(r,sa,Rank,height,len,200);
        for(int i = 1; i <= len; i++)
        {
            num[i] = (ll)(len - sa[i] - height[i]);
            num[i] += num[i-1];
        }
        int n;
        ll x;
        scanf("%d",&n);
        lpos = 0,rpos = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%I64d",&x);
            ll k = (ll)(lpos^rpos^x)+1LL;
//            cout << "k:" << k <<endl;
            lpos = rpos = 0;
            if(k > num[len])
            {
                printf("0 0\n");
                lpos = 0,rpos = 0;
                continue;
            }
            fin(k);
            printf("%d %d\n",lpos,rpos);
        }
    }
    return 0;
}

/*
HDU 5726 GCD ����GCD=k�ĸ���

problem:
����һ������,Ȼ����m��ѯ��,ÿ��ѯ������[l,r]��gcd�Լ������������ж��ٸ������gcd��֮���

solve:
��һ������ͨ���߶���������rmq�ķ��������.����������ĸ����Ͳ�֪��ôŪ��- -
�ʼ�����ÿ��ѯ�����ֵ֮���� ����+ö���Ҷ˵� ��˼·�������ж��ٸ������
���Ƿ��������ǵݼ���,�о�����ȷ������Ĵ�С,��.

���������ŷ��ֿ���Ԥ����,��һ����˵�l����,[l+1,n]�еĵ�l������gcd�ǵݼ���.
����
GCD[l,j] = 4,GCD[l,j+1] = 4,GCD[l,j+2] = 2
�о�����൱��ö����lΪ������������GCDֵ,Ȼ����ֵ���ǰGCDֵ�����ҵ�,���������ĸ���

��˻��漰�ܶ������GCD��ѯ,���߶����Ļ���ʱ,��RMQʵ��O(1)�Ĳ�ѯAC
����ʱ�临�Ӷ�, ��������QAQ

hhh-2016-08-15 21:35:11
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
int a[maxn];
int m[maxn];
int dp[maxn][20];

ll gcd(ll a,ll b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
void iniRMQ(int n,int c[])
{
    m[0] = -1;
    for(int i = 1; i <= n; i++)
    {
        m[i] = ((i&(i-1)) == 0)? m[i-1]+1:m[i-1];
        dp[i][0] = c[i];
    }
    for(int j = 1; j <= m[n]; j++)
    {
        for(int i = 1; i+(1<<j)-1 <= n; i++)
            dp[i][j] = gcd(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
    }
}

int RMQ(int x,int y)
{
    int k = m[y-x+1];
    return gcd(dp[x][k],dp[y-(1<<k)+1][k]);
}

map<int,ll>mp;

void ini(int n)
{
    mp.clear();
    for(int i = 1;i <= n;i++)
    {
       int now = a[i],j = i;
       while(j <= n)
       {
           int l = j,r = n;
           while(l < r)
           {
               int mid = (l+r+1) >> 1;
               if(RMQ(i,mid) == now)
                l = mid;
               else
                r = mid-1;
           }
           mp[now] += (ll)(l-j+1);
           j = l+1;
           now = RMQ(i,j);
       }
    }
}

int main()
{
    int T,n,m;
    int cas = 1;
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        printf("Case #%d:\n",cas++);
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        iniRMQ(n,a);
        ini(n);
        scanf("%d",&m);
        int a,b;
        for(int i =1; i <= m; i++)
        {
            scanf("%d%d",&a,&b);
            int ans1 = RMQ(a,b);
            printf("%d %I64d\n",ans1,mp[ans1]);
        }
    }
    return 0;
}

/*
51 nod 1610 ·������(Moblus+dp)

problem:
·�������б�Ȩ�����Լ������Ϊһ��·����ֵ������һ�������޻�ͼ��
T���޸Ĳ�����ÿ���޸�һ���ߵı�Ȩ��ÿ���޸ĺ���������޻�ͼ��·����ֵΪ1��·������(��1,000,000,007ȡģ)��

solve:
�о�ֱ����ͼ����GCD�Ļ����鷳,���һ��漰���޸�.
�������ֿ��Կ���ͨ���ݳ�����GCD,�����Ļ���ת������ͼ���泤��Ϊi��·���ĸ���.
��ʼʱ��¼·������w[i]�Լ�����Լ��. (w[i] = 4�Ļ�, ���Կ����� 1,2,4������)

����ͨ��ö��gcd���ܹ��� 100*n*n�����������·��ֵ�����.
���޸ĵ�ʱ��,���Է���ֻ�� Ӱ�챻�Ƴ���������ӵ����Լ����ǵ�Լ��. ����һ��
Ȼ��ͨ��moblusʵ���ݳ�������gcd = 1�����.

hhh-2016/09/09-20:59:44
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1000000007;
const int maxn = 135;
const double PI = acos(-1.0);
const int limit = 33;


template<class T> void read(T&num)
{
    char CH;
    bool F=false;
    for(CH=getchar(); CH<'0'||CH>'9'; F= CH=='-',CH=getchar());
    for(num=0; CH>='0'&&CH<='9'; num=num*10+CH-'0',CH=getchar());
    F && (num=-num);
}
int stk[70], tp;
template<class T> inline void print(T p)
{
    if(!p)
    {
        puts("0");
        return;
    }
    while(p) stk[++ tp] = p%10, p/=10;
    while(tp) putchar(stk[tp--] + '0');
    putchar('\n');
}
int n,m,q,id;
ll dp[maxn],num[maxn];
ll ma[maxn][maxn][maxn];

int tot;
int is_prime[maxn];
ll mu[maxn];
int prime[maxn];

void Moblus()
{
    tot = 0;
    mu[1] = 1;
    memset(is_prime,0,sizeof(is_prime));
    for(int i = 2; i < maxn-10; i++)
    {
        if(!is_prime[i])
        {
            prime[tot++] = i;
            mu[i] = -1;
        }

        for(int j = 0; j < tot && i*prime[j] < maxn-10; j++)
        {
            is_prime[i*prime[j]] = 1;
            if(i % prime[j])
            {
                mu[i*prime[j]] = -mu[i];
            }
            else
            {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
}

ll dfs(int u,int gcd)
{
    if(dp[u] != -1) return dp[u];
    ll ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(ma[gcd][u][i])
        {
            ans = (ll)(ans +  ma[gcd][u][i] + (ll)ma[gcd][u][i]*dfs(i,gcd)%mod)%mod;
        }
    }
    return dp[u] = ans;
}

ll solve(int gcd)
{
    clr(dp,-1);
    ll ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(dp[i] == -1)
            dfs(i,gcd);
    }
    for(int i = 1; i <= n; i++)
        ans = (ans + dp[i])%mod;
    return ans;
}

void debug()
{
    for(int i = 1; i <= 10; i++)
    {
        num[i] = solve(i);
        cout << num[i] <<" ";
    }
    cout << endl;
}

int u[maxn*maxn*5],vec[maxn*maxn*5];
int v[maxn*maxn*5];
int x[maxn*maxn*5];
int main()
{
//    freopen("in.txt","r",stdin);
    int y;
    Moblus();
    read(n),read(m);
    memset(ma,0,sizeof(ma));
    for(int i = 1; i <= m; i++)
    {
        read(u[i]),read(v[i]);
        read(x[i]);
        for(int j = 1; j * j <= x[i]; j++)
        {
            if(x[i] % j) continue;
            ma[j][u[i]][v[i]] ++;
            if(j * j != x[i])
                ma[x[i]/j][u[i]][v[i]] ++;
        }
    }
    for(int i = 1; i <= 100; i++)
    {
        num[i] = solve(i);
    }
//    debug();
    read(q);
    ll ans = 0;
    for(int i = 1; i <= 100; i++)
    {
        ans = (ans + (ll)mu[i] * num[i] +mod)%mod;
    }
     printf("%I64d\n",ans);
    int id,cnt;
    for(int i = 1; i <= q; i++)
    {
        ans = 0,cnt = 0;
        read(id),read(y);
        int a = u[id],b = v[id];
        for(int i = 1; i*i <= x[id]; i++)
        {
            if(x[id] % i) continue;
            ma[i][a][b] --,vec[cnt++] = i;
            if(i * i != x[id])
                ma[x[id]/i][a][b] --,vec[cnt++] = x[id]/i;
        }
        x[id] = y;
        for(int i = 1; i*i <= x[id]; i++)
        {
            if(x[id] % i) continue;
            ma[i][a][b] ++,vec[cnt++] = i;
            if(i*i != x[id])
                ma[x[id]/i][a][b] ++,vec[cnt++] = x[id]/i;
        }

        for(int i = 0; i < cnt; i++)
        {
            num[vec[i]] = solve(vec[i]);
        }
//        debug();
        for(int i = 1; i <= 100; i++)
        {
            ans = (ans + (ll)mu[i] * num[i]+mod)%mod;
        }
        printf("%I64d\n",ans);
    }
    return 0;
}

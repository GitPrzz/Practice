/*
hdu 4616 Game ( ��������dp )
����dp ���Դ�����㿪ʼ ? ���ڵ�������
���仯����

���������ͨ������dp,ͨ��dp[now][tra]������now��ʱ��ץ��tra�ε����.
����Ū��һֱ������
�������֣����ַ����޷�ȷ���𰸣����� a-b-c��   ��a��b�ʹ�c��b��״̬��һ��,�����Ա����ļ��仯������������

������now����ʾ�ߵ�״̬�����������۴��ĸ��㿪ʼ״̬����Ψһ�ġ�
�����������ж��ȵذ�tra��״̬���ˣ������������ǹ��˺ܶ�����(�ܷ�)������һֱ�ġ�����

hhh-2016-08-04 20:42:49
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const int maxn=50000+10;
const int INF=0x3f3f3f3f;
const int mod = 250000+10;
int tot;
int val[maxn];
int trap[maxn];
int head[maxn];
int dp[maxn*2][4];
int limit;
struct edge
{
    int from,to,next;
} edge[maxn << 2];

void ini()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(dp,-1,sizeof(dp));
}

void add_edge(int u,int v)
{
    edge[tot].from = u;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

int dfs(int now,int tra)
{
    //cout <<now <<" "<<tra <<endl;
    if(tra == limit)
        return 0;
    if(dp[now][tra] != -1)
        return dp[now][tra];
    int u = edge[now].from;
    int v = edge[now].to;

    int tp = tra+trap[v];
    int value = val[v];
    for(int i = head[v]; ~i ; i = edge[i].next)
    {
        if(edge[i].to != u){
           // cout << "node:"<<v <<" to:"<<edge[i].to<< " limit:"<<tra <<" value:" <<value <<endl;
            value = max(value,dfs(i,tp)+val[v]);
            //cout << "node:"<<v <<" to:"<<edge[i].to<< " limit:"<<tra <<" value:" <<value <<endl;
        }
    }
    return (dp[now][tra] = value );
}


int main()
{
    int T,n;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        ini();
        scanf("%d%d",&n,&limit);
        //cout << limit << endl;
        for(int i = 0; i < n; i++)
        {
            scanf("%d%d",&val[i],&trap[i]);
            // cout << val[i] <<" " << trap[i] <<endl;
        }
        int a,b;
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);
            // cout << a <<" " << b <<endl;
        }
        int ans = 0;
       // cout << tot <<endl;
        for(int i = 0; i < tot; i++)
        {
            //if(i == 5)
            ans = max(ans,dfs(i,trap[edge[i].from])+val[edge[i].from]);
            //cout << ans <<endl;
        }
        printf("%d\n",ans);
    }
    return 0;
}

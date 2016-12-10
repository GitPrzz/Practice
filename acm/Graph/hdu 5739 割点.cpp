/*
hdu 5739 ���

problem:
����һ������ͼ,G[i]Ϊɾ��i��ʱ,����ͼ�ļ�ֵ.  �� sum(i*G[i])%mod
�����ǰ����ͨ��,��ô��ͨ�����ļ�ֵΪ���е�Ȩֵ�Ļ�(���������ڵ���ͨ)
����Ϊ��ֺ�ĸ�����ͨ�����ļ�ֵ�ĺ�

solve:
������Ҫ�жϵ�ǰ���Ƿ��Ǹ��.
������Ǹ��,ֻ��Ҫ��ȥ������Ȩֵ����. ����Ǹ��,Ҫ��ȥ�����ͨ�����ļ�ֵ�ټ��ϲ�ɢ��ĸ�����ͨ������ֵ

�ʼ����������- -,����ģ���е�����,һֱwa.

hhh-2016-08-27 19:47:17
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 1e9
using namespace std;
const ll mod = 1e9+7;
const int maxn = 100005;

struct Edge
{
    bool cut ;
    int v,next,w;
} edge[maxn*5];

int head[maxn],tot;
int low[maxn],dfn[maxn],Stack[maxn],index,top;
bool Instack[maxn],cut[maxn];
int bridge;
ll val[maxn],mul[maxn],ans[maxn],fans[maxn],tval[maxn];
void add_edge(int u,int v)
{
    edge[tot].v = v,edge[tot].next = head[u],head[u] = tot++;
}

ll tans  =1 ;

ll pow_mod(ll a,ll n)
{
    ll cnt =1 ;
    while(n)
    {
        if(n & 1) cnt = cnt*a%mod;
        a = a*a%mod;
        n >>= 1;
    }
    return cnt ;
}
int now;
vector<int> vec[maxn];
int from[maxn];
void Tarjan(int u,int ance,int pre)
{
    int v;
    vec[now].push_back(u);
    from[u] = now;
    low[u] = dfn[u] = ++index;
    Stack[top++] = u;
    Instack[u] = true;
    tans = tans*val[u] % mod;
    int son = 0;
    for(int i= head[u]; i!= -1; i = edge[i].next)
    {
        v = edge[i].v;
        if(v == pre){
            continue;
        }
        if(!dfn[v])
        {
            son ++ ;
            ll tp = tans;
            Tarjan(v,ance,u);
            low[u] = min(low[u],low[v]);

            if(u != pre && low[v] >= dfn[u])
            {
                cut[u] = true;
                ll ta = tans * pow_mod(tp,mod-2)%mod;
//                cout <<"node:" << u <<" ta:" <<ta <<endl;
                ans[u] = (ans[u] + ta)%mod;
                fans[u] = (fans[u] * ta) % mod;
            }
        }
        else if(low[u] > dfn[v])
            low[u] = dfn[v];
    }
    if(u == ance && son > 1)
        cut[u] = true;
    Instack[u] = false;
    top --;
}

void init(int n)
{
    for(int i = 0; i <= n+1; i++)
    {
        head[i] = -1;
        ans[i] = 0;
        fans[i] = 1;
        Instack[i]=cut[i]= 0;
        dfn[i] = 0;
        vec[i].clear();
    }
    tot=top=index=0;
}

int main()
{
//    freopen("in.txt","r",stdin);
    int T,n,m,u,v;

    scanfi(T);
    while(T--)
    {

        scanfi(n),scanfi(m);
        init(n);
        for(int i =1; i <= n; i++)
        {
            scanfl(val[i]);
            fans[i] = 1;
        }
        for(int i = 0; i < m; i++)
        {
            scanfi(u),scanfi(v);
            add_edge(u,v);
            add_edge(v,u);
        }
        now = 1;
        ll ob = 0;
        for(int i = 1; i <= n; i++)
        {
            if(!dfn[i])
            {
                tans= 1;
                Tarjan(i,i,-1);
                tval[now] = tans;
                ll amul = tans;
                ob = (ob+tans) %mod;
//                cout << "all:" <<tans<<endl;
                for(int j = 0 ; j < vec[now].size(); j ++)
                {
                    int to = vec[now][j];

//                    cout << to <<" " << fans[to] << endl;
                    if(to == i) continue;
                    ans[to] = (ans[to] + amul*pow_mod(fans[to]*val[to]%mod,mod-2)%mod);
                    if(ans[to] > mod) ans[to] -= mod;
                }
                now ++;
            }
        }
        ll out = 0;
        ll tm;
        for(int i = 1; i <= n; i++)
        {
//            cout << fans[i] <<" " << ans[i] <<" "  <<cut[i] << endl;
            int tf = from[i];
            if(cut[i])
            {
                tm = (ob - tval[tf] + ans[i] + mod)%mod;
            }
            else
            {
                if(vec[from[i]].size() > 1)
                    tm = (ob - tval[tf] + tval[tf]*pow_mod(val[i],mod-2)%mod + mod) % mod;
                else
                    tm = (ob - tval[tf] + mod) % mod;
            }
            out = (out + i * tm % mod) % mod;
        }
        printf("%I64d\n",out);
    }
    return 0;
}


/*
3
4 3
1 2 3 4
1 2
2 3
1 3

4 2
100000000 131231232 312354435 432134234
1 2
3 4

66
315142079

*/

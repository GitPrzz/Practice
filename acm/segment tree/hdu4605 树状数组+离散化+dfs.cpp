/*
hdu4605 ��״����+��ɢ��+dfs
һ�������ԵĴ������������˼������԰�����Ȼ������TAT��Ҳ������
�ʼ���ֿ���ͨ���ж����ߵ���ǰ�ڵ����ҵĴ��� �� ����С�ĸ���

��X�� 1/2 1/2    ��XС 1/8 7/8
�൱�ڱ�X��ʱ��һ��2������XСʱ��3��2   7�������
���Կ��Ա�������Ȼ���жϡ�   �ȵ�ǰ��С�����ĸ���������״����ά��

�����ʼд�������˺�2�Ĵ�����ֻ�����˵���ǰ�ڵ�С��������
(��û����������)�Լ����Ҵ�������ʵ�������������ܵó��ж��ٴ��ڱ���С
��ʱ�������߼�7/8�Ĵ���

���Ǻ�����״���鱣�������Ū�ɶ�ά�ľͺ��ˡ�Ȼ������ʼ����ɢ����
hhh-2016-03-03 22:57:09
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
using namespace std;
typedef long long ll;
const int maxn = 150050;
const int inf = 0x3f3f3f3f;
int s[maxn*2][2];
int n,tot;
int ans[maxn][2];
int vec[maxn*2];
int vis[maxn];
struct node
{
    int val;
    int l,r;
} pnode[maxn];


vector<pair<int,int> >qu[maxn];
int lowbit(int x)
{
    return x&(-x);
}

void add(int x,int val,int i)
{
    while(x <= tot)
    {
        s[x][i]+=val;
        x += lowbit(x);
    }
}

int sum(int x,int i)
{
    int cnt = 0;
    while(x)
    {
        cnt += s[x][i];
        x -= lowbit(x);
    }
    return cnt;
}

void dfs(int u,int l,int r)
{
    int lson=pnode[u].l,rson=pnode[u].r,pos;
    for(int i = 0; i < (int)qu[u].size(); i++)
    {
        int id = qu[u][i].first;
        int lim = qu[u][i].second;
        pos = lower_bound(vec,vec+tot,lim)-vec+1;
        int ls = sum(pos-1,0);
        int rs = sum(pos-1,1);
        int lls = sum(pos,0);
        int rrs = sum(pos,1);
        if(ls+rs != lls+rrs)
        {
            ans[id][0] = -1;
            continue;
        }
        ans[id][0] = (ls+rs)*2+l+r;
        ans[id][1] = rs;
    }
    pos = lower_bound(vec,vec+tot,pnode[u].val)-vec+1;

    if(lson != -1)
    {
        add(pos,1,0);
        dfs(lson,l+1,r);
        add(pos,-1,0);
    }
    if(rson != -1)
    {
        add(pos,1,1);
        dfs(rson,l,r+1);
        add(pos,-1,1);
    }
    return ;
}


int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(s,0,sizeof(s));
        memset(ans,0,sizeof(ans));
        int m,q,M,v;
        tot = 0;
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&pnode[i].val);
            pnode[i].l = pnode[i].r = -1;
            vec[tot++] = (pnode[i].val);
        }
        scanf("%d",&m);
        for(int i =1; i <= m; i++)
        {
            int x;
            scanf("%d",&x);
            scanf("%d%d",&pnode[x].l,&pnode[x].r);
        }
        scanf("%d",&q);
        for(int i =1; i <= q+n; i++)qu[i].clear();
        for(int i =1; i <= q; i++)
        {
            scanf("%d%d",&v,&M);
            qu[v].push_back(make_pair(i,M));
            vec[tot++] = M;
        }
        sort(vec,vec+tot);
        tot = unique(vec,vec+tot)-vec;
        dfs(1,0,0);
        for(int i =1; i <=q ; i++)
        {
            if(ans[i][0] == -1)
                printf("0\n");
            else
                printf("%d %d\n",ans[i][1],ans[i][0]);
        }
    }
    return 0;
}

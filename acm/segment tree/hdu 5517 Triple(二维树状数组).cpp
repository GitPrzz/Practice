/*
hdu 5517 Triple(二维树状数组)

problem:
给你n个二元组<a,b>, m个三元组<c,d,e>. 如果d = e,那么<a,c,d>会组成一个新的三元组集合G.
问G中有多少个三元组在凸点.(没有其它三元组比它大)

solve:
要注意去重. 因为要求没有其它三元组比它大. 如果同一个b有多个a,那么只需要取最大的即可.
然后通过排序可以解决第一位a. 剩下两位c,d则可以通过二维树状数组来维护是否是最大值.
三元组G中相同的合并.

hhh-2016-08-31 20:06:36
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
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1e9+7;
const int maxn = 100010;
const int maxx = 1050;
int a,b;
int to[maxn],have[maxn];

struct node
{
    int a,b,c;
    int w;
    node(){}
    node(int _a,int _b,int _c,int _w):a(_a),b(_b),c(_c),w(_w) {}
    bool operator <(const node &t)const
    {
        if(a!= t.a)
            return a < t.a;
        else if(b != t.b)
            return b < t.b;
        else if(c != t.c)
            return c < t.c;
    }
    node operator +(const node &t)const
    {
        return node(a,b,c,w+t.w);
    }
    bool operator ==(const node &t)const
    {
        return !(*this<t || t < *this);
    }
};
ll s[maxx][maxx];
int lowbit(int x)
{
    return x&(-x);
}
void add(int x,int y,ll val)
{
    for(int i = x; i <= 1000; i+=lowbit(i))
        for(int j = y; j <= 1000; j+=lowbit(j))
        {
            s[i][j] += val;
        }
}

ll sum(int x,int y)
{
    ll cnt = 0;
    for(int i = x; i > 0; i-=lowbit(i))
        for(int j = y; j > 0; j-=lowbit(j))
        {
            cnt += s[i][j];
        }
    return cnt;
}
node tp[maxn];
int main()
{
    int T,cas =1;
    int c,d,e;
//    freopen("in.txt","r",stdin);
    scanfi(T);
    while(T--)
    {
        int n,m;
        clr(s,0),clr(to,0);
        int Maxy = 0, Maxx = 0,cnt = 0;
        scanfi(n),scanfi(m);
        for(int i = 0; i < n; i++)
        {
            scanfi(a),scanfi(b);
            if(a > to[b])to[b] = a,have[b] = 1;
            else if(a == to[b])have[b] ++;
//            cout << a[i] <<" " <<b[i] <<endl;
        }
        for(int i = 0; i < m; i++)
        {
            scanfi(c),scanfi(d),scanfi(e);
            Maxx = max(Maxx,c);
            Maxy = max(Maxy,d);
            if(to[e])
              tp[cnt++] = node(to[e],c,d,have[e]);
        }
        sort(tp,tp+cnt);
        int tot = 0;
        for(int i = 1;i < cnt;i++)
        {
            if(tp[i] == tp[tot])
            {
                tp[tot] = tp[tot] + tp[i];
            }
            else
            {
                tp[++tot] = tp[i];
            }
        }
        ll ans = 0;
        for(int i = tot;i >= 0;i--)
        {
            node t = tp[i];
//            printf("%d%d%d %d\n",t.a,t.b,t.c,t.w);
            int x = t.b,y = t.c;
            int large = sum(1000,1000)-sum(x-1,1000)-sum(1000,y-1)+sum(x-1,y-1);
//            if(t.a != last)
//                large -= have;
            if(large == 0)
                ans = (ll)(ans+t.w);
            add(x,y,1);
        }
        printf("Case #%d: %I64d\n",cas++,ans);
    }
    return 0;
}

/*
1
3 4
2 7 2 7 2 7
1 4 7 2 3 7 3 2 7 4 1 7
*/

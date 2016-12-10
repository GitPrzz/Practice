/*
hdu 5314 动态树

problem:
给你一个树,求有多少对(u,v)使u->v路径上面的最大值减去最小值不大于limit

solve:
最开始想的是用树链剖分维护最大最小值,结果超时  卒。。
然后看别人说动态树比树链剖分快一点,于是去学习两天动态树,然后用其维护最大最小值 卒。。

感觉没什么思路 - -
后来发现别人维护一个树的size.维持树中的最大最小值的差不大于limit
所以先按照权值排序,用两个指针. 如果 当前值-最左边值(l) > limit,就将l从这个树中除去
然后将当前节点连接到树上面,即判断与其相连的点哪些在树上面(可以用个数组来判断).

大致思路如此,然后就是如何维护size. 首先动态树中的重链是一直变化的,通常我们是用splay来维护重链上面的值,
所以需要outsize来维护哪些不在重链上面的点.
而 重链 和 普通链会在ACCESS的时候发生变化,于是在其过程中维护一下.

参考:http://blog.csdn.net/u013368721/article/details/47086899
hhh-2016-08-21 09:16:05
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#define lson  ch[0]
#define rson  ch[1]
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define key_val ch[ch[root][1]][0]
using namespace std;
const int maxn = 300100;
const int INF = 1e9+10;
ll ans ;
struct Node* null;
struct Node
{
    Node* ch[2] ;
    Node* fa;
    int Size ;
    int Outsize;
    int val,rev;
    void newnode(int v)
    {
        val = v;
        Size = 1 ;
        Outsize = 0;
        fa = ch[0] = ch[1] = null ;
        rev = 0;
    }
    void update_rev()
    {
        if(this == null)
            return ;
        swap(ch[0],ch[1]);
        rev ^= 1;
    }
    void push_up () {
        if(this == null)
            return ;
        Size = ch[0]->Size + 1 + ch[1]->Size + ch[0]->Outsize + ch[1]->Outsize;
//        cout << ch[0]->Size <<" " <<ch[1] <<Size <<endl;
    }

    void push_down()
    {
        if(this == null)
            return ;
        if(rev)
        {
            ch[0]->update_rev();
            ch[1]->update_rev();
            rev = 0;
        }
    }

    void link_child ( Node* to , int d )
    {
        ch[d] = to;
        to->fa = this ;
    }

    int isroot()
    {
        return fa == null || this != fa->ch[0] && this != fa->ch[1] ;
    }
    void down()
    {
        if ( !isroot () ) fa->down () ;
        push_down () ;
    }
    void Rotate ( int d )
    {
        Node* f = fa ;
        Node* ff = fa->fa ;
        f->link_child ( ch[d] , !d ) ;
        if ( !f->isroot () )
        {
            if ( ff->ch[0] == f ) ff->link_child ( this , 0 ) ;
            else ff->link_child ( this , 1 ) ;
        }
        else fa = ff ;
        link_child (f,d) ;
        f->push_up () ;
    }

    void splay ()
    {
        down () ;
        while ( !isroot () ) {
            if ( fa->isroot () ) {
                this == fa->ch[0] ? Rotate ( 1 ) : Rotate ( 0 ) ;
            } else {
                if ( fa == fa->fa->ch[0] ) {
                    this == fa->ch[0] ? fa->Rotate ( 1 ) : Rotate ( 0 ) ;
                    Rotate ( 1 ) ;
                } else {
                    this == fa->ch[1] ? fa->Rotate ( 0 ) : Rotate ( 1 ) ;
                    Rotate ( 0 ) ;
                }
            }
        }
        push_up () ;
    }

    void access()
    {
        Node* now = this ;
        Node* x = null ;
        while ( now != null )
        {
//            cout <<"now:"<< now->val <<" f:" <<x->val <<endl;
            now->splay () ;
            now->Outsize += (now->ch[1]->Size+now->ch[1]->Outsize);
            now->Outsize -= (x->Size + x->Outsize);
            now->link_child ( x , 1 );
            now->push_up () ;
            x = now ;
            now = now->fa ;
        }
        splay() ;
    }

    void make_root()
    {
        access();
        update_rev();
    }

    void cut()
    {
        access();
        ch[0]->fa = null;
        ch[0] = null;
        push_up();
    }
    void cut(Node* to)
    {
        make_root();
        to->cut();
    }

    void link(Node* to)
    {
        make_root();
        to->make_root();
        fa = to;
//        cout << Size <<" " << Outsize <<endl;
        ans += (ll)(to->Size + to->Outsize)*(Size+Outsize);
//        cout << ans  <<endl;
        to->Outsize += (Size + Outsize);
        push_up();
    }
};
Node memory_pool[maxn];
Node* now;
Node* node[maxn];
struct Edge
{
    int to,next;
}edge[maxn << 2];
int head[maxn],tot;
int vis[maxn];
void Clear()
{
    now = memory_pool;
    now->newnode(-INF);
    null = now ++;
    null->Size = 0;
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
}

void add_edge(int u,int v)
{
    edge[tot].to = v,edge[tot].next = head[u],head[u] = tot ++;
}
struct Point
{
    int id,v;
}po[maxn];

bool cmp(Point a,Point b)
{
    return a.v < b.v;
}
int main()
{
    int T,n,cas = 1,limit;
    int x,a,b;

//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        Clear();
        scanf("%d%d",&n,&limit);
        ans = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&x);
            now->newnode(x);
            node[i] = now++;
            po[i].v = x,po[i].id = i;
        }
        sort(po+1,po+1+n,cmp);
        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            add_edge(a,b);
            add_edge(b,a);
        }
        int l= 1;
        for(int i =1;i <= n;i++)
        {
            while(l <= i && po[i].v - po[l].v > limit)
            {
                int u = po[l].id;
                for(int j = head[u];~j;j = edge[j].next)
                {
                    int v = edge[j].to;
                    if(!vis[v])
                        continue;
                    node[u]->cut(node[v]);
                }
                vis[u] = 0;
                ++l;
            }
            int u = po[i].id;
            for(int j = head[u];~j; j = edge[j].next)
            {
//                cout <<edge[j].to <<endl;
                int v = edge[j].to;
                if(!vis[v])
                    continue;
                node[u]->link(node[v]);
            }
            vis[u] = 1;
        }
        printf("%I64d\n",ans*2);
    }
    return 0;
}

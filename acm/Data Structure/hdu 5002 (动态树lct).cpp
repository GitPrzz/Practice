/*
hdu 5002 (动态树lct)

problem:
给你一棵树树,主要包含四个操作:
1 x y u v:断开x,y之间的边 连接上u,v
2 x y w:将x->y之间的点权全部置为w
3 x y w:将x->y之间的点权全部加上w
4 x y:查询x->y之间第二大的

solve:
只是需要维护下第二大值,其它直接套模板

hhh-2016-08-20 17:21:29
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
const int INF = 0x3f3f3f3f;

struct Node* null;
struct Node
{
    Node* ch[2] ;
    Node* fa;
    int Size ;
    int mMax ;
    int sMax ;
    int max_num ;
    int Max_num ;
    int val ;
    int add ;
    int same ;
    int rev;
    void newnode(int v)
    {
        val = v ;
        mMax = v ;
        sMax = -INF ;
        Max_num = 1 ;
        max_num = 0 ;
        Size = 1 ;
        add = 0 ;
        same = -INF ;
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
    void update_add(int v)
    {
        if(this == null )return ;
        add += v;
        mMax += v,val += v;
        if(sMax != -INF) sMax += v;
    }

    void update_same(int v)
    {
        if(this == null) return ;
        same = v;
        add = 0,val = v,mMax = v;
        sMax = -INF,Max_num = Size,max_num = 0;
    }
    void cal(int val,int num)
    {
        if ( val == -INF ) return ;
        if ( val < sMax ) return ;
        if ( val > mMax )
        {
            sMax = mMax ;
            max_num = Max_num ;
            mMax = val ;
            Max_num = num ;
        }
        else if ( val == mMax )
        {
            Max_num += num ;
        }
        else if ( val > sMax )
        {
            sMax = val ;
            max_num = num ;
        }
        else max_num += num ;
    }
    void push_up () {
        Size = ch[0]->Size + 1 + ch[1]->Size ;
        mMax = sMax = -INF ;
        max_num = Max_num = 0 ;
        cal ( val , 1 ) ;
        cal ( ch[0]->mMax , ch[0]->Max_num ) ;
        cal ( ch[0]->sMax , ch[0]->max_num ) ;
        cal ( ch[1]->mMax , ch[1]->Max_num ) ;
        cal ( ch[1]->sMax , ch[1]->max_num ) ;
    }

    void push_down()
    {
        if(rev)
        {
            ch[0]->update_rev();
            ch[1]->update_rev();
            rev = 0;
        }
        if(same != -INF)
        {
            ch[0]->update_same(same);
            ch[1]->update_same(same);
            same = -INF;
        }
        if(add)
        {
            ch[0]->update_add(add);
            ch[1]->update_add(add);
            add = 0;
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
            now->splay () ;
            now->link_child ( x , 1 ) ;
            now->push_up () ;
            x = now ;
            now = now->fa ;
        }
        splay () ;
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
    Node* find_root ()
    {
        access () ;
        Node* to = this ;
        while ( to->ch[0] != null )
        {
            to->push_down () ;
            to = to->ch[0] ;
        }
        return to ;
    }
    void cut(Node* to)
    {
        to->make_root();
        cut();
    }

    void link(Node* to)
    {
        to->make_root();
        to->fa = this;
    }
    void make_same(Node* to,int val)
    {
        to->make_root();
        access();
        update_same(val);
    }
    void make_add(Node* to,int val)
    {
        to->make_root();
        access();
        update_add(val);
    }
    void query(Node* to)
    {
        to->make_root();
        access();

        if(!max_num)
            printf("ALL SAME\n");
        else
            printf("%d %d\n",sMax,max_num);
    }
};
Node memory_pool[maxn];
Node* now;
Node* node[maxn];

void Clear()
{
    now = memory_pool;
    now->newnode(-INF);
    null = now ++;
    null->Size = 0;
}

int main()
{
    int T,n,cas = 1,m;
    int x,y,a,b,c;
    int ob;
//    freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        Clear();
        scanf("%d%d",&n,&m);
        printf("Case #%d:\n",cas++);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&x);
            now->newnode(x);
            node[i] = now++;
        }

        for(int i = 1; i < n; i++)
        {
            scanf("%d%d",&a,&b);
            node[a]->link(node[b]);

        }
        for(int i= 1; i <= m; i++)
        {
            scanf("%d",&ob);
            if(ob == 1)
            {
                scanf("%d%d%d%d",&x,&y,&a,&b);
                node[x]->cut(node[y]);
                node[a]->link(node[b]);
            }
            else if(ob == 2)
            {
                scanf("%d%d%d",&x,&y,&c);
                node[x]->make_same(node[y],c);
            }
            else if(ob == 3)
            {
                scanf("%d%d%d",&x,&y,&c);
                node[x]->make_add(node[y],c);
            }
            else if(ob == 4)
            {
                scanf("%d%d",&x,&y);
                node[x]->query(node[y]);

            }
        }
    }
    return 0;
}

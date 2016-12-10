/*
hdu 5398 ��̬��LCT

problem:
����n����,���㹹��һ����,�ߵ�ȨֵΪ�˵�����Լ��. ����������Ȩ��

solve:
ö�����е�,Ȼ��̰�ĵ�˼��.���n-1���㹹����һ������������,��ô�����n����ʱ����Ӧ�����ܰ�����
�Լ���Լ������(��->С).�����Ļ��������ӵڶ���Լ����ʱ��ͻṹ�ɻ�,������Ҫ�� ��ǰ��-->��ǰԼ���������
�Ͽ���С��һ����.
���Կ���ö�� �����Լ��,Ȼ������LCTά�����������С��. ��������˺ܾ�,��֪��Ӧ�ðɱ�Ȩ�������ĸ��˵�
�ȽϺã��ܸо�����ì�� = =||. ���������ȫ����Ū�����������,�����ϵ�ֵ��ʼ�����޴������T_T,��2...

hhh-2016-08-21 16:43:04
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
const int maxn = 100100;
const int INF = 0x3f3f3f3f;

struct Node* null;
struct Node
{
    Node* ch[2] ;
    Node* fa;
    int Min;
    Node* Minnode;
    int Size,lpos,rpos ;
    int rev;
    void newnode(int v)
    {
        Min = v;
        Size = 1 ;
        Minnode = this;
        lpos = rpos = 0;
        fa = ch[0] = ch[1] = null ;
        rev = 0;
    }
    void ini()
    {
        Min = INF;
        Size = 1 ;
        Minnode = this;
        lpos = rpos = 0;
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

    void push_up ()
    {
        Minnode = this;
        if(ch[0] && ch[0]->Minnode->Min < Minnode->Min)
            Minnode = ch[0]->Minnode;
        if(ch[1] && ch[1]->Minnode->Min < Minnode->Min)
            Minnode = ch[1]->Minnode;
    }

    void push_down()
    {
        if(rev)
        {
            ch[0]->update_rev();
            ch[1]->update_rev();
            rev = 0;
        }
    }

    void link_child ( Node* o , int d )
    {
        ch[d] = o ;
        o->fa = this ;
    }

    int isroot()
    {
        return fa == null || this != fa->ch[0] && this != fa->ch[1] ;
    }
    void sign_down ()
    {
        if ( !isroot () ) fa->sign_down () ;
        push_down () ;
    }
    void Rotate ( int d )
    {
        Node* p = fa ;
        Node* gp = fa->fa ;
        p->link_child ( ch[d] , !d ) ;
        if ( !p->isroot () )
        {
            if ( gp->ch[0] == p ) gp->link_child ( this , 0 ) ;
            else gp->link_child ( this , 1 ) ;
        }
        else fa = gp ;
        link_child ( p , d ) ;
        p->push_up () ;
    }

    void splay ()
    {
        sign_down () ;
        while ( !isroot () )
        {
            if ( fa->isroot () )
            {
                this == fa->ch[0] ? Rotate ( 1 ) : Rotate ( 0 ) ;
            }
            else
            {
                if ( fa == fa->fa->ch[0] )
                {
                    this == fa->ch[0] ? fa->Rotate ( 1 ) : Rotate ( 0 ) ;
                    Rotate ( 1 ) ;
                }
                else
                {
                    this == fa->ch[1] ? fa->Rotate ( 0 ) : Rotate ( 1 ) ;
                    Rotate ( 0 ) ;
                }
            }
        }
        push_up () ;
    }

    void access()
    {
        Node* o = this ;
        Node* x = null ;
        while ( o != null )
        {
            o->splay () ;
            o->link_child ( x , 1 ) ;
            o->push_up () ;
            x = o ;
            o = o->fa ;
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
        Node* o = this ;
        while ( o->ch[0] != null )
        {
            o->push_down () ;
            o = o->ch[0] ;
        }
        return o ;
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
    Node* query(Node* to)
    {
        to->make_root();
        access();
        return Minnode;
    }
};
Node memory_pool[maxn*2];
Node* now;
Node* node[maxn];

void Clear()
{
    now = memory_pool;
    now->newnode(INF);
    null = now ++;
    null->Size = 0;
}
int dp[maxn];
vector<int > vec[maxn];

void init()
{
    Clear();
    for(int i = 100000; i >= 1; i--)
    {
        now->newnode(INF);
        node[i] = now++;
        for(int j = i+i; j <= 100000; j+=i)
        {
            vec[j].push_back(i);
        }
    }
    int tans = 0;
    dp[1] = 0;
    now->newnode(INF),node[1] = now++;
    for(int i =2; i <= 100000; i++)
    {
//        cout << "number:" << i<<endl;
        now->newnode(vec[i][0]);
        Node *tp = now++;
        tp->link(node[i]);
        tp->link(node[vec[i][0]]);
        tp->lpos = i,tp->rpos = vec[i][0];
        tans += vec[i][0];
//        cout << tp->lpos <<" " <<tp->rpos <<" " <<tans <<endl;
        for(int j = 1;j < vec[i].size();j++)
        {
            int to = vec[i][j];
//            cout <<"to "<<to <<endl;

            Node* tMin = node[to]->query(node[i]);
//            cout <<"Min:" << tMin->lpos <<" " <<tMin->rpos <<" "<<tMin->Min <<endl;
            if(tMin->Min < to)
            {
                tans -= tMin->Min;
                tMin->cut(node[tMin->lpos]);
//                cout <<"cut1 ";
                tMin->cut(node[tMin->rpos]);
//                cout << "cut2" <<endl;
                tMin->ini();
                tMin->Min = to,tMin->lpos = i,tMin->rpos = to;
//                cout << i <<" " <<to<<endl;

                tMin->link(node[i]);
//                 cout <<"link1 ";
                tMin->link(node[to]);
//                cout << "link2" <<endl;
                tans += to;
            }
        }
        dp[i] = tans ;
    }
}


int main()
{

//    freopen("in.txt","r",stdin);
    init();
    int n;
    while( scanf("%d",&n) !=EOF)
    {
        printf("%d\n",dp[n]);
    }
    return 0;
}

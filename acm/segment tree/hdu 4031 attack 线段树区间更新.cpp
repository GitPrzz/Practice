/*
hdu 4031 attack �߶����������

problem:
ÿ��λ����һ����������ÿ�ε��˻��һ��������й�������������һ����ȴʱ��t��
��ĳ��ʱ��ʱ��ĳ��λ�ñ��ɹ������Ĵ�����û�б�������

solve:
��Ҫ����ô���������ȴֵ�����⣬���乥��������ʹ�� �߶�����������������
�ʼ���ǵ���ͨ�� ������ά��ÿ���㣬��ÿ�ξ�Ҫ����[1,n]���о�Ӧ�ûᳬʱ��
Ȼ���뵽�� ͨ��ÿ��-1������ʱ��ı仯�������޷�֪��ÿ���㹥���ɹ������

����ֱ�ӱ�������- -
ͨ���߶�����¼�������˶��ٴΣ�Ȼ��ͨ����¼����֪�������ɹ��˶��ٴ�
���Ǿ��ܵó��𰸡�

hhh-2016-08-05 21:16:55
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
#pragma comment(linker, "/STACK:1024000000,1024000000")
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn=100000 + 10;
const int INF=0x3f3f3f3f;
const int mod = 1e9+7;
int n;

struct node
{
    int l,r;
    int val;
    int len ;
    int mid()
    {
        return (l+r)>> 1;
    }
} tree[maxn<<2];


void push_up(int i)
{
}

void build(int i,int l,int r)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].val = tree[i].len = 0;
    if(l == r)
    {
        return ;
    }
    int mid = tree[i].mid();
    build(lson,l,mid);
    build(rson,mid+1,r);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].val)
    {
        tree[lson].val += tree[i].val;
        tree[rson].val += tree[i].val;
        tree[i].val = 0;
    }
}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].val += val;
        push_up(i);
        return ;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
}

int query(int i,int k)
{
    if(tree[i].l == tree[i].r && tree[i].l == k)
    {
        return tree[i].val;
    }
    push_down(i);
    int mid = tree[i].mid();
    if(k <= mid)
        return query(lson,k);
    else
        return query(rson,k);
}
struct Point
{
    int l,r;
    Point()
    {

    }
    Point(int a,int b)
    {
        l = a,r = b;
    }
};
Point pt[maxn];
char op[5];

int main()
{
    int T,n,m,k;
    int cas = 1;
    int a,b;
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        int cnt = 0;
        build(1,1,n);
        printf("Case %d:\n",cas++);
        for(int i = 1;i <= m;i++)
        {
            scanf("%s",op);
            if(op[0] == 'Q')
            {
                int num = 0;
                scanf("%d",&a);
                for(int i = 0;i < cnt;)
                {
                    if( a>= pt[i].l && a <= pt[i].r)
                    {
                        num++;
                        i += k;
                    }
                    else
                    {
                        i++;
                    }
                }
                printf("%d\n",query(1,a) - num);
            }
            else
            {
                scanf("%d%d",&a,&b);
                Insert(1,a,b,1);
                pt[cnt++] = Point(a,b);
            }
        }
    }
    return 0;
}

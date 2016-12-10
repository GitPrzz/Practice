/*
hdu 3952 �߶��� (�������)

����n���ˣ�Ȼ���������������ǰ�˵ĵȼ�Ϊx���ֵľ���Ϊk���������
���Եõ�x*k�ľ��顣
Ȼ��k-1������ʾ2-k������Ҫ�ľ��飬��������leve[k]�ľ��飬��������
����k����(�ʼ��Ϊ��k-1��k��Ҫleve[k]�ľ��� TAT)

�ʼֻ�Ǽ�¼�ľ������ֵMAX��add��ǣ�Ȼ��������ֵ��
����ÿ�ζ�Ҫ���ҵȼ���С,�о�Ӧ����TLE,��ȴһֱWR.�о��ܷѽ�

Ȼ�������±��˵�˼·
������һ��need��grade,��������������������Сֵ,�����ӵľ���С��
���need,�������Щ��Ǽ���.������ҵ���Щ��Ҫ�����Ľ���������

hhh-2016-03-22 22:48:41
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
int n,qw;
int k;
const int maxn = 10010;
struct node
{
    int l,r,grade;
    int Max;
    int add,need;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn*10];
int leve[15];


void push_up(int i)
{
    tree[i].Max = max(tree[lson].Max,tree[rson].Max);
    tree[i].grade = max(tree[lson].grade,tree[rson].grade);
    tree[i].need = min(tree[lson].need,tree[rson].need);
}

void fin_level(int cur)
{
    for(int i = tree[cur].grade; i < k; i++)
    {
        if(tree[cur].Max >= leve[i])
            tree[cur].grade = i+1;
    }
}

void build(int l,int r,int i)
{
    tree[i].l = l;
    tree[i].r = r;
    tree[i].Max = tree[i].add = 0;
    tree[i].need = leve[1];
    tree[i].grade = 1;
    if(l == r)
    {
        return ;
    }
    int mid = tree[i].mid();
    build(l,mid,lson);
    build(mid+1,r,rson);
    push_up(i);
}

void push_down(int i)
{
    if(tree[i].add)
    {
        tree[lson].add += tree[i].add;
        tree[rson].add += tree[i].add;
        tree[lson].Max += tree[i].add*tree[lson].grade;
        tree[rson].Max += tree[i].add*tree[rson].grade;
        tree[lson].need -= tree[i].add;
        tree[rson].need -= tree[i].add;
        tree[i].add = 0;
    }
}

void Insert(int i,int l,int r,int val)
{
    push_down(i);
    int mid = tree[i].mid();
    if(tree[i].l == tree[i].r)
    {
        tree[i].Max += val*tree[i].grade;
        fin_level(i);
        tree[i].need = (leve[tree[i].grade]-tree[i].Max)/(tree[i].grade)+
        ((leve[tree[i].grade]-tree[i].Max)%(tree[i].grade)!=0);
        return ;
    }
    else if(tree[i].l >= l && tree[i].r <= r)
    {
        if(tree[i].need > val)
        {
            tree[i].add += val;
            tree[i].need -= val;
            tree[i].Max += (ll)val*tree[i].grade;
            return ;
        }
        push_down(i);
        if(l <= mid)Insert(lson,l,r,val);
        if(r > mid)Insert(rson,l,r,val);
        push_up(i);
        return;
    }
    if(l <= mid)Insert(lson,l,r,val);
    if(r > mid)Insert(rson,l,r,val);
    push_up(i);
}

int query(int i,int l,int r)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        return tree[i].Max;
    }
    push_down(i);
    int ma = 0;
    int mid = tree[i].mid();

    if(l <= mid)
        ma =max(ma,query(lson,l,r));
    if(r > mid)
        ma =max(ma,query(rson,l,r));
    return ma;
}

int main()
{
    int T,cas = 1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&k,&qw);
        for(int i = 1; i < k; i++)
            scanf("%d",&leve[i]);
        build(1,n,1);
        leve[0] = 0;

        leve[k] = 1<<30;
        char ch[4];
        int l,r;
        int val;
        printf("Case %d:\n",cas++);
        for(int i = 1; i <=qw; i++)
        {
            scanf("%s",ch);
            if(ch[0] == 'Q')
            {
                scanf("%d%d",&l,&r);
                ll ma = query(1,l,r);
                printf("%I64d\n",ma);
            }
            if(ch[0] == 'W')
            {
                scanf("%d%d%d",&l,&r,&val);
                Insert(1,l,r,val);
            }
        }
        printf("\n");
    }
    return 0;
}

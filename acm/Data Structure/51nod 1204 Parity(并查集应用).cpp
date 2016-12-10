/*
51nod 1204 Parity(���鼯Ӧ��)

problem:
����Դ���ѡ��һ��������01�Ӵ�,Ȼ����q��ѯ�ʺͻش�. ��ʾ����[l,r]������������ż����1. ���һ������ì�ܵ�λ��

solve:
���������߶���ʲô��,���ֲ�����ô����.    û�������Ƶ�,��ȫû�뵽���鼯,��.....
���[l,r]��even,��ô[1,l-1]��[1,r]��1�ĸ�������ż�� or ����.
���[l,r]��odd,��ô [1,l-1] �� [1,r]����ż�Բ�ͬ.

������[1,n]��ʾ'��ͬ'��ϵ,[n+1,2*n]�����ʾ'��ͬ'��ϵ.������������
�ж� (l-1+n,r) && (l-1,b+n) ����ȷ�� l-1��r�Ƿ�Ϊ'��ͬ'��ϵ.  ����ͬ��

hhh-2016/09/06-20:47:14
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
const int maxn = 300050;
const double PI = acos(-1.0);
const int limit = 33;
int pre[maxn];
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

int fin(int x)
{
    if(pre[x ]== x) return x;
    return pre[x] = fin(pre[x]);
}

void unio(int a,int b)
{
    int ta= fin(a);
    int tb = fin(b);
    pre[ta] = tb;
}
char op[10];

int main()
{
//    freopen("in.txt","r",stdin);
    int n,q,flag = 0;
    int a,b;
    read(n);
    read(q);
    for(int i = 0;i <= 2*n;i++)
        pre[i] = i;
    for(int i = 1; i <= q; i++)
    {
        scanf("%d%d%s",&a,&b,op);
        if(flag)
            continue;
        if(op[0] == 'e')
        {
            if(fin(a-1+n) == fin(b) && fin(a-1) == fin(b + n))
            {
                flag = i;
            }
            unio(a-1,b);
            unio(a-1+n,b+n);
        }
        else
        {
            if(fin(a-1) == fin(b) && fin(a-1+n) == fin(b+n))
            {
                flag = i;
            }
            unio(a-1+n,b);
            unio(a-1,b+n);
        }
    }
    if(flag)
        printf("%d\n",flag);
    else
        printf("-1\n");
    return 0;
}

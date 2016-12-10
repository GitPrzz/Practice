/*
51nod1295 XOR key(�ɳ־û�trie)

problem:
��[a[l],a[r]]�е�����x������ܵõ������ֵ.

solve:
Ҫ���������ֵ,ͨ���ǴӸ�λ����λ����ƥ��.
����Ҫ���������ܵõ������ֵ,��������������ϯ���ķ���. T[i]�������Ӿ���T[i-1]�������½��ڵ�
����̳�T[i-1]�Ľڵ�.�Ӷ��õ�[1,i]���������Tire��.
Ȼ����������������м���.

hhh-2016/09/05-15:23:44
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
#define scanfd(a) scanf("%lf",&a)
#define key_val ch[ch[root][1]][0]
#define eps 1e-7
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const ll mod = 1000000007;
const int maxn = 50010;
const double PI = acos(-1.0);
const int limit = 33;
int bin[65];
int tot;
int son[maxn*limit*2][2],val[maxn*limit*30];
int T[maxn];

void init()
{
    tot = 0;
    memset(son,-1,sizeof(son));
    memset(val,0,sizeof(val));
}

int Insert(int root,int cur)
{
    if(cur<0)return -1;
    int t = bin[cur-1];
    int rt =++tot;
    val[rt] = val[root] + 1;
    son[rt][t^1] = son[root][t^1];                    //������µĵ�
    son[rt][t] = Insert(son[root][t],cur-1);
    return rt;
}

int cal(int root1,int root2,int cur)
{
    if(cur < 0)
        return 0;
    int t = bin[cur-1];
    if(val[son[root2][t]] - val[son[root1][t]] > 0)
        return cal(son[root1][t],son[root2][t],cur-1) + (1 << (cur-1));
    return cal(son[root1][t^1],son[root2][t^1],cur-1);
}

int main()
{
    int n,q;
    int x,l,r;
    while(scanfi(n) != EOF)
    {
        init();
        scanfi(q);
        int x;
        for(int i = 1; i <= n; i++)
        {
            scanfi(x);
            for(int i = 0; i <= limit; i++)
            {
                bin[i] = x % 2;
                x /= 2;
            }
            T[i] = Insert(T[i-1],limit);
        }
        for(int i = 1;i <= q;i++)
        {
            scanfi(x),scanfi(l),scanfi(r);
            for(int i = 0; i <= limit; i++)
            {
                bin[i] = 1-x % 2;
                x /= 2;
            }
            printf("%d\n",cal(T[l],T[r+1],limit));
        }
    }
    return 0;
}

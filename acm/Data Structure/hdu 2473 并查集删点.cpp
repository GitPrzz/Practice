/*
hdu 2473 并查集删点

problem:
每次有n个点，然后是m个询问：
M a b:将a，b合并                      S a:移除a与其它点的关系(将a从它的集合中孤立出来)
然后问最终有多少个集合

solve:
M就相当于并查集的合并操作，在删除a的时候维持原先的结构不变，将其映射到虚拟的点上
然后查找有多少个根节点即可

hhh-2016-08-10 16:19:42
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
typedef unsigned int ul;
const int INF = 0x3f3f3f3f;
const int  maxn = 1000000+10;
const int mod = 1e9+7;

int pre[maxn];
int id[maxn];
int num[maxn];

int fin(int x)
{
    if(pre[x] == -1) return x;
    return pre[x] = fin(pre[x]);
}

void unio(int a,int b)
{
    int ta = fin(id[a]);
    int tb = fin(id[b]);
    if(ta == tb)
        return ;
    pre[ta] = tb;
    num[tb] += num[ta];
    num[ta] = 0;
}
char str[4];

int main()
{
    int n,m;
    int a,b;
    int cas =1 ;
    while(scanf("%d%d",&n,&m) != EOF)
    {
        if(n == 0 && m == 0)
            break;
        for(int i = 0; i < maxn; i++)
        {
            pre[i] = -1,num[i] = 1,id[i] = i;
        }
        int cnt = n;
        for(int i = 1; i <= m; i++)
        {
            scanf("%s",str);
            if(str[0] == 'M')
            {
                 scanf("%d%d",&a,&b);
                 unio(a,b);
            }
            else
            {
                 scanf("%d",&a);
                 num[fin(id[a])] -- ;
                 id[a] = cnt++;
            }
        }
        int ans = 0;
        for(int i = 0;i < cnt;i++)
        {
           if(num[i])
                ans ++ ;
        }
        printf("Case #%d: ",cas++);
        printf("%d\n",ans);
    }
    return 0;
}

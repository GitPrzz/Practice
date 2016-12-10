/*
hdu 2473 ���鼯ɾ��

problem:
ÿ����n���㣬Ȼ����m��ѯ�ʣ�
M a b:��a��b�ϲ�                      S a:�Ƴ�a��������Ĺ�ϵ(��a�����ļ����й�������)
Ȼ���������ж��ٸ�����

solve:
M���൱�ڲ��鼯�ĺϲ���������ɾ��a��ʱ��ά��ԭ�ȵĽṹ���䣬����ӳ�䵽����ĵ���
Ȼ������ж��ٸ����ڵ㼴��

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

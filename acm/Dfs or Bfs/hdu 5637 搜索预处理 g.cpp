/*
hdu 5637 ����Ԥ����

����n������Ȼ�����x�����ֲ�����
1.�ı�x�������е�һλ����1->0 or 0->1
2.��x��n�����е�t���õ� x^t
�����õ�y����С������

�ʼ�뵽���x^y�����ǲ�֪����ô�������ÿ��ѯ�ʶ�����һ�������Ļ��о�
��TLE,Ϊʲô��û�뵽Ԥ�������- -��

���⣺
�Ȱ��������ֲ����õ���������������Ȼ���x->yҲ���������(x^y)�������ֵ
����С�����Ѿ����������ֱ�ӽ���O(1)�Ĳ�ѯ����

hhh-2016-03-06 12:12:08
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
#define MID(a,b) (a+((b-a)>>1))
const int maxn=100500;
const int MOD = 1e9+7;

int a[maxn];
int step[maxn<<2];
int tp[maxn<<2];
int y,n;
int ans ;

void bfs()
{
    memset(step,-1,sizeof(step));
    int star = 0,tail = 0;
    tp[0] = 0,step[0] = 0;
    while(star <= tail)
    {
        int cur = tp[star];
        for(int i =1; i <= n;i++)
        {
            int t = cur^a[i];
            if(step[t] != -1)
                continue;
            tp[++tail] = t;
            step[t] = step[cur]+1;
        }
        for(int i =0;i <= 17;i++)
        {
            int t = cur^(1<<i);
            if(step[t] != -1)
                continue;
            tp[++tail] = t;
            step[t] = step[cur]+1;
        }
        star++;
    }
    return ;
}


int main()
{
    int t,q;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&q);
        for(int i =1; i <= n; i++)
        {
            scanf("%d",&a[i]);
        }
        bfs();
        int x,y;
        ll sum = 0;
        for(int i = 1;i <= q;i++)
        {
            scanf("%d%d",&x,&y);
            int ans = step[x^y];
            sum = (sum+(ll)(i*ans)%MOD)%MOD;
        }
        printf("%I64d\n",sum%MOD);

    }
    return 0;
}

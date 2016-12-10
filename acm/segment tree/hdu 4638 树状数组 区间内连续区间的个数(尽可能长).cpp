/*
hdu 4638 ��״���� ��������������ĸ���(�����ܳ�)

����n����,�����ѯ����[l,r]�����������ĸ�������������䳤��ƽ���ĺ�,
�������䳤��Խ��Խ��
3 1 2 5 4  ��[1,5]��:1,2,3,4,5   1��
           ��[2,4]��:1,2 �� 4    2��
�������ǰ�ÿ�������ɶ�����,��ÿ������ֵΪ1
���ڵ�ǰ���ֵ�a[i],���ǰ�������a[i-1],a[i+1]��ô�������һ��,��������
�Ǵ������ҵ��Ƴ�����,���Ա����ֵӦ���������ұ��Է����ѯ,�������ǰ�������
a[i-1],a[i+1].�������ǵ�λ����-1,ɾ�����ǵĶ���ֵ.

hhh-2016-04-04 17:05:44
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int mod = 10007;
const int maxn = 100050;

int s[maxn];
int a[maxn];
int p[maxn];
int ans[maxn];
struct node
{
    int l,r;
    int id;
} op[maxn];
int n,m;
bool cmp(node a,node b)
{
    return a.r < b.r;
}

int lowbit(int x)
{
    return x&(-x);
}

void add(int x,int val)
{
    while(x <= n)
    {
        s[x] += val;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int cnt = 0;
    while(x)
    {
        cnt += s[x];
        x -= lowbit(x);
    }
    return cnt;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(s,0,sizeof(s));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            p[a[i]] = i;
        }
        for(int i =0; i< m; i++)
        {
            scanf("%d%d",&op[i].l,&op[i].r);
            op[i].id = i;
        }
        sort(op,op+m,cmp);
        for(int i = 1,cur = 0; i <= n; i++)
        {
            add(i,1);
            if(a[i] > 1 && p[a[i]-1] < i)
                add(p[a[i]-1],-1);
            if(a[i] < n && p[a[i]+1] < i)
                add(p[a[i]+1],-1);

            while(i == op[cur].r && cur < m)
            {
                ans[op[cur].id] = sum(op[cur].r)-sum(op[cur].l-1);
                cur++;
            }
        }
        for(int i = 0; i < m; i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}

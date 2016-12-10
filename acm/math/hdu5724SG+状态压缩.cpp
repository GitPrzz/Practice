/*
hdu 5724 SG+״̬ѹ��

�о����ǲ��ģ����Һܾ���ǰ�Ϳ��˿�SG�����ǲ�û��ôϵͳ��ȥѧϰzzz��
���ȿ��԰�����n�п���n��ʯ�ԣ���1��ʾ�����ӣ�0��ʾû�еĻ����ܹ��ö����Ʊ�ʾ�����е�״̬��
1000100�������ת���� 0100100 1000010�ȵ�

Ȼ��������ù�ʽ���ÿ�������SG(ö�� 1~(1<<20))
�ó�ÿһ�е�״̬���㼴��

hhh-2016-08-01 17:28:17
ѧϰ��
//http://blog.csdn.net/luomingjun12315/article/details/45555495
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const ll mod = 1e9 + 7;
const ll INF = 0x3f3f3f3f;
const int maxn = 1000100;

int vis[22];
int sg[1<<20];

int SG(int cur)
{
    memset(vis,0,sizeof(vis));
    for(int i = 20; i >= 0; i--)
    {
        if(cur & (1<<i))
        {
            for(int j = i-1; j >= 0; j--)
            {
                if(!(cur & (1 << j)))
                {
                    int tmp = cur;
                    tmp ^= ((1<<i)^(1<<j));
                    vis[sg[tmp]] = true;
                    break;
                }
            }
        }
    }
    for(int i = 0 ; i <= 20; i++)
    {
        if(!vis[i])
            return i;
    }
    return 0;
}

int main()
{
    memset(sg,0,sizeof(sg));
    for(int i = 1; i < (1 << 20); i++)
        sg[i] = SG(i);
    int T,n,x;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int ans = 0;
        for(int i = 1;i <= n;i++)
        {
            int m,cur = 0;
            scanf("%d",&m);
            for(int j = 1;j <= m;j++)
            {
                scanf("%d",&x);
                cur |= 1 << (20-x);
            }
            ans ^= sg[cur];
        }
        if(ans )
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

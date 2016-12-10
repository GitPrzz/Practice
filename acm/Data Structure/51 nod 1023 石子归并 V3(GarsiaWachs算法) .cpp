/*
51 nod 1023 ʯ�ӹ鲢 V3(GarsiaWachs�㷨)

problem:
����n��ʯ��,�����������Ժϲ����������ǵĺ�. ���������С����

�ο�:
http://blog.sina.com.cn/s/blog_a825ada90101no1m.html
�ⲩ�ͽ��Ͳ���,���Բ��Ǻܶ�����㷨��ԭ�� T T.

hhh-2016/09/05-21:14:18
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
const int maxn = 50050;
const double PI = acos(-1.0);

ll t[maxn];
ll ans;
int num;
void dfs(int cur)
{
    ll tval = t[cur-1] + t[cur];
    ans = ans+(ll)tval;
    for(int i = cur;i < num-1;i++)
        t[i] = t[i+1];
    int k;
    num --;
    for(k = cur-1;k >= 1 && t[k-1] < tval;k--)
    {
        t[k] = t[k-1];
    }
    t[k] = tval;

    while(k >= 2 && t[k] >= t[k-2])
    {
        int len = num-k;
        dfs(k-1);
        k = num - len;

    }
}


int main(){
    int n;
    while(scanfi(n)!=EOF){
//    clr(t,inf);
    for(int i =0 ;i < n;i++)
        scanfi(t[i]);
    ans = 0;
    num = 1;
    for(int i =1;i < n;i++)
    {
        t[num ++ ] = t[i];
        while(num >= 3 &&  t[num-3] <= t[num-1])
            dfs(num-2);
    }
    while(num > 1) dfs(num-1);
    printf("%I64d\n",ans);
    }
    return 0;
}

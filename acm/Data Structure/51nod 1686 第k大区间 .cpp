/*
51nod 1686 ��k������

����һ�������ֵΪ���������ֵĴ�����
�ָ���n�����������������ֵ����󣬵�K���ֵΪ���١�

�о�һ�������ⶼ���Կ��� ���� + check.�о�ֱ����𰸺��鷳.������� ��������Ҫ����
�ж��ٸ��������������ö��ֵx. ö�������ҵ�r,�ҵ�һ��������lʹ [l,r]֮����x���ظ�ֵ

��ôl��l֮ǰ��ֵ��r�������䶼�������һ����x���ظ�ֵ�����䡣
������vec��¼һ������ֵ���ֵ�λ��,�ж�һ�¼���. �������ܴ���������ɢ������һ�¡�

hhh-2016/05/29 18:08:02
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <cmath>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
using namespace std;
const int maxn = 100100;
const double PI = 3.1415926;
const double eps = 1e-6;
int a[maxn];
int b[maxn];
int n;
ll k;
int tn;
int tha[maxn];

vector<int> vec[maxn];

bool cal(int x)
{
    if(x == 1)
        return (n*(n-1)/2) >= k;
    for(int i = 1; i <= n; i++)
    {
        vec[i].clear();
    }
    memset(tha,0,sizeof(tha));
    ll len = 0;
    ll ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ll t = 0;
        if( tha[a[i]] >= x-1)
        {
            t = vec[a[i]][tha[a[i]]-x+1];
        }
        len = max(len,t);
        ans = (ll)(ans+len);
        vec[a[i]].push_back(i);
        tha[a[i]] ++ ;
    }
    return ans >= k;
}

int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d%I64d",&n,&k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d",&a[i]);
        b[i] = a[i];
    }
    sort(b+1,b+1+n);
    tn = unique(b+1,b+n+1)-b-1;
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(b+1,b+1+tn,a[i])-b;
    int l = 1,r = n;
    int ans = 1;
    while(l <= r)
    {
        int mid = (l+r) >>1;
        if(cal(mid))
        {
            l = mid+1;
            ans = mid;
        }
        else
            r = mid-1;
    }
    printf("%d\n",ans);
    return 0;
}

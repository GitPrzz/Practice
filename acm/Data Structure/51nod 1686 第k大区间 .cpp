/*
51nod 1686 第k大区间

定义一个区间的值为其众数出现的次数。
现给出n个数，求将所有区间的值排序后，第K大的值为多少。

感觉一般这种题都可以考虑 二分 + check.感觉直接求答案很麻烦.如果二分 我们则需要考虑
有多少个区间的众数大于枚举值x. 枚举区间右点r,找到一个最靠的左点l使 [l,r]之间有x个重复值

那么l及l之前的值与r构成区间都可以组成一个有x个重复值的区间。
所以用vec记录一个各个值出现的位置,判断一下即可. 但是数很大，所以用离散化处理一下。

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

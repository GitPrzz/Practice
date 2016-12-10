/*
51nod 平均数

题目：给你n个数，可以知道总共可以组成 (n+1)*n/2 个区间，那么请问这些区间中第k大的平均值
最开始是一点思路都没有，后来看到一个有点相似的题目，发现我们可以吧问题转换成 平均值大于
x的区间有多少个

这样就可以通过枚举答案，然后通过判断解决。用f[i]表示前i个数的和，那么：
Ave = (f[r]-f[l])/(r-l)    所以Ave >= x  --->  f[r]-rx >= f[l]-lx即前面出现的比当前值小的个数
但是发现 f[r]-rx 可以达到-10^10，而且是浮点型。于是又纠结了很久，一开始也想到了离散化(但总觉得会超时Orz)
结果发现的确是自己想太多，利用sort,每次查找当前值是第几个,然后利用树状数组维护即可。

hhh 2016/05/28 16:22:06
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
const int maxn = 101010;
const double PI = 3.1415926;
const double eps = 1e-6;
double a[maxn];
ll s[maxn];
double f[maxn];
double g[maxn];
int n;
ll k;

void add(int x,int val)
{
    while(x <= 100000)
    {
        s[x] += val;
        x += (x&(-x));
    }
}

ll sum(int pos)
{
    ll ans = 0;
    while(pos > 0)
    {
        ans += s[pos];
        pos -= (pos&(-pos));
    }
    return ans;
}

bool cal(double x)
{
    memset(s,0,sizeof(s));
    f[0] = 0;
    for(int i = 1; i <= n; i++)
        f[i] = f[i-1] + a[i];
    ll num = 0;
    for(int i = 1; i <= n; i++)
    {
        f[i] -= (double)i*x;
        g[i] = f[i];
        if(f[i] > 0)
            num ++;
    }
    sort(g+1,g+n+1);

//    for(int i = 1;i <= n;i++)
//        cout << g[i] <<" ";
//    cout << endl;
    for(int i = 1; i <= n; i++)
    {
        int pla = lower_bound(g+1,g+n+1,f[i])-g;
        num += sum(pla);
        add(pla,1);
    }
    if(num >= k)
        return true;
    else
        return false;
}

int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d",&n);
    scanf("%lld",&k);
    double Max = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%lf",&a[i]);
        Max = max(a[i],Max);
    }
    double l = 0;
    double r = Max;
    while( r - l > eps)
    {
        double mid = (l+r)/2;
        if(cal(mid))
            l = mid;
        else
            r = mid-eps;
    }
    printf("%f\n",l);
    return 0;
}

/*
hdu 4279 数论经典题
表示并没能想出，考虑过欧拉+质数分解但是感觉不合适
后来参考ACdreamers发现转换很奇妙
首先f[i]表示小于i中 不与i互质且不整除i的数的个数.
然后求区间[a,b]中f[i]为奇的数的个数

f[i]便表示成 i-互质的数-约数+1 (因为1被减了两次)

这里用到一个结论：欧拉函数在n>2时，值都为偶数。
约数则是(质数的幂+1)的累乘.如果要累积为奇，则质数分解的幂全为偶数，即一个平方数

若是平方数： f[i] = x - 奇 - 偶 - 1；
若是非blabla：f[i] = x - 偶 - 偶 - 1；
综上：我们需要奇数平方数和偶数非平方数
即 偶数个数-偶数^2的个数+奇数^2的个数。
而偶数个数为 x/2-1，-1是为了把2减掉。偶数^2个数为 sqrt(x)/2，
奇数^2个数为 ( sqrt(x)-(sqrt(x)/2) )-1，这里-1是为了把1减掉。

所以，化简后，F(x)=x/2-1+(sqrt(x)%2? 0:-1).

hhh-2016-02-20 03:33:40
*/

#include <functional>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long  double ld;

ll solve(ll x)
{
    if(x < 6)
        return 0;
    ll t1 = x/2-1;  //偶数个数
//    ll t2 = sqrt(x)/2; //偶数平方数
//    ll t3 = sqrt(x)-sqrt(x)/2-1; //奇数平方数
//    cout << sqrt(x) << endl;
    ll ans = 0;
    ld t = x;
    if((ll)sqrt(t)%2 == 0) ans++;
    return t1 - ans;
}
int main()
{
    ll a,b;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d",&a,&b);
        printf("%I64d\n",solve(b)-solve(a-1));
    }
    return 0;
}


/*
Codeforces 651A - Joysticks
Ä£ÄâÌâ
hhh-2016-03-07 12:57:56
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lson (i<<1)
#define rson ((i<<1)|1)
const int maxn = 300010;


int main()
{
    int T,n,m;
    int a,b;
    while(scanf("%d%d",&a,&b) != EOF)
    {
        int ans = 0;
        while(a > 0 && b > 0)
        {
            if(a <= 1 && b <= 1)
                break;
            if(a < b) swap(a,b);
            a -= 2;
            b += 1;
            if(b > 100) b = 100;
            ans ++;

        }
        cout<<ans<<endl;
    }
    return 0;
}

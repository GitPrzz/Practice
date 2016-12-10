
/*
Codeforces 651B - Beautiful Paintings
Ä£ÄâÌâ
hhh-2016-03-07 13:21:46
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
const int maxn = 10010;

int a[maxn];
int vis[maxn];


int main()
{
    int T,n,m;
    while(scanf("%d",&n) != EOF)
    {
        memset(vis,0,sizeof(vis));
        for(int i = 1; i <= n; i++)
        {
            scanf("%d",&a[i]);
            vis[a[i]]++;
        }
        int tx;
        int num,ans= 0;
        sort(a+1,a+n+1);
        while(1)
        {
            tx = -1;
            num = 0;
            for(int i =1; i <= n; i++)
            {
                if(vis[a[i]] && a[i] > tx)
                {
                    num++;
                    tx = a[i];
                    vis[a[i]] -= 1;
                }
            }
            if(!num)
                break;
            else
                ans += num-1;
        }
        cout <<ans<<endl;
    }
    return 0;
}

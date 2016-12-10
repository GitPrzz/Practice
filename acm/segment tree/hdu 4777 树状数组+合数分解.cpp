/*
hdu 4777 树状数组+合数分解

给你n个数，然后是q个询问，每次[l,r]中与区间内其它所有数互质的数的个数

感觉有点像查找区间内不同数的个数，于是用了l[i]表示左边最近与它不互质的数的
位置，本来想到是只要有互质的 就表为1，但是区间查询出现了问题(与i不互质的
l[i]如果不在区间内，i仍然被标记为1，- -2了)。

当遇到i时，只有当l[i]也在区间中的时候才能算，所以在l[i]上加1。当遇到r[i]时，就算没有l[i]
i也有r[i],所有l[i]减1，i上加1.
至于r[i]本身，已经被加到l[r[i]]上去了

所以大致思路就是：
先处理出l[i]和r[i](可以考虑求出质因子然后判断).
然后把查询按照r的从小到大排序，有点像往后递推的感觉
最后按照上面的思路求出区间[l,r]中不与其它互质的个数，再减去即可

//表示一直没看懂别人的报告(主要是不理解为什么这样插入删除)，这还是偶然间想通的QAQ

hhh-2016-03-06 14:01:51
*/
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <vector>
#include <functional>
#define lson (i<<1)
#define rson ((i<<1)|1)
using namespace std;
typedef long long ll;
const int maxn = 200050;
int vis[maxn];
const int inf = 0x3f3f3f3f;
int prime[maxn+1],factor[maxn],s[maxn];
int n,q;
void get_prime()
{
    memset(prime,0,sizeof(prime));
    for(int i =2 ; i <= maxn; i++)
    {
        if(!prime[i])
            prime[++prime[0]] = i;
        for(int j = 1; j <= prime[0] && prime[j] <= maxn/i; j++)
        {
            prime[i*prime[j]] = 1;
            if(i % prime[j] == 0)break;
        }
    }
}
int facnt;
int getFactor(int x)
{
    facnt = 0;
    int tmp = x;
    for(int i = 1; prime[i] <= tmp/prime[i]; i++)
    {
        if(tmp % prime[i] == 0)
        {
            factor[facnt]= prime[i];
            while(tmp%prime[i] == 0)
            {
                tmp/=prime[i];
            }
            facnt ++;
        }
    }
    if(tmp != 1)
    {
        factor[facnt++] = tmp;
    }
}

int lowbit(int x)
{
    return x&(-x);
}

void add(int x,int val)
{
    if(x == 0) return ;
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

int t[maxn];
int l[maxn],r[maxn];
int ans[maxn],a[maxn];

struct node
{
    int l,r;
    int id;
} opr[maxn];

bool cmp(node a,node b)
{
    return a.r < b.r;
}
vector<int>c[maxn];
int main()
{
    int T;
    int cas = 1;
    get_prime();
    while(scanf("%d%d",&n,&q) != EOF)
    {
        memset(s,0,sizeof(s));

        if(n == 0 && q == 0)
            break;
        for(int i =1; i <= n; i++)
            scanf("%d",&a[i]);

        for(int i =1; i <= q; i++)
        {
            scanf("%d%d",&opr[i].l,&opr[i].r);
            opr[i].id = i;
        }

        memset(t,0,sizeof(t));
        for(int i =1; i <= n; i++)
        {
            l[i] = 0;
            getFactor(a[i]);
            for(int j = 0; j < facnt; j++)
            {
                l[i] = max(l[i],t[factor[j]]);
                t[factor[j]] = i;
            }
        }
        for(int i =0 ; i < maxn; i++) t[i] = n+1;
        for(int i =n; i >= 1 ; i--)
        {
            r[i] = n+1;
            getFactor(a[i]);
            for(int j = 0; j < facnt; j++)
            {
                r[i] = min(r[i],t[factor[j]]);
                t[factor[j]] = i;
            }
        }
        for(int i = 0; i <= n+2; i++)
        {
            c[i].clear();
        }
        for(int i = 1; i <= n; i++)
            c[r[i]].push_back(i);
        //memset(vis,0,sizeof(vis));

        sort(opr+1,opr+q+1,cmp);
        for(int i = 1,k = 1; i <= q; i++)
        {
            while(k <= n && k <= opr[i].r)
            {
                add(l[k],1);
                for(int o = 0; o < c[k].size(); o++)
                {
                    int v = c[k][o];
                    add(v,1);
                    add(l[v],-1);
                }
                k++;
            }
            ans[opr[i].id] = opr[i].r-opr[i].l+1-(sum(opr[i].r)-sum(opr[i].l-1));
        }
        for(int i =1; i <= q; i++)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}


/*
input:
3 2
2 1 4
1 2
1 3
6 4
3 6 1 2 5 3
1 3
4 6
4 4
2 6
0 0

output:
2
1
1
3
1
2
*/

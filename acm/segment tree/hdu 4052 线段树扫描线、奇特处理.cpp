/*
hdu 4052 线段树扫描线、奇特处理

给你W*H大小的矩形，其中有N个地区不能使用(给出了这个地区的两个顶点的坐标即(x1,y1)
和(x2,y2))，问能下多少个1*M的矩形。

但是看见题目有想到了扫描线,但是一直不知道应该怎么处理后来偶然看见别人提示可以转换
成求面积,大致就有了思路

假设1*n的矩阵中放入1*m的矩阵,能有多少种?    n-m+1
我们扫描每一列,两个相邻为n的旧机器中就能放下n-m+1个新机器,于是原先的旧机器矩形
就变成了(x1,y1,x2+ma-1,y2)(从下往上扫描)
        (x1,y1,x2,y2+ma-1)(从左往右扫描)
而剩下的为被占据的位置就是方案数了
因为我是在每个旧机器往右边添加的,所以还要解决这一列没有从1开始的情况,所以在最左边
加上(1,1,ma,h+1)的矩阵
而且ma=1时,横着放和竖着放是一样的,所以除以2

但是第一个版本写出来一直 RuntimeError
后来实在没法又换了个,把离散化用vec处理终于出现了WR(TAT)
主要是 ma == 1 情况,因为我会在1添加一个矩阵,但是当ma==1时这个矩阵也被建立了就导致
(1,1,1,h+1) 由于是按边建树l=x1,r=x2-1 -> r<l (- -！好气)  //应该多测几次的

然后进行了特判第一个也过了

hhh-2016-03-30 22:26:25
*/


//Second
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <functional>
#include <map>
#include <algorithm>
#include <queue>
#include <vector>
#define lson (i<<1)
#define rson ((i<<1)|1)
typedef long long ll;
using namespace std;

const int maxn = 1000005;
vector<int> vec;
int w,h;
int x[maxn],y[maxn],tx[maxn],ty[maxn];
map<int,int > mp;
int n,ma;
struct node
{
    int l,r;
    int sum;
    ll len;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];

void push_up(int i)
{
    if(tree[i].sum)
        tree[i].len = vec[tree[i].r+1]-vec[tree[i].l];
    else if(tree[i].l == tree[i].r)
        tree[i].len = 0;
    else
        tree[i].len = tree[lson].len+tree[rson].len;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].sum = tree[i].len = 0;
    if(l == r)
        return;
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].sum += val;
        push_up(i);
        return ;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
    return ;
}

struct edge
{
    int l,r;
    int high;
    int va;
};
edge Line[maxn<<2];
int m;
bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}

int tox;
ll ans;
void solve(int cur,int hi,int wi)
{
    vec.clear();
    if(cur)
    {
        for(int i =1; i <= n; i++)
            swap(x[i],y[i]),swap(tx[i],ty[i]);
    }
    tox = 0;
    for(int i = 1; i <= n; i++)
    {
        int t = min(wi+1,tx[i]+ma-1);
        Line[tox].l = x[i],Line[tox].r =t,Line[tox].high = y[i],Line[tox++].va = 1;
        Line[tox].l = x[i],Line[tox].r =t,Line[tox].high = ty[i],Line[tox++].va = -1;
        vec.push_back(x[i]);
        vec.push_back(t);
    }
    if(ma != 1)
    {
        Line[tox].l = 1,Line[tox].r = ma,Line[tox].high=1,Line[tox++].va=1;
        Line[tox].l = 1,Line[tox].r = ma,Line[tox].high=hi+1,Line[tox++].va=-1;
        vec.push_back(1),vec.push_back(ma);
    }
    sort(Line,Line+tox,cmp);
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    int m = vec.size();
    for(int i = 0; i < m; i++)
        mp[vec[i]] = i;
    build(1,0,m);
    int l,r;
    for(int i = 0; i < tox-1; i++)
    {
        l = mp[Line[i].l];
        r = mp[Line[i].r]-1;
        if(r < l)
            continue;
        Insert(1,l,r,Line[i].va);
        ans -= (ll)tree[1].len*(Line[i+1].high-Line[i].high);
    }
    //cout << tans <<endl;
}

int main()
{
    while(scanf("%d%d%d%d",&w,&h,&n,&ma) != EOF)
    {
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d%d%d",&x[i],&y[i],&tx[i],&ty[i]);
            tx[i]++,ty[i]++;
        }

        ans =(ll)w*h*2;
        solve(0,h,w);
        solve(1,w,h);
        if(ma == 1)
            ans /= 2;
        printf("%I64d\n",ans);
    }
    return 0;
}


/*
First：

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <functional>
#include <map>
#include <algorithm>
#include <queue>

#define lson (i<<1)
#define rson ((i<<1)|1)
typedef long long ll;
using namespace std;

const int maxn = 1000005;

ll w,h;
int n,ma;
int now;
struct node
{
    int l,r;
    int sum;
    ll len;
    int mid()
    {
        return (l+r)>>1;
    }
} tree[maxn<<2];
ll hs[2][maxn];

void push_up(int i)
{
    if(tree[i].sum)
        tree[i].len = hs[now][tree[i].r+1]-hs[now][tree[i].l];
    else if(tree[i].l == tree[i].r)
        tree[i].len = 0;
    else
        tree[i].len = tree[lson].len+tree[rson].len;
}

void build(int i,int l,int r)
{
    tree[i].l = l,tree[i].r = r;
    tree[i].sum = tree[i].len = 0;
    if(l == r)
        return;
    build(lson,l,tree[i].mid());
    build(rson,tree[i].mid()+1,r);
    push_up(i);
}

void push_down(int i)
{

}

void Insert(int i,int l,int r,int val)
{
    if(tree[i].l >= l && tree[i].r <= r)
    {
        tree[i].sum += val;
        push_up(i);
        return ;
    }
    int mid = tree[i].mid();
    push_down(i);
    if(l <= mid)
        Insert(lson,l,r,val);
    if(r > mid)
        Insert(rson,l,r,val);
    push_up(i);
    return ;
}

struct edge
{
    ll l,r;
    ll high;
    int va;
};
edge tx[maxn<<2];
edge ty[maxn<<2];
int m;
bool cmp(edge a,edge b)
{
    if(a.high != b.high)
        return a.high < b.high;
    else
        return a.va > b.va;
}
int bin(int cur,ll x)
{
    int l = 0,r = m-1;
    while(l <= r)
    {
        int mid = (l+r)>>1;
        if(hs[cur][mid] == x)
            return mid;
        else if(hs[cur][mid] < x)
            l = mid+1;
        else
            r = mid-1;
    }
}
int tox,toy;
ll solve(int cur)
{
    now = cur;
    int len = (cur == 0 ? tox:toy);
    m = 1;
    for(int i = 1; i < len; i++) //ШЅжи
    {
        if(hs[cur][i] != hs[cur][i-1])
            hs[cur][m++] = hs[cur][i];
    }
//    for(int i = 0;i < m;i++)
//        printf("%d ",hs[cur][i]);
//    cout <<endl;
    build(1,0,m);
    ll tans = 0;
    int l,r;
    for(int i = 0; i < len-1; i++)
    {
        if(cur == 0)
        {
            l = bin(cur,tx[i].l);
            r = bin(cur,tx[i].r)-1;
            Insert(1,l,r,tx[i].va);
            tans += (ll)tree[1].len*(tx[i+1].high-tx[i].high);
        }
        else
        {
            l = bin(cur,ty[i].l);
            r = bin(cur,ty[i].r)-1;
            if(r < l )continue;
            Insert(1,l,r,ty[i].va);
            tans += (ll)tree[1].len*(ty[i+1].high-ty[i].high);
        }

        //cout << tree[i].len << endl;
        //cout << tans <<endl;

    }
    //cout << tans <<endl;
    return tans;
}

int main()
{
    while(scanf("%I64d%I64d%d%d",&w,&h,&n,&ma) != EOF)
    {
        tox = 0,toy = 0;
        ll x1,y1,x2,y2;
        for(int i = 1; i <= n; i++)
        {
            scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
            x2++,y2++;
            ll t1 = (x2+ma-1)>w+1? w+1:x2+ma-1;
            tx[tox].l = x1,tx[tox].r = t1,tx[tox].high = y1,tx[tox].va = 1;
            hs[0][tox++] = x1;
            tx[tox].l = x1,tx[tox].r = t1,tx[tox].high = y2,tx[tox].va = -1;
            hs[0][tox++] = t1;

            t1 = (y2+ma-1)>h+1? h+1:y2+ma-1;
            ty[toy].l = y1,ty[toy].r = t1,ty[toy].high = x1,ty[toy].va = 1;
            hs[1][toy++] = y1;
            ty[toy].l = y1,ty[toy].r = t1,ty[toy].high = x2,ty[toy].va = -1;
            hs[1][toy++] = t1;
        }
        if(ma != 1){
        tx[tox].l = 1,tx[tox].r = ma,ty[toy].l=1,ty[toy].r = ma;
        tx[tox].high=1,tx[tox].va=1,ty[toy].high=1,ty[toy].va=1;
        hs[0][tox++] = 1,hs[1][toy++]=1;

        tx[tox].l = 1,tx[tox].r = ma,ty[toy].l=1,ty[toy].r = ma;
        tx[tox].high=h+1,tx[tox].va=-1,ty[toy].high=w+1,ty[toy].va=-1;
        hs[0][tox++] = ma,hs[1][toy++] = ma;
        }
        sort(hs[0],hs[0]+tox);
        sort(hs[1],hs[1]+toy);
        sort(tx,tx+tox,cmp);
        sort(ty,ty+toy,cmp);
        ll ans = w*h*2;

        ans -= solve(0);
        //printf("%I64d\n",ans);
        ans -= solve(1);
        if(ma == 1)
            ans /= 2;
        printf("%I64d\n",ans);
    }
    return 0;
}


*/

/*
51nod ƽ����

��Ŀ������n����������֪���ܹ�������� (n+1)*n/2 �����䣬��ô������Щ�����е�k���ƽ��ֵ
�ʼ��һ��˼·��û�У���������һ���е����Ƶ���Ŀ���������ǿ��԰�����ת���� ƽ��ֵ����
x�������ж��ٸ�

�����Ϳ���ͨ��ö�ٴ𰸣�Ȼ��ͨ���жϽ������f[i]��ʾǰi�����ĺͣ���ô��
Ave = (f[r]-f[l])/(r-l)    ����Ave >= x  --->  f[r]-rx >= f[l]-lx��ǰ����ֵıȵ�ǰֵС�ĸ���
���Ƿ��� f[r]-rx ���Դﵽ-10^10�������Ǹ����͡������־����˺ܾã�һ��ʼҲ�뵽����ɢ��(���ܾ��ûᳬʱOrz)
������ֵ�ȷ���Լ���̫�࣬����sort,ÿ�β��ҵ�ǰֵ�ǵڼ���,Ȼ��������״����ά�����ɡ�

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

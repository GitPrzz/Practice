/*
51nod 1035�����ѭ����

����һ��n,��1~n�� 1/i��ѭ���������һ����
���ݱȽ�С�����������ֱ��ģ��������㡣���ǲ�֪����ô�ж� 1/6 = 0.1666666���� �Լ���ô�ж�
ģ���Ƿ�Ӧ��ֹͣ��
����������Ŀ���Ե�Ч������С��kʹ 10^k%n == 1������ѭ���ڵĳ��ȿ϶�С�ڵ��� euler(n)��
����1/6������Ҳο����˵��� �Ȱ�10�����ӳ�ȥ,Ȼ���ٽ��м��㣬�о����Ǻܶ���

hhh - 2016/05/29 16:24:42
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
const int maxn = 1010100;
const double PI = 3.1415926;
const double eps = 1e-6;

int len[1010];

int gcd(int a,int b)
{
    while(a % b != 0)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return b;
}

void ini()
{
    memset(len,0,sizeof(len));
    for(int i = 1;i <= 1000;i++)
    {
        int now = i;
        while(now % 2 == 0)
            now /= 2;
        while(now % 5 == 0)
            now /= 5;
        int t = 1;
        for(int h = 1;h <= now;h++)
        {
            t *= 10;
            t %= now;
            if(t == 1)
            {
                len[i] = h;
                break;
            }
        }
    }
}

int read(){
	int ans=0;
	char last=' ',ch=getchar();
	while(ch<'0' || ch>'9')last=ch,ch=getchar();
	while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
	if(last=='-')ans=-ans;
	return ans;
}


int main()
{
    ini();
    int ans ;
    int Max= 0 ;
    int n = read();
    for(int i = 1;i <= n;i++)
    {
       // cout << len[i] << " ";
        if(len[i] > Max)
        {
            ans = i;
            Max = len[i];
        }
    }
    //cout <<endl;
    printf("%d\n",ans);
    return 0;
}

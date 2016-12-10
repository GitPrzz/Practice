/*
51nod 1035：最长的循环节

给你一个n,求1~n中 1/i的循环节最长是哪一个数
数据比较小，所以想的是直接模拟除法运算。但是不知道怎么判断 1/6 = 0.1666666这种 以及怎么判断
模拟是否应该停止。
后来发现题目可以等效于求最小的k使 10^k%n == 1，所以循环节的长度肯定小于等于 euler(n)。
至于1/6这个，我参考别人的是 先把10的因子除去,然后再进行计算，感觉不是很懂。

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

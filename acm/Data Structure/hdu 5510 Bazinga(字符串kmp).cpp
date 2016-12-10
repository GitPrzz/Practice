/*
hdu 5510 Bazinga(�ַ���kmp)

problem:
����n���ַ���,��һ���������i. ʹ1~i-1���ַ�������һ������str[i]���Ӵ�

solve:
�ʼ����������ֵ���.���Ǹо����鷳,Ŀ��ᳬʱ.
Ȼ�������kmp,�����Ż�������.  ÿ�ε�����ǰ��,��������1~i-1�����ж���i���Ӵ�. ��ô������iʱ�Ϳ���ֱ�ӷ���true.
�����ƥ����˳�,�����һֱ������ȥ. ���TLE��....�ܱ���

����������ȷ�Ż�:���i��k���Ӵ�. ��ôƥ���ʱ��Ͳ���Ҫƥ��i,��Ϊ�����ǰ��kƥ��,��ô��һ����iƥ��....
���Թ����б��һ�²���ƥ��ľ�����
hhh-2016-08-29 21:00:19
*/
#pragma comment(linker,"/STACK:124000000,124000000")
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
#include <map>
#define lson  i<<1
#define rson  i<<1|1
#define ll long long
#define clr(a,b) memset(a,b,sizeof(a))
#define scanfi(a) scanf("%d",&a)
#define scanfs(a) scanf("%s",a)
#define scanfl(a) scanf("%I64d",&a)
#define key_val ch[ch[root][1]][0]
#define inf 1e9
using namespace std;
const ll mod = 1e9+7;
const int maxn = 2005;
char str[505][2004];
int flag[maxn];
void pre_kmp(char x[],int m,int kmpnext[])
{
    int i,j;
    j = kmpnext[0] = -1;
    i = 0;
    while(i < m)
    {
        while(j != -1 && x[i] != x[j])
            j = kmpnext[j];
        if(x[++i] == x[++j])
            kmpnext[i] = kmpnext[j];
        else
            kmpnext[i] = j;
    }
}
int nex[2005];
int kmp(char x[],char y[])
{
    int m = strlen(x);
    int n = strlen(y);
    int i,j;
    clr(nex,0);
    pre_kmp(x,m,nex);
    i = j = 0;

    while(i < n)
    {
        while(j != -1 && y[i] != x[j]) j = nex[j];
        i++,j++;
        if(j >= m)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int T,n;
//    freopen("in.txt","r",stdin);
    scanfi(T);
    int cas = 1;
    while(T--)
    {
        clr(flag,0);
        scanfi(n);
        int ans = -1;
        for(int i = 1; i <= n; i++)
        {
            scanfs(str[i]);
            for(int j =1;j < i;j++)
            {
                if(flag[j])
                    continue;
                if(kmp(str[j],str[i]))
                    flag[j] = 1;
                else
                {
                    ans = i;
                }
            }
        }
        printf("Case #%d: %d\n",cas++,ans);
    }
    return 0;
}

/*
hdu 5512
�����һ��Ϊ1�����������ʣ���ôȫ�����ޡ�
��������ʣ�n/(gcd(a��b))
1��n������Yuwgna��Iaka���˴�a��b���㿪ʼ�޽�����ÿ�ο����޽�����λ��i=j+k��i=j-k��
j��kΪ���޽��õ�����λ�ã�Yuwgna��ʼ�ޣ����˭��������˭�����ˣ������˭Ӯ��
hhh-2016-02-19 18:19:36
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

const int maxn = 20005;

int gcd(int a,int b)
{
    while(a % b!=0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return b;
}

int main()
{
    int T,n,a,b;
    scanf("%d",&T);
    int cas = 1;
    while(T--)
    {

        scanf("%d%d%d",&n,&a,&b);
        printf("Case #%d: ",cas++);
        int flag;
        if(a == 1 || b == 1 || gcd(a,b) == 1)
        {
            if(n%2)
                flag = 1;
            else
                flag = 0;
        }
        else
        {
            int t = gcd(a,b);
            if(n/t % 2)
                flag = 1;
            else
                flag = 0;
            //printf("gcd:%d\n",t);
        }
        if(flag)
            printf("Yuwgna\n");
        else
            printf("Iaka\n");
    }
    return 0;
}

/*
hdu 4279 ���۾�����
��ʾ��û����������ǹ�ŷ��+�����ֽ⵫�Ǹо�������
�����ο�ACdreamers����ת��������
����f[i]��ʾС��i�� ����i�����Ҳ�����i�����ĸ���.
Ȼ��������[a,b]��f[i]Ϊ������ĸ���

f[i]���ʾ�� i-���ʵ���-Լ��+1 (��Ϊ1����������)

�����õ�һ�����ۣ�ŷ��������n>2ʱ��ֵ��Ϊż����
Լ������(��������+1)���۳�.���Ҫ�ۻ�Ϊ�棬�������ֽ����ȫΪż������һ��ƽ����

����ƽ������ f[i] = x - �� - ż - 1��
���Ƿ�blabla��f[i] = x - ż - ż - 1��
���ϣ�������Ҫ����ƽ������ż����ƽ����
�� ż������-ż��^2�ĸ���+����^2�ĸ�����
��ż������Ϊ x/2-1��-1��Ϊ�˰�2������ż��^2����Ϊ sqrt(x)/2��
����^2����Ϊ ( sqrt(x)-(sqrt(x)/2) )-1������-1��Ϊ�˰�1������

���ԣ������F(x)=x/2-1+(sqrt(x)%2? 0:-1).

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
    ll t1 = x/2-1;  //ż������
//    ll t2 = sqrt(x)/2; //ż��ƽ����
//    ll t3 = sqrt(x)-sqrt(x)/2-1; //����ƽ����
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

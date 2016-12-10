/*
51nod 1092 �����ַ���

����һ���ַ���,����������Ӷ��ٸ���ĸ�ܹ�ʹ���Գơ�

���ʹ���Գ�,���Կ��Կ��� ���һ����ĸ��Ч��ɾ����Ӧ����ĸ�����Ǿͳ���,����ɾ��
���ٸ���ĸ����ʣ�µĴ��ǶԳƵġ����൱��������ַ�������ĶԳƴ��ĳ��ȣ����������
����������У���Ȼ�����ܳ��ȼ�ȥ���ɡ�

hhh-2016/05/27  10:25:36
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
const int maxn = 1040;
string str1;
string str2;
int dp[maxn][maxn];

int main()
{
    cin >> str1;

    str2 = str1;
    memset(dp,0,sizeof(dp));
    int len = str1.length();
    reverse(str2.begin(),str2.end());
    for(int i = 0;i < len;i++)
    {
        for(int j = 0;j < len;j++)
        {
            if(str1[i] == str2[j])
                dp[i+1][j+1] = max(dp[i][j]+1,max(dp[i][j+1],dp[i+1][j]));
            else
                dp[i+1][j+1] = max(dp[i][j],max(dp[i+1][j],dp[i][j+1]));
        }
    }
    printf("%d\n",len-dp[len][len]);
}

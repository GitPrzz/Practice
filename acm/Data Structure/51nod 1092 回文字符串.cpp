/*
51nod 1092 回文字符串

给你一个字符串,请问最少添加多少个字母能够使它对称。

最后使它对称,所以可以考虑 添加一个字母等效于删除对应的字母。于是就成了,最少删除
多少个字母后它剩下的串是对称的。就相当于求这个字符串中最长的对称串的长度（倒过来求个
最长公共子序列），然后用总长度减去即可。

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

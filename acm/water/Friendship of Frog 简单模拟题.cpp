/*
Friendship of Frog ¼òµ¥Ä£ÄâÌâ
hhh-2016-02-24 17:35:13
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
const int maxn = 1e5+10;

char str[maxn];
map<char,int> mp;
int main()
{
    int T,cas =1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",str);
        int len = strlen(str);
        int ans = 0x3f3f3f3f;
        mp.clear();
        for(int i = 0; i < len; i++)
        {
            if(mp.find(str[i]) == mp.end())
                mp[str[i]] = i;
            else
            {
                ans = min(ans,i - mp[str[i]]);
                mp[str[i]] = i;
            }
        }
        if(ans == 0x3f3f3f3f)
            ans = -1;
        printf("Case #%d: %d\n",cas++,ans);
    }
    return 0;
}

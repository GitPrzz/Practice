/*
hdu5652 India and China Origins(并查集)

给你一个棋盘形状的东东,上面1代表无法越过的山峰,0代表可以通过的平原.
而且在接下来q次会出现一些山峰,问多少次后棋盘上下不连通
如果一直联通则输出-1

开始想到了并查集但是实现起来有点问题,每次插入后都要把最左边一列判断
一下,看他们的父亲是否是棋盘的最右端.感觉并不够简便
然后参考了下大神们的代码,发现可以在合并的时候记录下这个联通量最左边
和最右边的位置,这样每次合并时只需要判断max-min是否等于棋盘的宽度就
好了
果然自己太死板了TAT

hhh-2016-03-27 12:42:45
*/

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
#define lson  (i<<1)
#define rson  ((i<<1)|1)
typedef long long ll;
const int maxn = 505 ;
int from = 500*500;
int to = 500*500+1;
int n,m;
int dir[9][2] = {{1,1},{1,0},{0,1},{1,-1},{0,-1},{-1,1},{-1,-1},{-1,0}};
char str[maxn];
int far[maxn*maxn];
int tmap[maxn][maxn];
int l[maxn*maxn],r[maxn*maxn];

int fin(int x)
{
    return x == far[x]?  x : far[x] = fin(far[x]);
}

bool  unio(int a,int b)
{
    int ta = fin(a);
    int tb = fin(b);
    if(ta != tb)
    {
        far[ta] = tb;
        l[tb] = min(l[ta],l[tb]);
        r[tb] = max(r[ta],r[tb]);
        if(r[tb] - l[tb] == m-1)
            return 1;
    }
    return 0;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i = 0; i < n; i++)
        {
            scanf("%s",str);
            for(int j = 0; j < m; j++)
            {
                tmap[i][j] = str[j]-'0';
                far[i*m+j] = i*m+j;
            }
        }

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
                //if(tmap[i][j])
                {
                    l[i*m+j] = j;
                    r[i*m+j] = j;
                }
        }
        int flag =0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(tmap[i][j])
                {
                    for(int k = 0; k < 8; k++)
                    {
                        int tx = i + dir[k][0];
                        int ty = j + dir[k][1];
                        if(tx < 0 || tx >= n || ty < 0 || ty >= m || !tmap[tx][ty])
                            continue;
                        if(unio(i*m+j,tx*m+ty))
                            flag = 1;
                    }

                }
            }
        }
        if(flag)
            printf("0\n");
        int q;
        scanf("%d",&q);
        for(int i = 0; i < q; i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            tmap[x][y] = 1;
            if(flag)
                continue;
            for(int k = 0; k < 8; k++)
            {
                int tx = x + dir[k][0];
                int ty = y + dir[k][1];
                if(tx < 0 || tx >= n || ty < 0 || ty >= m || !tmap[tx][ty])
                    continue;
                if(unio(x*m+y,tx*m+ty))
                {
                    flag = 1;
                    printf("%d\n",i+1);
                }
            }
        }
        if(!flag)
            printf("-1\n");
    }
    return 0 ;
}

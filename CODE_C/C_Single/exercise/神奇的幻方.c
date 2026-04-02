#include <stdio.h>

int main()
{
    int N;
    scanf("%d",&N);
    int num[N][N];
    for(int i=0;i<=N-1;i++)
    {
        for(int j=0;j<=N-1;j++)
        {
            num[i][j]=0;
        }
    }
    int x0,y0,x,y;
    x0=1;y0=(N+1)/2;
    num[x0-1][y0-1]=1;
    for(int k=2;k<=N*N;k++)
    {
        if(x0==1&&y0!=N)
        {
            x=N;y=y0+1;
        }
        if(y0==N&&x0!=1)
        {
            y=1;x=x0-1;
        }
        if(x0==1&&y0==N)
        {
            x=x0+1;y=y0;
        }
        if(x0!=1&&y0!=N)
        {
            if(num[x0-1-1][y0+1-1]==0)
            {
                x=x0-1;y=y0+1;
            }
            else
            {
                x=x0+1;y=y0;
            }
        }
        num[x-1][y-1]=k;
        x0=x;y0=y;
    }
    for(int i=0;i<=N-1;i++)
    {
        for(int j=0;j<=N-1;j++)
        {
            printf("%d ",num[i][j]);
        }
        printf("\n");
    }
    return 0;
}
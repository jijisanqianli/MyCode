//
// Created by Jerry on 2026/3/11.
//
#include <stdio.h>

int num[1024][1024];

void freeman(int num[][1024],int x,int y,int length)
{
    for(int i=x;i<x+length/2;i++)
    {
        for(int j=y;j<y+length/2;j++)
        {
            num[i][j]=0;
        }
    }
    if(length/2==1)
    {
        return;
    }
    else
    {
        freeman(num,x+length/2,y,length/2);
        freeman(num,x+length/2,y+length/2,length/2);
        freeman(num,x,y+length/2,length/2);
    }
}

int main()
{
    int n,length=1;
    scanf("%d",&n);
    length=length<<n;//length*2的n次方
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<length;j++)
        {
            num[i][j]=1;
        }
    }
    freeman(num,0,0,length);
    for(int i=0;i<length;i++)
    {
        for(int j=0;j<length;j++)
        {
            printf("%d ",num[i][j]);
        }
        printf("\n");
    }
    return 0;
}
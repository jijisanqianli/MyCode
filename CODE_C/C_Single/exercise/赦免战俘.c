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
// #include <stdio.h>

// void copyarr(int* o,int* n,int xbegin,int ybegin,int lenth/*原来的*/)
// {
//     for(int i=xbegin;i<=xbegin+lenth-1;i++)
//     {
//         for(int j=ybegin;j<=ybegin+lenth-1;j++)
//         {
//             *(n+lenth*2*i+j)=*(o+lenth*(i-xbegin)+(j-ybegin));
//             // n[i][j]=o[i-xbegin][j-ybegin];
//         }
//     }
// }

// int main()
// {
//     int n,length=1,reallength=2;
//     scanf("%d",&n);
//     for(int i=0;i<n;i++)
//     {
//         length*=2;
//     }
//     int count=0;
//     while(reallength!=length)
//     {
//         if(count==0)
//         {
//             int ori[2][2]={{0,1},{1,1}};
//             count++;
//         }
//         else
//         {
//             int *ori=(int *)malloc(reallength*sizeof(int));

//         }
//         reallength*=2;
//         int *n=(int *)malloc(reallength*sizeof(int));
//         // int n[reallength][reallength];//创建一个更大的数组
//         for(int i=0;i<(reallength/2);i++)//右上角
//         {
//             for(int j=0;j<(reallength/2);j++)
//             {
//                 n[i][j]=0;
//             }
//         }
//         copyarr(&(ori[0][0]),&(n[0][0]),reallength/2,0,reallength/2);
//         copyarr(&(ori[0][0]),&(n[0][0]),0,reallength/2,reallength/2);
//         copyarr(&(ori[0][0]),&(n[0][0]),reallength/2,reallength/2,reallength/2);
//     }
//     return 0;
// }
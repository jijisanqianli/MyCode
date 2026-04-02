#include <stdio.h>

//定义魔法
void magic(int* arr,int x,int y,int r,int z)
{
    
}

int main()
{
    ///构造方阵表和输入次数
    int n,m;
    scanf("%d %d",&n,&m);
    int arr[n][n];
    int num=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            num++;
            arr[i][j]=num;
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }    
    return 0;
}
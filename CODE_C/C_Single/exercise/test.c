#include <stdio.h>

int main()
{
    int num[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    //先换四个角
    int storage1=num[0][0];
    num[0][0]=num[2][0];
    int storage2=num[0][2];
    num[0][2]=storage1;
    storage1=num[2][2];
    num[2][2]=storage2;
    num[2][0]=storage1;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",num[i][j]);
        }
        printf("\n");
    }
}


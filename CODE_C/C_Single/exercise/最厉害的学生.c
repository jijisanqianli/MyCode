#include <stdio.h>

typedef struct
{
    char name[9];
    int Chinese;
    int math;
    int English;
}Student;


int main()
{
    int N=0;
    scanf("%d",&N);//学生个数
    Student arr[N];//构建结构体数组
    int max=0,count=0;
    for(int i=0;i<N;i++)
    {
        Student x;
        scanf("%s %d %d %d",x.name,&x.Chinese,&x.math,&x.English);
        int sum=x.Chinese+x.math+x.English;
        if(sum>max)
        {
            max=sum;
            count=i;
        }
        arr[i]=x;
    }
    printf("%s %d %d %d",arr[count].name,arr[count].Chinese,arr[count].math,arr[count].English);
    return 0;
}
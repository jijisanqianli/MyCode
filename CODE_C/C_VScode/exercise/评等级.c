#include <stdio.h>

typedef struct//定义Student
{
    char name[9];
    int Chinese;
    int Math;
    int English;
}Student;

int judge(Student a,Student b);

int main()
{
    int N=0;//同学个数
    scanf("%d",&N);
    Student list[N];
    for(int i=0;i<N;i++)
    {
        scanf("%s %d %d %d",list[i].name,&list[i].Chinese,&list[i].Math,&list[i].English);
    }
    for(int i=0;i<N;i++)
    {
        for(int j=i+1;j<N;j++)
        {
            if(judge(list[i],list[j])==1)
            {
                printf("%s %s\n",list[i].name,list[j].name);
            }
        }
    }
    return 0;
}

int judge(Student a,Student b)
{
    int difference;
    difference=a.Chinese-b.Chinese;
    if(difference<=5&&difference>=-5)
    {
        difference=a.Math-b.Math;
        if(difference<=5&&difference>=-5)
        {
            difference=a.English-b.English;
            if(difference<=5&&difference>=-5)
            {
                difference=(a.Chinese+a.English+a.Math)-(b.Chinese+b.English+b.Math);
                if(difference<=10&&difference>=-10)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
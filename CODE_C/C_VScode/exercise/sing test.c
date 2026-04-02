#include <stdio.h>

float ranking(int m)
{
    int max=0,min,count=0,sum=0,x;
    for(int i=0;i<m;i++)
    {
        if(i!=m-1)
        {
            scanf("%d ",&x);
        }
        else
        {
            scanf("%d",&x);
        }
        if(x>max)
        {
            max=x;
        }
        if(count==0)
        {
            min=x;
            count=1;
        }
        if(x<min&&count==1)
        {
            min=x;
        }
        sum+=x;
    }
    float result;
    result=(sum-min-max)/(m-2);
    return result;
}

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    float max=0;//选手个数，评委个数
    for(int i=0;i<n;i++)
    {
        float result=ranking(m);
        if(result>max)
        {
            max=result;
        }
    }
    printf("%.2f",max);
    return 0;
}
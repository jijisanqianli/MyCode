#include <stdio.h>
#include <stdlib.h>

int findNumber(int x);
int getTheNumber1(int begin);
int getTheNumber2(int begin);
int judgePrime(int x);

int main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    //首先构造范围内的回文数
    //1551 989 7557 111 12321
    int *list = (int*)calloc(b-a+1, sizeof(int));
    int listcount=0;
    //找出位数
    int numberA=findNumber(a);
    int numberB=findNumber(b);
    //然后开始构造
    for(int i=numberA;i<=numberB;i++)//位数的上升
    {
        int theNumber=0;//回文数本体
        if(i%2==0)//位数是偶数,比如是4
        {   
            //先创建初始数，比如10
            int begin=1,end=1;
            for(int j=0;j<(i/2)-1;j++)
            {
                begin*=10;
                end*=10;
            }
            end*=10;
            while(begin<=(end-1))
            {
                theNumber=getTheNumber1(begin);//获得回文数
                if(theNumber>=a&&theNumber<=b)
                {
                    list[listcount]=theNumber;
                    listcount++;
                }
                begin++;
            }
        }
        else//位数是奇数，比如5
        {
            //先创建初始数比如100
            int begin=1,end=1;
            for(int j=0;j<(i-1)/2;j++)
            {
                begin*=10;
                end*=10;
            }
            end*=10;
            while(begin<=(end-1))
            {
                theNumber=getTheNumber2(begin);//获得回文数
                if(theNumber>=a&&theNumber<=b)
                {
                    list[listcount]=theNumber;
                    listcount++;
                }
                begin++;
            }
        }
    }
    for(int i=0;list[i]!=0;i++)
    {
        if(judgePrime(list[i])==1)
        {
            printf("%d\n",list[i]);
        }
    }
    free(list);
    return 0;
}

/*  123 321   */

int getTheNumber1(int begin)
{
    int a=begin,b=0;
    while(a!=0)
    {
        b=b*10+a%10;
        a=(a-(a%10))/10;
        begin*=10;
    }
    int result=begin+b;
    return result;
}

int getTheNumber2(int begin)
{
    int a=begin,b=0;
    a=(a-(a%10))/10;
    while(a!=0)
    {
        b=b*10+a%10;
        a=(a-(a%10))/10;
        begin*=10;
    }
    int result=begin+b;
    return result;
}

int findNumber(int x)
{
    int count=1;
    while(1)
    {
        if((x%10)==x)
        {
            break;
        }
        count++;
        x=(x-(x%10))/10;
    }
    return count;
}

int judgePrime(int x)
{
    if(x==1)
    {
        return 0;
    }
    else if(x%2==0&&x!=2)
    {
        return 0;
    }
    else
    {
        for(int i=2;i*i<=x;i++)
        {
            if(x%i==0)
            {
                return 0;
            }
        }
        return 1;
    }
}
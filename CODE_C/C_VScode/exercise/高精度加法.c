#include <stdio.h>

int plusread(int* num1,int* num2,int* resultreverse,int num1count,int num2count);

int main()
{
    int num1[600]={},num2[600]={};
    int num1count=0,num2count=0;
    char ch;
    while((ch=getchar())!='\n')
    {
        num1[num1count]=ch-'0';
        num1count++;
    }
    while((ch=getchar())!='\n')
    {
        num2[num2count]=ch-'0';
        num2count++;
    }
    int resultreverse[600];//装入加法结果
    int begin=plusread(num1,num2,resultreverse,num1count,num2count);
    for(int i=begin;i>=0;i--)
    {
        printf("%d",resultreverse[i]);
    }
    return 0;
}

int plusread(int* num1,int* num2,int* resultreverse,int num1count,int num2count)
{
    int num1reverse[600]={};
    int num2reverse[600]={};
    for(int i=num1count-1;i>=0;i--)
    {
        num1reverse[num1count-1-i]=num1[i];
    }
    for(int i=num2count-1;i>=0;i--)
    {
        num2reverse[num2count-1-i]=num2[i];
    }
    int max=num1count;
    if(num2count>max)
    {
        max=num2count;
    }
    int jinwei=0;
    for(int i=0;i<max+1;i++)
    {
        resultreverse[i]=(num1reverse[i]+num2reverse[i]+jinwei)%10;
        jinwei=(num1reverse[i]+num2reverse[i]+jinwei)/10;
        if(i==max&&resultreverse[i]!=0)//判断最后一位是否进位（进位了）
        {
            return max;
        }
    }
    return max-1;

}
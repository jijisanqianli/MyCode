#include <stdio.h>

typedef struct//一局的最终比分
{
    int W;
    int L;
}title;

title first[5685];//第一种分制的结果存储
title second[2980];//第二种分制的结果存储

void judge1(int* result1,int* firstcount);
void judge2(int* result2,int* secondcount);

int main()
{
    char input[25]="";//一行输入
    int result1[2]={};//11分制存储数据W,L
    int result2[2]={};//21分制存储
    int firstcount=0,secondcount=0;//结果存储的工具
    int xunhuan=1;
    while(xunhuan==1)
    {
        fgets(input,25,stdin);//读入一行数据
        for(int i=0;i<25;i++)//解析该行数据
        {
            if(input[i]=='W')
            {
                result1[0]++;result2[0]++;
                judge1(result1,&firstcount);
                judge2(result2,&secondcount);
                input[i]='\0';
            }
            else if(input[i]=='L')
            {
                result1[1]++;result2[1]++;
                judge1(result1,&firstcount);
                judge2(result2,&secondcount);
                input[i]='\0';
            }
            else if(input[i]=='E')//停止,进行最后剩余数据存储
            {
                xunhuan=0;
                first[firstcount].W=result1[0];
                first[firstcount].L=result1[1];
                second[secondcount].W=result2[0];
                second[secondcount].L=result2[1];
                firstcount++;secondcount++;
                break;//停止
            }
            else
            {
                input[i]='\0';
            }
        }
    }
    //输出第一种结果
    for(int i=0;i<firstcount;i++)
    {
        printf("%d:%d\n",first[i].W,first[i].L);
    }
    //输出第二种结果
    printf("\n");
    for(int i=0;i<secondcount;i++)
    {
        if(i==secondcount-1)
        {
            printf("%d:%d",second[i].W,second[i].L);
        }
        else
        {
            printf("%d:%d\n",second[i].W,second[i].L);
        }
    }
    return 0;
}

void judge1(int* result1,int* firstcount)//分析一局是否结束,并且进行相关处理
{
    int compare=result1[0]-result1[1];
    if((compare>=2||compare<=-2)&&(result1[0]>=11||result1[1]>=11))//一局结束
    {
        first[*firstcount].W=result1[0];
        first[*firstcount].L=result1[1];
        result1[0]=0;result1[1]=0;//重置
        (*firstcount)++;
    }
}

void judge2(int* result2,int* secondcount)//分析一局是否结束,并且进行相关处理
{
    int compare=result2[0]-result2[1];
    if((compare>=2||compare<=-2)&&(result2[0]>=21||result2[1]>=21))//一局结束
    {
        second[*secondcount].W=result2[0];
        second[*secondcount].L=result2[1];
        result2[0]=0;result2[1]=0;//重置
        (*secondcount)++;
    }
}
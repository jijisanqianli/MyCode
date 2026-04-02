#include <stdio.h>
#include <string.h>

#define MAX 2100
char s1[MAX]={};int num1[MAX]={};//反转版的数字
char s2[MAX]={};int num2[MAX]={};

int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    /*fgets(s1,MAX,stdin);*/s1[strcspn(s1, "\n")] = 0;
    /*fgets(s2,MAX,stdin);*/s2[strcspn(s2, "\n")] = 0;
    int s1length=strlen(s1),s2length=strlen(s2);
    for(int i=0;i<s1length;i++)
    {
        num1[i]=s1[s1length-1-i]-'0';
    }
    for(int i=0;i<s2length;i++)
    {
        num2[i]=s2[s2length-1-i]-'0';
    }
    int result[MAX]={};
    int resultcount=0;
    for(int i=0;i<s1length;i++)//下面的数字
    {
        int k=0;int jinwei=0;
        for(k=0;k<s2length;k++)//上面的数字
        {
            int resultcopy=result[i+k];
            result[i+k]=(jinwei+num1[i]*num2[k]+resultcopy)%10;
            jinwei=(jinwei+num1[i]*num2[k]+resultcopy)/10;
        }
        result[i+k]+=jinwei;
        if(result[i+k]>0)
        {
            resultcount=i+k;
        }
        else
        {
            resultcount=i+k-1;
        }
    }
    if(s1[0]=='0'||s2[0]=='0')
    printf("0");
    else
    {
        for(int i=resultcount;i>=0;i--)
        {
        printf("%d",result[i]);
        }
    }
    return 0;
}


/*1  2  3
     9  4
--------
  4   8   12
9 18  27*/
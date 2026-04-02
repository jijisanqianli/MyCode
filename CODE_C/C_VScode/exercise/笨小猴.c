#include <stdio.h>
#include <string.h>

int judgePrime(int n)
{
    if (n <= 1) 
    {
        return 0; 
    }
    if (n == 2) {
        return 1; 
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int count=0;
    char word[110];
    fgets(word,sizeof(word),stdin);
    word[strcspn(word,"\n")]='\0';
    int num[27];
    for(int i=0;i<=26;i++)
    {
        num[i]=0;
    }
    while(word[count]!='\0')
    {
        num[word[count]-'a']++;
        count++;
    }
    int maxn=0,minn=0;
    count=0;
    for(int i=0;i<=26;i++)
    {
        if(num[i]>=maxn)
        {
            maxn=num[i];
        }
        if(num[i]!=0)
        {
            if(count==0)
            {
                minn=num[i];
                count++;
            }
            if(num[i]<=minn)
            {
                minn=num[i];
            }
        }
    }
    int t=maxn-minn;
    int judge=judgePrime(t);
    if(judge==1)
    {
        printf("Lucky Word\n%d",t);
    }
    else
    {
        printf("No Answer\n0");
    }
    return 0;
}
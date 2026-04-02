#include <stdio.h>
#include <string.h>

int main()
{
    int wordcount[26];
    for(int i=0;i<=25;i++)
    {
        wordcount[i]=0;
    }
    for(int i=0;i<=3;i++)
    {
        int count=0;
        char s[110];
        fgets(s,sizeof(s),stdin);
        s[strcspn(s,"\n")]='\0';
        while(s[count]!='\0')
        {
            if(s[count]>='A'&&s[count]<='Z')
            {
                wordcount[s[count]-'A']++;
            }
            count++;
        }
    }
    int max=0;
    for(int i=0;i<=25;i++)
    {
        if(wordcount[i]>=max)
        {
            max=wordcount[i];
        }
    }
    int maxconst=max;
    for(int i=0;i<maxconst;i++)
    {
        for(int j=0;j<26;j++)
        {
            if((max-wordcount[j])>0&&j!=25)
            {
                printf("  ");
            }
            else if((max-wordcount[j])==0&&j!=25)
            {
                printf("* ");
                wordcount[j]--;
            }
            else if((max-wordcount[j])==0&&j==25)
            {
                printf("*");
                wordcount[j]--;
            }
            else if((max-wordcount[j])>0&&j==25)
            {
                printf(" ");
            }
        }
        max--;
        printf("\n");
    }
    for(int i=0;i<25;i++)
    {
        char k='A'+i;
        printf("%c ",k);
    }
    printf("Z");
    return 0;

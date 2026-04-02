#include <stdio.h>

int main()
{
    int n,k=1;
    int num[27];
    for(int i=0;i<=26;i++)
    {
        num[i]=0;
    }
    scanf("%d",&n);
    num[k-1]=n;
    while(n!=1)
    {
        if(n%2==0)
        {
            n=n/2;
        }
        else
        {
            n=n*3+1;
        }
        k++;
        num[k-1]=n;
    }
    for(int i=k-1;i>=0;i--)
    {
        printf("%d ",num[i]);
    }
    return 0;
}
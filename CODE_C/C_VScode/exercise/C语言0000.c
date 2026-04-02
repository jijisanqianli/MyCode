#include <stdio.h>
#include <stdlib.h>

int compare(const void* a,const void* b)
{
    return *(int*)a-*(int*)b;
}

int main()
{
    int m,n,k;
    scanf("%d",&m);
    int nums1[m];
    for(int i=0;i<=m-1;i++)
    {
        scanf("%d",&k);
        nums1[i]=k;
    }
    scanf("%d",&n);
    int nums2[n];
    for(int i=0;i<=n-1;i++)
    {
        scanf("%d",&k);
        nums2[i]=k;
    }
    int num[m+n];
    for(int i=0;i<=m-1;i++)
    {
        num[i]=nums1[i];
    }
    for(int i=0;i<=n-1;i++)
    {
        num[i+m]=nums2[i];
    }
    qsort(num,sizeof(num)/sizeof(num[0]),sizeof(num[0]),compare);
    for(int i=0;i<=m+n-1;i++)
    {
        printf("%d ",num[i]);
    }
    return 0;
}
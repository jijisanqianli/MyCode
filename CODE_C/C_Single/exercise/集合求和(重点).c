#include <stdio.h>

int main() {
    int s[30];
    int n = 0;
    long long sum = 0;
    
    // 读取所有数字
    while (scanf("%d", &s[n]) == 1) {
        sum += s[n];
        n++;
    }
    
    // 每个元素出现 2^(n-1) 次
    // 总和 = sum × 2^(n-1)
    
    long long result = sum;
    for (int i = 1; i < n; i++) {
        result *= 2;  // 乘以 2^(n-1)
    }
    
    printf("%lld\n", result);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

//2,54,64,5,15,4
//6个时算到3个和 5个时算到2个和
//奇数个数，只需要算出集合个数
long long theComuteCount(int sCount,int number);

int main()
{
    //int* s=(int*)calloc(31,sizeof(int))
    int s[30]={};
    int sCount=0;
    char space;
    int sum=0;//存储集合总数
    while(1)
    {
        scanf("%d",&s[sCount]);
        sum+=s[sCount];
        sCount++;
        scanf("%c",&space);
        if(space=='\n')
        {
            break;
        }
    }
    long long result=0;//最终结果
    long long comuteCount;//集合个数
    if((sCount%2)==0)//偶数个数
    {
        for(int i=0;i<=(sCount/2)-1;i++)
        {
            comuteCount=theComuteCount(sCount,i);
            result+=(comuteCount*sum);
        }
        comuteCount=theComuteCount(sCount,sCount/2)/2;//最后一次单独算
        result+=(comuteCount*sum);
    }
    else//奇数个数
    {
        for(int i=0;i<=(sCount-1)/2;i++)
        {
            comuteCount=theComuteCount(sCount,i);
            result+=(comuteCount*sum);
        }
    }
    printf("%lld",result);
    return 0;
}

long long theComuteCount(int sCount,int number)//组合数公式7*6*5/3*2 6*5*4/3*2*1
{
    
    long long res = 1;
    for (int i = 1; i <= number; i++) 
    {
        // 分子：n - k + i
        // 分母：i
        res = res * (sCount-number+ i) / i;
    }
    return res;
}
*/
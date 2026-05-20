#include <stdio.h>

unsigned long long possibilities(unsigned long long n,unsigned long long result[1000]) {
    unsigned long long sum=1;
    for (int i = 1; i <= n/2; i++) {
        if (result[i]!=0) {
            sum+=result[i];
            continue;
        }
        sum+=possibilities(i,result);
    }
    return result[n]=sum;
}

int main() {
    int n;
    scanf("%d",&n);
    unsigned long long result[1000]={0};
    result[1]=1;
    printf("%llu",possibilities(n,result));
    return 0;
}
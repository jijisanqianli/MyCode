#include <stdio.h>

unsigned long long count_possibilities(int input,int remain,unsigned long long memory[20][20]) {
    if (input == 0) return 1;
    if (memory[input][remain] != 0) return memory[input][remain];
    if (input > 0 && remain==0 )return memory[input][remain]=count_possibilities(input-1,remain+1,memory);
    return memory[input][remain]=count_possibilities(input-1,remain+1,memory)+count_possibilities(input,remain-1,memory);
}

int main () {
    int n;
    scanf("%d",&n);
    unsigned long long memory[20][20] = {0};
    unsigned long long possibilities = count_possibilities(n,0,memory);
    printf("%llu",possibilities);
    return 0;
}
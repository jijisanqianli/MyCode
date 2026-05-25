#include <stdio.h>
#include <string.h>

// int count_plans(int i,int* price,int money_remaining,int N,int storage[100][10001]) {
//     if (money_remaining==0) return 1;
//     if (money_remaining<0 || i>N-1) return 0;
//     if (storage[i][money_remaining]!=-1) return storage[i][money_remaining];
//     return count_plans(i+1,price,money_remaining-price[i],N,storage)+count_plans(i+1,price,money_remaining,N,storage);
// }

//int storage[100][10001];

int main() {
    int N,M;//N为菜品种类，M为钱数
    scanf("%d %d",&N,&M);
    int price[N];
    for (int i=0;i<N;i++) {
        scanf("%d",&price[i]);
    }
    int storage[10001]={0};//存储达成钱数的方案数
    storage[0]=1;//不点菜是达成0元的唯一方案
    for (int i=0;i<N;i++) {
        for (int j=M;j>=price[i];j--) {
            storage[j]=storage[j]+storage[j-price[i]];
        }
    }
    printf("%d",storage[M]);
    // memset(storage, -1, sizeof(storage));
    // int result=count_plans(0,price,M,N,storage);
    // printf("%d",result);
    return 0;
}
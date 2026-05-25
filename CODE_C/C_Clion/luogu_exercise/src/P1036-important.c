#include <stdbool.h>
#include <stdio.h>

bool isprime(int n) {
    if (n<2) return false;
    if (n==2) return true;
    if (n%2==0) return false;
    for (int i=3;i*i<=n;i+=2) {
        if (n%i==0) return false;
    }
    return true;
}

void count_primes(int* num,int* primecount,int sum,int count,int start,const int count_goal,int n) {
    if (count==count_goal) {
        if (isprime(sum)) {
            (*primecount)++;
        }
        return;
    }
    for (int i=start;i<=n-(count_goal-count);i++) {
        count_primes(num,primecount,sum+num[i],count+1,i+1,count_goal,n);
    }
}

int main() {
    int n,k;
    scanf("%d %d",&n,&k);
    int num[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&num[i]);
    }
    int prime_count=0;
    count_primes(num,&prime_count,0,0,0,k,n);
    printf("%d",prime_count);
    return 0;
}
#include <stdio.h>

int main() {
    int n;
    scanf("%d",&n);
    int num[n+1];
    //从大到小进行
    int power=n;
    for (int i=0;i<=n;i++) {
        scanf("%d",&num[i]);
    }
    if (n==0) {
        printf("%d",num[0]);
    }
    else {
        if (num[0]!=1&&num[0]!=-1) {
            printf("%d",num[0]);
        }
        if (num[0]==-1) {
            printf("-");
        }
        if (n>=1) {
            printf("x");
            if (power>1) {
                printf("^%d",power);
            }
            power--;
            for (int i=1;i<=n-1;i++) {
                if (num[i]==0) {
                    power--;
                    continue;
                }
                if (num[i]>0) {
                    printf("+");
                    if (num[i]!=1) {
                        printf("%d",num[i]);
                    }
                }
                if (num[i]<0) {
                    printf("-");
                    if (num[i]!=-1) {
                        printf("%d",-num[i]);
                    }
                }
                printf("x");
                if (power>1) {
                    printf("^%d",power);
                }
                power--;
            }
            if (num[n]>0) {
                printf("+");
            }
            if (num[n]!=0) {
                printf("%d",num[n]);
            }
        }
    }
    return 0;
}
#include <stdio.h>

unsigned long long W(long long a,long long b,long long c,unsigned long long result[25][25][25]) {
    if (a<=0 || b<=0 || c<=0) return 1;
    if (a>20 || b>20 || c>20) return W(20,20,20,result);
    if (result[a][b][c]!=0) return result[a][b][c];
    if (a<b && b<c) return result[a][b][c]=W(a,b,c-1,result)+W(a,b-1,c-1,result)-W(a,b-1,c,result);
    return result[a][b][c]=W(a-1,b,c,result)+W(a-1,b-1,c,result)+W(a-1,b,c-1,result)-W(a-1,b-1,c-1,result);
}

int main() {
    long long a,b,c;
    unsigned long long result[25][25][25]={0};
    while (1) {
        scanf("%lld %lld %lld",&a,&b,&c);
        if (a==-1 && b==-1 && c==-1) {
            break;
        }
        printf("w(%lld, %lld, %lld) = %llu\n",a,b,c,W(a,b,c,result));
    }
    return 0;
}
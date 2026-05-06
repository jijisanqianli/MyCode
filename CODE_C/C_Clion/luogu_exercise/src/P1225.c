#include <stdio.h>

typedef struct {
    int num[1500];
    int length;
}BIG_NUM;

BIG_NUM plus(BIG_NUM a,BIG_NUM b) {
    BIG_NUM result;
    int carry=0;
    int times=a.length;
    if (a.length<b.length) times=b.length;
    for (int i=0; i<times+1; i++) {
        result.num[i]=(a.num[i]+b.num[i]+carry)%10;
        carry=(a.num[i]+b.num[i]+carry)/10;
    }
    result.length=times;
    if (result.num[times]!=0) result.length++;
    return result;
}

void init_BIG_NUM(BIG_NUM* num) {
    for (int i=0; i<1500; i++) {
        num->num[i]=0;
    }
    num->length=1;
}

BIG_NUM count_stairs(int N) {
    if (N<=2) {
        BIG_NUM result;
        result.num[0]=N;result.length=1;
        return result;
    }
    BIG_NUM a,b,sum;
    init_BIG_NUM(&a);init_BIG_NUM(&b);init_BIG_NUM(&sum);
    a.length=1;a.num[0]=1;
    b.length=1;b.num[0]=2;
    for (int i=3; i<=N; i++) {
        sum=plus(a,b);
        a=b;
        b=sum;
    }
    return sum;
}

void print_BIG_NUM(BIG_NUM num) {
    for (int i=num.length-1; i>=0; i--) {
        printf("%d",num.num[i]);
    }
}

int main () {
    int N;
    scanf("%d",&N);
    BIG_NUM result=count_stairs(N);
    print_BIG_NUM(result);
    return 0;
}

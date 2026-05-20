#include <stdio.h>

typedef struct {
    int count;
    int num[500];
}BIG_NUM;

BIG_NUM init(int x) {
    BIG_NUM result;
    int count=0;
    for (int i=0;i<500;i++) {
        result.num[i]=0;
    }
    if (x==0) {
        result.count=1;
        return result;
    }
    while (x!=0) {
        result.num[count]=x%10;
        x=x/10;
        count++;
    }
    result.count=count;
    return result;
}

BIG_NUM plus(BIG_NUM num1, BIG_NUM num2) {
    BIG_NUM result=init(0);
    int seq=num1.count;
    if (num1.count < num2.count) {
        seq=num2.count;
    }
    result.count=seq;
    int carry=0;
    for (int i=0;i<seq;i++) {
        result.num[i]=(num1.num[i]+num2.num[i]+carry)%10;
        carry=(num1.num[i]+num2.num[i]+carry)/10;
    }
    if (carry!=0) {
        result.count++;
        result.num[result.count-1]=carry;
    }
    return result;
}

void print_BIG_NUM(BIG_NUM num) {
    int seq=num.count;
    for (int i=0;i<seq;i++) {
        printf("%d",num.num[num.count-1-i]);
    }
}

BIG_NUM count_routes(int now,int goal,BIG_NUM one,BIG_NUM zero) {
    BIG_NUM result=init(0);
    BIG_NUM second=init(1),third=init(2);
    for (int i=4;i<=goal;i++) {
        result=plus(second,third);
        second=third;
        third=result;
    }
    return result;
}

int main() {
    int m,n;
    scanf("%d %d",&m,&n);
    n=n-(m-1);m=1;
    BIG_NUM one=init(1),zero=init(0);
    print_BIG_NUM(count_routes(m,n,one,zero));
    return 0;
}
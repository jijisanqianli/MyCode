#include <stdio.h>

void print_arr(int* X,int len);
void compare(int* A,int* B,int N,int* A_score,int* B_score,int Na,int Nb);
int result(int A,int B);

int main() {
    int N,Na,Nb;
    scanf("%d %d %d",&N,&Na,&Nb);
    int A[Na],B[Nb];
    for (int i=0;i<Na;i++) {
        scanf("%d",&A[i]);
    }
    //printf("end1");
    for (int i=0;i<Nb;i++) {
        scanf("%d",&B[i]);
    }
    //printf("end2");
    int A_score=0,B_score=0;
    compare(A,B,N,&A_score,&B_score,Na,Nb);
    printf("%d %d",A_score,B_score);
    return 0;
}

void print_arr(int* X,int len) {
    for (int i=0;i<len;i++) {
        printf("%d ",X[i]);
    }
    printf("\n");
}

void compare(int* A,int* B,int N,int* A_score,int* B_score,int Na,int Nb) {
    int A_pointer=0,B_pointer=0;
    for (int i=0;i<N;i++) {
        //printf("begin1");
        int the_result=result(A[A_pointer],B[B_pointer]);
        //printf(" %d ",the_result);
        if (the_result==1) {
            (*A_score)++;
        }else if (the_result==-1) {
            (*B_score)++;
        }
        A_pointer++;B_pointer++;
        if (A_pointer==Na) {
            A_pointer=0;
        }
        if (B_pointer==Nb) {
            B_pointer=0;
        }
        //printf("end1\n");
    }

}

int result(int A,int B) {
    if (A==0) {
        if (B==0) {
            return 0;
        }else if (B==1) {
            return -1;
        }else if (B==2) {
            return 1;
        }else if (B==3) {
            return 1;
        }else if (B==4) {
            return -1;
        }
    }else if (A==1) {
        if (B==1) {
            return 0;
        }else if (B==2) {
            return -1;
        }else if (B==3) {
            return 1;
        }else if (B==4) {
            return -1;
        }
    }else if (A==2) {
        if (B==2) {
            return 0;
        }else if (B==3) {
            return -1;
        }else if (B==4) {
            return 1;
        }
    }else if (A==3) {
        if (B==3) {
            return 0;
        }else if (B==4) {
            return 1;
        }
    }else if (A==4) {
        if (B==4) {
            return 0;
        }
    }
    return -result(B,A);
}

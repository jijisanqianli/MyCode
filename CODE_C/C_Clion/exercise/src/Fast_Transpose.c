#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int i, j; // 行、列下标
    int v;    // 元素值
} Triple;

typedef struct {
    Triple data[1000]; // 非零元素表
    int mu, nu, tu;    // 矩阵行数、列数、非零元个数
} TSMatrix;

TSMatrix* create_arr_sequence(int mu,int nu,int tu);
TSMatrix* fast_transpose(TSMatrix* the_arr);
void print_arr_sequence_num(TSMatrix* the_arr);
void print_arr_sequence(TSMatrix* the_arr);

int main() {
    int mu,nu,tu;
    scanf("%d %d %d",&mu,&nu,&tu);
    TSMatrix* the_arr=create_arr_sequence(mu,nu,tu);
    print_arr_sequence(the_arr);
    printf("\n");
    TSMatrix* new_arr=fast_transpose(the_arr);
    print_arr_sequence(new_arr);
    free(the_arr);
    free(new_arr);
    return 0;
}

void print_arr_sequence(TSMatrix* the_arr) {
    int count=0;
    int v=the_arr->data[count].v,i=the_arr->data[count].i,j=the_arr->data[count].j;
    for (int n=0;n<the_arr->mu;n++) {
        for (int k=0;k<the_arr->nu;k++) {
            if (n==i && k==j) {
                printf("%d ",v);
                count++;
                v=the_arr->data[count].v;
                i=the_arr->data[count].i;
                j=the_arr->data[count].j;
            }else {
                printf("%d ",0);
            }
        }
        printf("\n");
    }
}

void print_arr_sequence_num(TSMatrix* the_arr) {
    for (int i=0;i<the_arr->tu;i++) {
        printf("%d ",the_arr->data[i].v);
    }
    printf("\n");
}

TSMatrix* create_arr_sequence(int mu,int nu,int tu) {
    TSMatrix* the_arr=(TSMatrix*)malloc(sizeof(TSMatrix));
    the_arr->mu=mu;the_arr->nu=nu;the_arr->tu=tu;
    for (int k=0;k<tu;k++) {
        int i,j,v;
        scanf("%d %d %d",&i,&j,&v);
        the_arr->data[k].i=i;the_arr->data[k].j=j;the_arr->data[k].v=v;
    }
    return the_arr;
}

TSMatrix* fast_transpose(TSMatrix* the_arr) {
    TSMatrix* new_arr=(TSMatrix*)malloc(sizeof(TSMatrix));
    int new_mu=the_arr->nu,new_nu=the_arr->mu,new_tu=the_arr->tu;
    new_arr->mu=new_mu;new_arr->nu=new_nu;new_arr->tu=new_tu;
    int new_row_num[new_mu];
    for (int i=0;i<new_mu;i++) {
        new_row_num[i]=0;
    }
    for (int k=0;k<new_tu;k++) {
        new_row_num[the_arr->data[k].j]++;
    }
    int pos[the_arr->nu];
    pos[0]=0;
    for (int i=1;i<new_mu;i++) {
        pos[i]=pos[i-1]+new_row_num[i-1];
    }
    for (int k=0;k<new_tu;k++) {
        int position=pos[the_arr->data[k].j];
        pos[the_arr->data[k].j]++;
        new_arr->data[position].v=the_arr->data[k].v;
        new_arr->data[position].j=the_arr->data[k].i;
        new_arr->data[position].i=the_arr->data[k].j;
    }
    return new_arr;
}
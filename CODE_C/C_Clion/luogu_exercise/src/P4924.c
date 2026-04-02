#include <stdio.h>
#include <stdlib.h>

int* create_square(int n);
void print_square(int* square,int n);
void counterclockwise_rotation(int* square,int n,int x,int y,int r);
void clockwise_rotation(int* square,int n,int x,int y,int r);

int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int* square=create_square(n);
    //print_square(square,n);
    //printf("%d\n",*(square+1*n+1));
    for(int i=0;i<m;i++) {
        int x,y,r,z;
        scanf("%d %d %d %d",&x,&y,&r,&z);
        if (z==0) {
            clockwise_rotation(square,n,x,y,r);
        }
        else {
            counterclockwise_rotation(square,n,x,y,r);
        }
    }
    print_square(square,n);
    free(square);
    return 0;
}

//顺时针
void clockwise_rotation(int* square,int n,int x,int y,int r) {
    int* centre=square+(x-1)*n+(y-1);
    for(int i=1;i<=r;i++) {
        for(int j=0;j<2*i;j++) {
            //取得四个角
            int* left_up=centre-i*n-i+j;
            int* left_down=centre+i*n-i-j*n;
            int* right_up=centre-i*n+i+j*n;
            int* right_down=centre+i*n+i-j;
            //交换四个角
            int temp=*right_up;
            *right_up=*left_up;
            *left_up=*left_down;
            *left_down=*right_down;
            *right_down=temp;
        }
    }
}

//逆时针
void counterclockwise_rotation(int* square,int n,int x,int y,int r) {
    int* centre=square+(x-1)*n+(y-1);
    for(int i=1;i<=r;i++) {
        for(int j=0;j<2*i;j++) {
            //取得四个角
            int* left_up=centre-i*n-i+j*n;
            int* left_down=centre+i*n-i+j;
            int* right_down=centre+i*n+i-j*n;
            int* right_up=centre-i*n+i-j;
            //交换四个角
            int temp=*right_up;
            *right_up=*right_down;
            *right_down=*left_down;
            *left_down=*left_up;
            *left_up=temp;
        }
    }
}

void print_square(int* square,int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            printf("%d ",*(square+i*n+j));
        }
        printf("\n");
    }
}

int* create_square(int n) {
    int* square = (int*)malloc(n * n * sizeof(int));
    if (square == NULL) {
        return NULL;
    }
    int num=1;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            *(square+i*n+j)= num;
            num++;
        }
    }
    return square;
}
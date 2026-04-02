#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* create_map(int m,int n);
void print_map(char* map,int m,int n);
void change_map(char* map,int m,int n);

int main() {
    int n,m;
    scanf("%d %d",&m,&n);
    char* map=create_map(m,n);
    //printf("输入完成\n");
    //print_map(map,m,n);
    //printf("\n");
    change_map(map,m,n);
    print_map(map,m,n);
    free(map);
    return 0;
}

char* create_map(int m,int n) {
    char* map=(char*)malloc(sizeof(char)*m*n);
    for (int i=0;i<m;i++) {
        char str[n+1];
        scanf("%s",str);
        for (int j=0;j<n;j++) {
            map[i*n+j] = str[j];
        }
    }
    return map;
}

void print_map(char* map,int m,int n) {
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            printf("%c",map[i*n+j]);
        }
        printf("\n");
    }
}

void change_map(char* map,int m,int n) {
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) {
            if (map[i*n+j]=='?') {
                int count=0;
                int begin_x=i-1,begin_y=j-1;
                for (int k=0;k<3;k++) {
                    for (int l=0;l<3;l++) {
                        int x=begin_x+k,y=begin_y+l;
                        if (x>=0 && x<m && y>=0 && y<n) {
                            if (map[n*x+y]=='*') {
                                //printf("%d %d\n",x,y);
                                count++;
                            }
                        }
                    }
                }
                map[i*n+j]='0'+count;
            }
        }
    }
}
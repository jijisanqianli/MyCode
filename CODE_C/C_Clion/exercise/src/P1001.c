#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int num_self;
    int count;
}the_number;

int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int arr[n];
    for(int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }
    int result[m];
    for(int i=0;i<m;i++) {
        int l,r;
        int count=0;
        scanf("%d %d",&l,&r);
        the_number list[r-l+1];int len=0;
        for(int j=l-1;j<=r-1;j++) {
            int num=arr[j];
            //printf("%d\n",num);
            bool has_numer=false;
            for (int k=0;k<=len-1;k++) {
                if (num==list[k].num_self) {
                    list[k].count++;
                    has_numer=true;
                    //printf("增加\n");
                }
            }
            if (has_numer==false) {
                len++;
                list[len-1].num_self=num;
                list[len-1].count=1;
                //printf("新建\n");
            }
        }
        for (int k=0;k<=len-1;k++) {
            //printf("%d:%d\n",list[k].num_self,list[k].count);
            if (list[k].count==list[k].num_self) {
                count++;
            }
        }
        result[i]=count;
    }
    for (int i=0;i<m;i++) {
        printf("%d\n",result[i]);
    }
    return 0;
}
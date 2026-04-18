#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int machine_procedure[21][10000]={0};//[][0]放置最近结束时间

int main () {
    //机器数，工件数
    int m,n;
    scanf("%d %d",&m,&n);
    //安排顺序
    int order[m*n];
    for (int i=0;i<m*n;i++) {
        scanf("%d",&order[i]);
    }
    //确定机器号
    int* machine[n+1];
    for (int i=1;i<=n;i++) {
        int* machine_num=malloc((m+1)*sizeof(int));
        for (int j=1;j<m+1;j++) {
            scanf("%d",&machine_num[j]);
        }
        machine_num[0]=0;
        machine[i]=machine_num;
    }
    //确定加工时间
    int* time[n+1];
    for (int i=1;i<=n;i++) {
        int *time_num=malloc((m+1)*sizeof(int));
        for (int j=1;j<=m;j++) {
            scanf("%d",&time_num[j]);
        }
        time_num[0]=0;
        time[i]=time_num;
    }
    //初始工件加工工序
    int process[n];
    for (int i=0;i<n;i++) {
        process[i]=0;
    }
    for (int i=0;i<n*m;i++) {
        int now_produce=order[i];
        process[now_produce]++;
        int now_machine=machine[now_produce][process[now_produce]];
        int now_time=time[now_produce][process[now_produce]];
        if (machine_procedure[now_machine][0]+1<=machine[now_produce][0]) {
            for (int j=machine[now_produce][0];j<=machine[now_produce][0]+now_time-1;j++) {
                machine_procedure[now_machine][j]=1;
            }
            machine_procedure[now_machine][0]=machine[now_produce][0]+now_time-1;
            machine[now_produce][0]=machine[now_produce][0]+now_time-1;
        }else {

        }
    }
}
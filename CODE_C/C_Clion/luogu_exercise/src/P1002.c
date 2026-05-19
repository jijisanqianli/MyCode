#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
}trap;

unsigned long long count_path(int target_x,int target_y, bool is_trap[25][25]) {
    unsigned long long dp[25][25] = {0};
    for (int x=0;x<=target_x;x++) {
        for (int y=0;y<=target_y;y++) {
            if (is_trap[x][y]) {
                dp[x][y] = 0;
                continue;
            }
            if (x==0&&y==0) {
                dp[x][y] = 1;
                continue;
            }
            if (x==0) {
                dp[x][y] = dp[x][y-1];
                continue;
            }
            if (y==0) {
                dp[x][y] = dp[x-1][y];
                continue;
            }
            dp[x][y]=dp[x-1][y]+dp[x][y-1];
        }
    }
    return dp[target_x][target_y];
}

int main(){
    int target_x,target_y;
    int horse_x,horse_y;
    scanf("%d %d %d %d",&target_x,&target_y,&horse_x,&horse_y);
    bool is_trap[25][25]={false};
    is_trap[horse_x][horse_y]=true;
    is_trap[horse_x+2][horse_y+1]=true;
    is_trap[horse_x+1][horse_y+2]=true;
    if (horse_x-1>=0) is_trap[horse_x-1][horse_y+2]=true;
    if (horse_x-2>=0) is_trap[horse_x-2][horse_y+1]=true;
    if (horse_x-2>=0 && horse_y-1>=0) is_trap[horse_x-2][horse_y-1]=true;
    if (horse_x-1>=0 && horse_y-2>=0) is_trap[horse_x-1][horse_y-2]=true;
    if (horse_y-2>=0) is_trap[horse_x+1][horse_y-2]=true;
    if (horse_y-1>=0) is_trap[horse_x+2][horse_y-1]=true;
    unsigned long long path=count_path(target_x,target_y,is_trap);
    printf("%lld",path);
    return 0;
}
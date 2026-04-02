#include <stdio.h>
#include <string.h>
#include "list.h"

void get_char_list(char* goal_str,int* char_list) {
    int goal_len=strlen(goal_str);
    for (int i=0;i<goal_len;i++) {
        char_list[(int)goal_str[i]]=i+1;
    }
}

int return_pos(int* char_list,char x) {
    return char_list[(int)x]-1;
}

int Sunday(char* standard_str,char* goal_str) {
    int char_list[128]={0};
    get_char_list(goal_str,char_list);
    int standard_len=strlen(standard_str),goal_len=strlen(goal_str);
    int goal_idx=0,standard_idx=0,latest_pos=goal_len-1;
    while (standard_str[standard_idx]!='\0') {
        if (standard_str[standard_idx]==goal_str[goal_idx]) {
            if (goal_idx==goal_len-1) {
                return standard_idx-goal_len+1;
            }
            standard_idx++;
            goal_idx++;
        }else {
            int after_pos=return_pos(char_list,standard_str[latest_pos+1]);
            if (after_pos==-1) {
                goal_idx=0;
                standard_idx=latest_pos+2;
                latest_pos=standard_idx+goal_len-1;
            }
            if (after_pos!=-1) {
                goal_idx=0;
                standard_idx=latest_pos+1-after_pos;
                latest_pos=standard_idx+goal_len-1;
            }
            if (latest_pos>=standard_len) {
                return -1;
            }
        }
    }
    return -1;
}

int main() {
    char standard_str[100];
    char goal_str[100];
    scanf("%s",standard_str);
    scanf("%s",goal_str);
    printf("%d",Sunday(standard_str,goal_str));
    return 0;
}
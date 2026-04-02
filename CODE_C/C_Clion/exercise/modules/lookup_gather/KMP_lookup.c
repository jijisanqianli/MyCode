#include <stdio.h>
#include <string.h>
#include "list.h"

void get_next(int* next,const char* goal_string) {
    next[0]=0;
    int len=0;
    int len_str = strlen(goal_string);
    for(int i=1;i<len_str;i++) {
        while (len>0 && goal_string[i]!=goal_string[len]) {
            len=next[len-1];
        }
        if (goal_string[i]==goal_string[len]) {
            len++;
        }
        next[i]=len;
        // if (goal_string[i]==goal_string[len]) {
        //     len++;
        //     next[i]=len;
        // }else {
        //     while (len>0) {
        //         len=next[len-1];
        //         if (goal_string[i]==goal_string[len]) {
        //             len++;
        //             break;
        //         }
        //     }
        //     next[i]=len;
        // }
    }
}

int KMP_lookup(const char* standard_string,const char* goal_string) {
    int standard_len=strlen(standard_string);
    int goal_len=strlen(goal_string);
    int next[goal_len];
    get_next(next,goal_string);
    int standard_idx=0,goal_idx=0;
    while (standard_string[standard_idx]!='\0') {
        if (standard_len-standard_idx<goal_len&&goal_idx==0) {
            return -1;
        }
        if (standard_string[standard_idx]==goal_string[goal_idx]) {
            if (goal_idx==goal_len-1) {
                return standard_idx-goal_len+1;
            }
            standard_idx++;
            goal_idx++;
        }else {
            if (goal_idx==0) {
                standard_idx++;
                continue;
            }
            goal_idx=next[goal_idx-1];
        }
    }
    return -1;
}

int main() {
    char standard_string[100];
    scanf("%s",standard_string);
    char goal_string[100];
    scanf("%s",goal_string);
    int result=KMP_lookup(standard_string,goal_string);
    printf("%d\n",result);
    return 0;
}
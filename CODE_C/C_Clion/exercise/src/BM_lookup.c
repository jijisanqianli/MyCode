#include <stdio.h>
#include <string.h>

void create_bad_char_list(int* bad_char,char* goal_str) {
    int goal_len = strlen(goal_str);
    for (int i=0; i<goal_len; i++) {
        bad_char[(int)goal_str[i]]=i+1;
    }
}

int get_bad_char_pos(int* bad_char_list,char bad_char) {
    return bad_char_list[(int)bad_char]-1;
}

void create_reverse_next(int* reverse_next,char* goal_str) {
    int goal_len = strlen(goal_str);
    reverse_next[0]=0;
    int len=0;
    for (int i=goal_len-2; i>=0; i--) {
        while (len>0&&goal_str[len]!=goal_str[i]) {
            len=reverse_next[len-1];
        }
        if (goal_str[len]==goal_str[i]) {
            len++;
        }
        reverse_next[i]=len;
    }
}

int BM_lookup(char* standard_str,char* goal_str) {
    int bad_char[128]={0};
    create_bad_char_list(bad_char,goal_str);
    int standard_len=strlen(standard_str),goal_len=strlen(goal_str);
    int standard_idx=goal_len-1,goal_idx=goal_len-1;
    while (standard_idx<standard_len) {
        if (standard_str[standard_idx]==goal_str[goal_idx]) {
            if (goal_idx==0) {
                return standard_idx;
            }
            standard_idx--;
            goal_idx--;
        }else {
            int bad_move=goal_idx-get_bad_char_pos(bad_char,standard_str[standard_idx]);
            if (bad_move<=0) {
                bad_move=1;
            }
            standard_idx+=bad_move+goal_len-goal_idx-1;
            goal_idx=goal_len-1;
        }
    }
    return -1;
}

int main() {
    char standard_str[100];
    char goal_str[100];
    scanf("%s",standard_str);
    scanf("%s",goal_str);
    printf("%d",BM_lookup(standard_str,goal_str));
    return 0;
}
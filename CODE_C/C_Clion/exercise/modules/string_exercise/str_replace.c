#include "dsstring.h"

int str_len(const char *in) {
    int len=0;
    while (in[len]!='\0') {
        len++;
    }
    return len;
}

void getnext(int* next,const char* goal_string) {
    next[0]=0;
    int len=0;
    int len_str = str_len(goal_string);
    for(int i=1;i<len_str;i++) {
        while (len>0 && goal_string[i]!=goal_string[len]) {
            len=next[len-1];
        }
        if (goal_string[i]==goal_string[len]) {
            len++;
        }
        next[i]=len;
    }
}

void KMP_lookup_for_this(const char* standard_string,const char* goal_string,int* list) {
    int goal_len=str_len(goal_string);
    int next[goal_len];
    getnext(next,goal_string);
    int list_idx=0;
    int standard_idx=0,goal_idx=0,result=-1;
    while (standard_string[standard_idx]!='\0') {
        if (standard_string[standard_idx]==goal_string[goal_idx]) {
            if (goal_idx==goal_len-1) {
                result=standard_idx-goal_len+1;
                list[list_idx]=result;
                list_idx++;
                goal_idx=0;
                standard_idx++;
                continue;
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
    result=-1;
    list[list_idx]=result;
}

int str_replace_KMP(const char *in, char *out, int outlen, const char *oldstr, const char *newstr) {
    int in_len = str_len(in),old_len = str_len(oldstr),new_len = str_len(newstr);
    int len_difference=new_len-old_len;
    int outlen_now=in_len+1;
    int out_idx=0,in_idx=0,list_idx=0;
    int count=0;
    int list[100]={0};
    KMP_lookup_for_this(in,oldstr,list);
    while (1) {
        if (in[in_idx]=='\0') {
            //printf("循环结束");
            break;
        }
        if (list[list_idx]==in_idx) {
            if (outlen_now+len_difference<=outlen) {
                for (int i=0;i<new_len;i++) {
                    out[out_idx]=newstr[i];
                    out_idx++;
                }
                outlen_now+=len_difference;
                list_idx++;
                in_idx+=old_len;
                count++;
                continue;
            }
            //printf("替换失败%d%c",in_idx,in[8]);
        }
        out[out_idx]=in[in_idx];
        out_idx++;
        in_idx++;
    }
    out[out_idx]='\0';
    return count;
}

bool is_oldstr(const char* in,int in_dix,const char* oldstr) {
    int i=0;
    while (true) {
        if (in[in_dix]=='\0'&&oldstr[i]!='\0') {
            return false;
        }
        if (oldstr[i]=='\0') {
            return true;
        }
        if (in[in_dix]!=oldstr[i]) {
            return false;
        }
        in_dix++;
        i++;
    }
}

int str_replace_flow(const char *in, char *out, int outlen, const char *oldstr, const char *newstr) {
    int in_len = str_len(in),old_len = str_len(oldstr),new_len = str_len(newstr);
    int len_difference=new_len-old_len;
    int outlen_now=in_len+1;
    int out_idx=0,in_idx=0,list_idx=0;
    int count=0;
    while (1) {
        if (in[in_idx]=='\0') {
            //printf("循环结束");
            break;
        }
        if (in[in_idx]==oldstr[0]) {
            if (is_oldstr(in,in_idx,oldstr)) {
                if (outlen_now+len_difference<=outlen) {
                    for (int i=0;i<new_len;i++) {
                        out[out_idx]=newstr[i];
                        out_idx++;
                    }
                    outlen_now+=len_difference;
                    list_idx++;
                    in_idx+=old_len;
                    count++;
                    continue;
                }
                //printf("替换失败%d%c",in_idx,in[8]);
            }
        }
        out[out_idx]=in[in_idx];
        out_idx++;
        in_idx++;
    }
    out[out_idx]='\0';
    return count;
}

int main() {
    char in[]="abcde";
    int outlen=20;
    char out[100]="";
    char oldstr[]="c";
    char newstr[]="123";
    // int i=0;
    // int list[100]={0};
    // KMP_lookup_for_this(in,oldstr,list);
    // while (1) {
    //     printf("%d ",list[i]);
    //     if (list[i]==-1) {
    //         break;
    //     }
    //     i++;
    // }
    //printf("\n%d\n",str_replace_KMP(in,out,outlen,oldstr,newstr));
    printf("\n%d\n",str_replace_flow(in,out,outlen,oldstr,newstr));
    for (int i=0;out[i]!='\0';i++) {
        printf("%c",out[i]);
    }
    return 0;
}


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_the_same_type(char a,char b);
bool can_handle(const char* str,int i);
void reverse(char *s);
void handle(char* str,int p1,int p2,int p3);

int main() {
    int p1,p2,p3;
    scanf("%d %d %d",&p1,&p2,&p3);
    char str[110];
    scanf("%s",str);
    handle(str,p1,p2,p3);
    printf("%s",str);
    return 0;
}

void handle(char* str,int p1,int p2,int p3) {
    char result[500];
    result[0]='\0';
    char str_copy[500];
    str_copy[0]='\0';
    strcpy(str_copy,str);
    for (int i=0;str_copy[i]!='\0';i++) {
        if (str_copy[i]=='-') {
            if (can_handle(str_copy,i)) {
                strncat(result,str_copy,i);
                char middle[200];
                middle[0]='\0';
                char begin=str_copy[i-1];
                char end=str_copy[i+1];
                int middle_len=end-begin-1;
                if (p1==1) {
                    begin=(char)(begin+1);
                    for (int j=0;j<middle_len;j++) {
                        char every_word[p2+1];
                        for (int k=0;k<p2;k++) {
                            every_word[k]=begin;
                        }
                        every_word[p2] = '\0';
                        strcat(middle,every_word);
                        begin=(char)(begin+1);
                    }
                }else if (p1==2) {
                    if ()
                    begin=(char)(begin-32+1);
                    for (int j=0;j<middle_len;j++) {
                        char every_word[p2+1];
                        for (int k=0;k<p2;k++) {
                            every_word[k]=begin;
                        }
                        every_word[p2] = '\0';
                        strcat(middle,every_word);
                        begin=(char)(begin+1);
                    }
                }else if (p1==3) {
                    for (int j=0;j<middle_len;j++) {
                        char every_word[p2+1];
                        for (int k=0;k<p2;k++) {
                            every_word[k]='*';
                        }
                        every_word[p2] = '\0';
                        strcat(middle,every_word);
                    }
                }
                if (p3==2) {
                    reverse(middle);
                }
                strcat(result,middle);
                int m=i;
                strcpy(str_copy, str_copy + m + 1);
                i=0;
            }
        }
    }
    strcat(result,str_copy);
    strcpy(str,result);
}

void reverse(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++) {
        char t = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = t;
    }
}

bool can_handle(const char* str,int i) {
    if (is_the_same_type(str[i-1],str[i+1])) {
        if (str[i-1]<str[i+1]) {
            return true;
        }
    }
    return false;
}

bool is_the_same_type(char a,char b) {
    if (a>='a' && a<='z'&& b>='a' && b<='z') {
        return true;
    }
    if (a>='0' && a<='9' && b>='0' && b<='9') {
        return true;
    }
    return false;
}
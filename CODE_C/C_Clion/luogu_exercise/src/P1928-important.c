#include <stdio.h>
#include <string.h>

void unzip(char** origin,char* buffer0) {
    while (**origin!='\0') {
        if (**origin!='[' && **origin!=']') {
            int len=strlen(buffer0);
            buffer0[len]=**origin;
            buffer0[len+1]='\0';
            (*origin)++;
        }
        else if (**origin=='[') {
            int num=0;
            (*origin)++;
            while (**origin>='0' && **origin<='9') {
                num=num*10+**origin-'0';
                (*origin)++;
            }
            char buffer[20000]={0};
            unzip(origin,buffer);
            for (int i=0;i<num;i++) {
                strcat(buffer0,buffer);
            }
        }
        else if (**origin==']') {
            (*origin)++;
            break;
        }
    }
}

int main() {
    char origin[20000];
    scanf("%s",origin);
    char* x=&origin[0];
    char buffer[20000];
    unzip(&x,buffer);
    printf("%s",buffer);
    return 0;
}
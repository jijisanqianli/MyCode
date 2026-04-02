#include <stdbool.h>
#include <stdio.h>

bool is_letter(char x) {
    if (x>='a' && x<='z'||x>='A' && x<='Z') {
        return true;
    }
    return false;
}

bool is_big(char x) {
    if (x>='A' && x<='Z') {
        return true;
    }
    return false;
}

int result(char x,char y) {
    int result=(int)x-(int)y;
    if (result<0) {
        return -result;
    }
    return result;
}

int str_compare(const char* ptr1, const char* ptr2){
    int i=0;
    while (1) {
        if (ptr1[i]!=ptr2[i]) {
            if (is_letter(ptr1[i])&&is_letter(ptr2[i])) {
                if (is_big(ptr1[i])) {
                    char small=ptr1[i]+('a'-'A');
                    if (small==ptr2[i]) {
                        i++;
                        continue;
                    }
                }else {
                    char big=ptr1[i]-('A'-'a');
                    if (big==ptr2[i]) {
                        i++;
                        continue;
                    }
                }
            }
            return result(ptr1[i],ptr2[i]);
        }
        i++;
    }
}
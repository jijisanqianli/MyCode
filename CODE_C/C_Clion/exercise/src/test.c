#include <stdbool.h>
#include <stdio.h>

bool is_letter(char x) {
    if ((x>='a' && x<='z')||(x>='A' && x<='Z')) {
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

int str_compare_pro(const char* ptr1, const char* ptr2) {
    int i = 0;
    // 只要有一个没到头，就继续比
    while (ptr1[i] || ptr2[i]) {
        if (ptr1[i] == ptr2[i]) {
            i++;
            continue;
        }
        // 处理大小写特例
        if (is_letter(ptr1[i]) && is_letter(ptr2[i]) && (ptr1[i] ^ 32) == ptr2[i]) {
            i++;
            continue;
        }
        // 不匹配，直接退出
        break;
    }
    return (unsigned char)ptr1[i] - (unsigned char)ptr2[i];
}

int str_compare(const char* ptr1, const char* ptr2){
    int i=0;
    while (1) {
        if (ptr1[i]=='\0'&&ptr2[i]=='\0') {
            return 0;
        }
        if (ptr1[i]!=ptr2[i]) {
            if (is_letter(ptr1[i])&&is_letter(ptr2[i])) {
                if (is_big(ptr1[i])) {
                    char small=ptr1[i]+('a'-'A');
                    if (small==ptr2[i]) {
                        i++;
                        continue;
                    }
                }else {
                    char big=ptr1[i]-('a'-'A');
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

int main() {
    char x[4]="abc";
    char y[4]="aBC";
    printf("%d\n",str_compare(x,y));
}
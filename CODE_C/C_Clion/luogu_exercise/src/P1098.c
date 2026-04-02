#include <stdio.h>
#include <string.h>

#define MAX_LEN 500
#define MAX_RESULT 10000

// 判断是否是小写字母
int is_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

// 判断是否是数字
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

// 判断两个字符是否同类型（都是字母或都是数字）
int same_type(char a, char b) {
    return (is_letter(a) && is_letter(b)) || (is_digit(a) && is_digit(b));
}

// 获取填充字符（按 p1 转换）
char get_char(char c, int p1) {
    if (p1 == 3) return '*';                    // 星号
    if (p1 == 2 && is_letter(c)) return c - 32; // 转大写
    return c;                                   // 原样（小写或数字）
}

int main() {
    int p1, p2, p3;
    scanf("%d %d %d", &p1, &p2, &p3);
    
    char str[MAX_LEN];
    scanf("%s", str);
    
    char result[MAX_RESULT] = {0};
    int len = strlen(str);
    int res_idx = 0;  // 结果索引
    
    for (int i = 0; i < len; i++) {
        // 检查是否是有效的减号（不在开头结尾）
        int is_valid_dash = (str[i] == '-' && i > 0 && i < len - 1);
        
        if (is_valid_dash) {
            char left = str[i-1];
            char right = str[i+1];
            
            // 检查是否应该展开（同类型且右边大于左边）
            if (same_type(left, right) && right > left) {
                // 临时存储填充部分
                char fill[500] = {0};
                int fill_idx = 0;
                
                // 生成从 left+1 到 right-1 的所有字符
                for (char c = left + 1; c < right; c++) {
                    char fc = get_char(c, p1);
                    // 每个字符重复 p2 次
                    for (int k = 0; k < p2; k++) {
                        if (fill_idx < 499) {
                            fill[fill_idx++] = fc;
                        }
                    }
                }
                fill[fill_idx] = '\0';
                
                // 如果需要逆序
                if (p3 == 2) {
                    for (int j = 0; j < fill_idx / 2; j++) {
                        char t = fill[j];
                        fill[j] = fill[fill_idx - 1 - j];
                        fill[fill_idx - 1 - j] = t;
                    }
                }
                
                // 将填充部分加入结果
                for (int j = 0; j < fill_idx && res_idx < MAX_RESULT - 1; j++) {
                    result[res_idx++] = fill[j];
                }
                continue;  // 跳过这个减号
            }
        }
        
        // 普通字符直接加入结果
        if (res_idx < MAX_RESULT - 1) {
            result[res_idx++] = str[i];
        }
    }
    
    result[res_idx] = '\0';
    printf("%s\n", result);
    
    return 0;
}
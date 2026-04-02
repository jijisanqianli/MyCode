//额，这段程序我在vscode里编译运行后好像并没有编译错误，能够正常输出，略微改了一些可能出错的地方
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    //修改一
    const char *A = "I LOVE YOU";
    char *B = NULL;
    int length = strlen(A);
    
    // 分配足够的空间给B，包括空字符
    B = (char*)malloc((length + 1) * sizeof(char));
    //修改二
    if(B==NULL)
    {
        printf("内存分配失败");
        return -1;
    }
    
    char* dest = B;
    char* src = A; // 从字符串A的开头开始
    
    // 使用正确的逻辑来复制字符串
    while (*src != '\0') {
        *dest++ = *src++; // 复制字符并移动指针
    }
    *dest = '\0'; // 确保复制的字符串以空字符结尾
    
    printf("%s", B);
    free(B); // 释放分配的内存
    return 0;
}
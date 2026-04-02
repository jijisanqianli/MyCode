#include "seqlist.h"
#include <stdio.h>
#include <windows.h>

int main() {
    // 关键：设置控制台编码为GBK，匹配Windows默认编码
    SetConsoleOutputCP(CP_ACP);
    SetConsoleCP(CP_ACP); // 同时设置输入编码

    // 1. 创建空顺序表
    SeqList* list = createSeqList();
    // 2. 输入初始数据
    inputSeqList(list);
    printSeqList(list);

    // 3. 测试插入：在第2个位置（下标1）插入数字99
    printf("\n插入99到下标1的位置：\n");
    insertSeqList(list, 1, 99);
    printSeqList(list);

    // 4. 测试查找：找数字99的位置
    int pos = searchSeqList(list, 99);
    if (pos != -1) {
        printf("\n数字99的下标：%d\n", pos);
    } else {
        printf("\n未找到数字99！\n");
    }

    // 5. 测试修改：把下标1的元素改成88
    printf("\n修改下标1的元素为88：\n");
    updateSeqList(list, 1, 88);
    printSeqList(list);

    // 6. 测试删除：删除下标1的元素
    printf("\n删除下标1的元素：\n");
    deleteSeqList(list, 1);
    printSeqList(list);

    // 7. 销毁顺序表
    destroySeqList(list);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    SeqList* L = createSeqList();
    int index;
    printf("输入元素个数：\n");
    scanf("%d", &index);
    setSeqList(L, index);
    print_list(L);
    del_x2y(L,4,6);
    printf("\n");
    print_list(L);
    /*print_list(&list);
    printf("\n");
    del_dupnumPlus(&list);
    print_list(&list);*/

    /*print_list(&list);
    printf("\n");
    odd_even(&list);
    print_list(&list);*/
    return 0;
}
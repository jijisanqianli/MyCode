#ifndef LIST_H
#define LIST_H
//这里我把int作为这个类型
typedef int ElemType;

struct _lnklist{
    ElemType data;
    struct _lnklist *next;
};

typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;
void lnk_del_x2y(LinkList L, ElemType mink, ElemType maxk);

void printList(Node* head);
void lnk_merge(LinkList A, LinkList B, LinkList C);
int lnk_search(LinkList L, int k, ElemType* p_ele);

#endif //LIST_H
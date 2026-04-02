#ifndef LIST_H
#define LIST_H
typedef int ElemType;

typedef struct _QueueNode {
    ElemType data;          // 数据域
    struct _QueueNode *next;      // 指针域
}LinkQueueNode, *LinkQueue;

bool init_queue(LinkQueue *LQ);
bool enter_queue(LinkQueue *LQ, ElemType x);
bool leave_queue(LinkQueue *LQ, ElemType *x);
void print_queue(LinkQueue *LQ);

#define Stack_Size 50
typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

bool push(Stack* S, ElemType x);
bool pop(Stack* S, ElemType *x);
void init_stack(Stack *S);
int compute_reverse_polish_notation(char *str);

void print_str(char *str);
#endif //LIST_H
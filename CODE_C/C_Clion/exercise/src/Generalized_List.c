#include <stdio.h>
#include <stdlib.h>

typedef enum {
    ATOM,
    LIST
}ElemTag;

typedef struct GLNode{
    ElemTag tag;
    union {
        int atom;
        struct {
            struct GLNode *hp;
            struct GLNode *tp;
        }ptr;
    }val;
} *GList,GLNode;

int GListDepth(GList L) {
    // 1. 如果 L 为空，返回 1 (空表深度为1)
    if (!L) return 1;
    // 2. 如果 L 是原子，返回 0
    if (L->tag == ATOM) return 0;
    // 3. 如果 L 是子表，递归求 hp 的深度和 tp 的深度...
    // 核心：处理子表 (LIST)
    // 广义表的深度 = 1 + max(所有元素的深度)
    int dep_h = 0, dep_t = 0;
    // 1. 算出第一个元素的深度（注意：如果是原子，这里递归回来是0；如果是子表，则是子表深度）
    dep_h = GListDepth(L->val.ptr.hp) + 1;
    // 2. 算出后面剩余部分的深度
    // 注意：tail_pointer 指向的是“除去第一个后的表”，它这一层不增加深度
    dep_t = GListDepth(L->val.ptr.tp);
    // 3. 返回最大值
    return (dep_h > dep_t) ? dep_h : dep_t;
}

// 辅助函数：创建一个原子结点
GList CreateAtom(int char_val) {
    GList p = (GList)malloc(sizeof(GLNode));
    p->tag = ATOM;
    p->val.atom = char_val;
    return p;
}

// 辅助函数：创建一个表结点
GList CreateList(GList hp, GList tp) {
    GList p = (GList)malloc(sizeof(GLNode));
    p->tag = LIST;
    p->val.ptr.hp = hp;
    p->val.ptr.tp = tp;
    return p;
}

int main() {
    // 手动构建 (a, (b, c))
    // 第一步：构建最内层的 (b, c) -> 其实是 (b, (c, NULL))
    GList atom_c = CreateAtom('c');
    GList list_c = CreateList(atom_c, NULL); // 表 (c)

    GList atom_b = CreateAtom('b');
    GList sub_list = CreateList(atom_b, list_c); // 表 (b, c)

    // 第二步：构建外层 (a, sub_list) -> 其实是 (a, (sub_list, NULL))
    GList list_sub = CreateList(sub_list, NULL); // 表 ((b, c))

    GList atom_a = CreateAtom('a');
    GList L = CreateList(atom_a, list_sub); // 最终表 (a, (b, c))

    // 第三步：测试深度
    printf("广义表 (a, (b, c)) 的深度是: %d\n", GListDepth(L));
    // 预期输出：2

    return 0;
}

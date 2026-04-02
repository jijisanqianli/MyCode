#include "dsstring.h"

Block* create_block() {
    Block* block = (Block*)malloc(sizeof(Block));
    for (int i=0;i<BLOCK_SIZE;i++) {
        block->ch[i]=BLS_BLANK;
    }
    block->next=NULL;
    return block;
}

bool blstr_substr(BLString src, int pos, int len, BLString *sub) {
    if (pos < 0 || pos >= src.len || len < 0) return false;
    if (pos + len > src.len) len = src.len - pos; // 有多少取多少
    if (len == 0) return false;

    int go_count = pos / BLOCK_SIZE;
    Block* traverse_object = src.head;
    while (go_count > 0) {
        traverse_object = traverse_object->next;
        go_count--;
    }
    int src_idx = pos % BLOCK_SIZE;

    Block* sub_block = NULL;
    while (true) {
        if (sub->head == NULL) {
            sub_block = create_block();
            sub->head = sub_block;
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            sub_block->ch[j] = traverse_object->ch[src_idx];
            (sub->len)++;
            src_idx++;
            len--;
            if (len == 0) {
                sub->tail = sub_block;
                return true;
            }
            if (src_idx > BLOCK_SIZE - 1) {
                src_idx = 0;
                traverse_object = traverse_object->next;
            }
        }
        sub_block->next = create_block();
        sub_block = sub_block->next;
    }
}
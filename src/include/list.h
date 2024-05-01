#ifndef TAC_LIST_H
#define TAC_LIST_H
#include <stdlib.h>

/**
 * 定义一个容器结构，items是不定类型的二维数组，它的元素使一个item指针
 * size 表示容器中元素的数量————item的数量
 * item_size 表示每个元素的大小，这个值是固定的，在init_list的时候就指定了
*/
typedef struct LIST_STRUCT{
    void** items;
    size_t size;
    size_t item_size;
}list_T;

// 初始化list 容器的参数，确定item的大小
list_T* init_list(size_t item_size);

// 将元素填充至容器中
void list_push(list_T* list, void* item);


#endif
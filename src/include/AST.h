#ifndef TAC_AST_H
#define TAC_AST_H
#include "list.h"

typedef struct AST_STRUCT
{
    enum{
        AST_COMPOUND,
        AST_ASSIGNMENT,
        AST_FUNCTION,
        AST_CALL,
        AST_INT,
        AST_DEFINITION_TYPE,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_NOOP,
    }type;
    list_T* children;
    char* name;                // name 存储的是当前ast节点的token-value
    struct AST_STRUCT* value;  // 用这个value值存储subnode
    int int_value;
    int data_type;             // 如果是单个token的话，存储token-type，如果是多个token组合，则存储token_type的替换值：如Array<string>
} AST_T;

AST_T* init_ast(int type);

#endif
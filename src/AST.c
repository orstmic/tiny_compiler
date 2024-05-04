#include "include/AST.h"

AST_T* init_ast(int type)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    // 只有当前的ast节点是一个集合的时候，才会为当前节点初始化一个动态列表容器。
    if(type == AST_COMPOUND)
    {
        ast->children = init_list(sizeof(struct AST_STRUCT*));
    }

    return ast;
}

const char* ast_type_to_str(int type)
{
    switch(type){
        case        AST_COMPOUND:               return "AST_COMPOUND";
        case        AST_ASSIGNMENT:             return "AST_ASSIGNMENT";
        case        AST_FUNCTION:               return "AST_FUNCTION";
        case        AST_CALL:                   return "AST_CALL";
        case        AST_INT:                    return "AST_INT";
        case        AST_DEFINITION_TYPE:        return "AST_DEFINITION_TYPE";
        case        AST_VARIABLE:               return "AST_VARIABLE";
        case        AST_STATEMENT:              return "AST_STATEMENT";
        case        AST_NOOP:                   return "AST_NOOP";
    }

    return "not_stringable";
}
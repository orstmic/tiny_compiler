#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/AST.h"

parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_next_token(lexer);

    return parser;
}
/**
 * 该函数的作用是让当前的lexer指向下一个token
 * 更新parser
*/
token_T* parser_eat(parser_T* parser, int type)
{
    if(parser->token->type != type)
    {
        printf("[Parser]: Unexpected token: `%s`, was expected: `%s`\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    parser->token = lexer_next_token(parser->lexer);
    return parser->token;
}


AST_T* parser_parse(parser_T* parser)
{
    return parser_parse_compound(parser);
}

AST_T* parser_parse_id(parser_T* parser)
{
    // 拿到当前parser所指向的token—value
    char* value = calloc(strlen(parser->token->value) + 1, sizeof(char));
    strcpy(value, parser->token->value);
    
    parser_eat(parser, TOKEN_ID);

    if(parser->token->type == TOKEN_EQUALS)
    {
        // parse assignment 赋值
        // 首先要吞噬掉等号
        parser_eat(parser, TOKEN_EQUALS);
        AST_T* ast = init_ast(AST_ASSIGNMENT);
        ast->name = value;
        ast->value = parser_parse_expr(parser);

        return ast;
    }

    // 否则，当前的ID为变量，下面对变量进行解析
    AST_T* ast = init_ast(AST_VARIABLE);
    ast->name = value;
    return ast;

}

AST_T* parser_parse_list(parser_T* parser)
{
    // 如果当前token是`(`，说明下面的内容又是一个小集合体
    // 先吞噬掉`(`
    parser_eat(parser,TOKEN_LPAREN);


    AST_T* compound = init_ast(AST_COMPOUND);
    
    // 先将第一个ast节点收容到list容器中，如果下面还有TOKEN_COMMA，再将后面的一并收入容器
    list_push(compound->children, parser_parse_expr(parser));

    while(parser->token->type == TOKEN_COMMA)
    {
        parser_eat(parser, TOKEN_COMMA);
        list_push(compound->children, parser_parse_expr(parser));
    }

    // 最后吞噬掉`)`
    parser_eat(parser, TOKEN_RPAREN);

    return compound;
}

/**
 * 不断判断当前token是哪种类型，下面分为四种
 * 1.如果是英文字母：a.赋值语句 b.定义变量
 * 2.
*/
AST_T* parser_parse_expr(parser_T* parser)
{
    switch(parser->token->type)
    {
        case TOKEN_ID: return parser_parse_id(parser);
        case TOKEN_LPAREN: return parser_parse_list(parser);
        default: 
        {
            printf("[Parser]: Unexpected token `%s`\n", token_to_str(parser->token)); 
            exit(1);
        }
    }
}

AST_T* parser_parse_compound(parser_T* parser)
{

    // 初始化ast节点的同时，初始化该节点存储子节点的容器【list_T】
    AST_T* compound = init_ast(AST_COMPOUND);

    while(parser->token->type != TOKEN_EOF)
    {
        /**
         * 如果不加判断的话，如下，就会进入死循环
         * 不断在parser_parse和parser_parse_compound之间来回跑
        */
        // AST_T* child = parser_parse(parser);
        // list_push(compound->children, child);

        // 因此让它进入parser_parse_expr
        AST_T* child = parser_parse_expr(parser);
        list_push(compound->children, child);
    }

    return compound;
}
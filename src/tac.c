#include "include/tac.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include <string.h>
#include <stdlib.h>
#include "include/as_frontend.h"

static char* sh(const char* cmd)
{
    char* output = (char*) calloc(1, sizeof(char));
    output[0] = '\0';

    FILE* fp;
    char* path[1035];

    fp = popen(cmd, "r");
    if(fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while(fgets(path, sizeof(path), fp) != NULL)
    {
        output = (char*) realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
        strcat(output, path);
    }
    pclose(fp);
    return output;

}

void tac_compile(char* src)
{
    lexer_T* lexer = init_lexer(src);
    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    
    char* s = as_f_root(root);
    tac_write_file("a.s", s);
    sh("as a.s -o a.o");
    sh("ld a.o -o a.out");

    // printf("%s\n", s);
}


void tac_compile_file(const char* filename)
{
    char* src = tac_read_file(filename);
    tac_compile(src);
    free(src);
}
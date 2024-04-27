#include "include/tac.h"
#include "include/lexer.h"
#include "include/io.h"
#include <stdlib.h>

void tac_compile(char* src)
{
    lexer_T* lexer = init_lexer(src);
    token_T* tok = 0;

    while((tok = lexer_next_token(lexer))->type != TOKEN_EOF)
    {
        printf("%s", token_to_str(tok));
    }
}


void tac_compile_file(const char* filename)
{
    char* src = tac_read_file(filename);
    tac_compile(src);
    free(src);
}
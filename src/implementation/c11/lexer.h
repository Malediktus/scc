#ifndef LEXER_H
#define LEXER_H

#include "../../compiler/compiler.h"

void c11_init_lexer(lexer_t *lexer, const char *text, const char *filepath);
void c11_deinit_lexer(lexer_t *lexer);
token_t *c11_lex(lexer_t *lexer);

static lexer_impl_t c11_lexer = {c11_init_lexer, c11_deinit_lexer, c11_lex};

#endif
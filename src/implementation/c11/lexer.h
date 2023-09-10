#ifndef LEXER_H
#define LEXER_H

#include "../../compiler/compiler.h"

void c11_init_lexer(compiler_t *compiler, const char *text, const char *filepath);
void c11_deinit_lexer(compiler_t *compiler);
token_t *c11_lex(compiler_t *compiler);

static lexer_impl_t c11_lexer = {c11_init_lexer, c11_deinit_lexer, c11_lex};

#endif
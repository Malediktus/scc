#ifndef PARSER_H
#define PARSER_H

#include "../../compiler/compiler.h"
#include "../../ast/ast.h"

void c11_init_parser(compiler_t *compiler);
void c11_deinit_parser(compiler_t *compiler);
AST_node_t *c11_parse(compiler_t *compiler);

static parser_impl_t c11_parser = {c11_init_parser, c11_deinit_parser, c11_parse};

#endif
#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>
#include <stdlib.h>
#include "../utils/vec.h"

struct AST_node;

typedef struct
{
  char *filepath;
  uint32_t line;
  uint32_t column;
} position_t;

position_t *position_create(const char *filepath, uint32_t line, uint32_t column);
void position_delete(position_t *position);

typedef enum
{
  TOK_NONE = 0,
} token_type_t;

typedef struct
{
  token_type_t type;
  char *text;
  position_t *start;
  position_t *end;
} token_t;

token_t *token_create(token_type_t type, const char *text, position_t *start, position_t *end);
void token_delete(token_t *token);

struct compiler;

typedef struct
{
  void (*init_lexer)(struct compiler *compiler, const char *text, const char *filepath);
  void (*deinit_lexer)(struct compiler *compiler);

  token_t *(*lex)(struct compiler *compiler);
} lexer_impl_t;

typedef struct
{
  lexer_impl_t *implementation;
  char *text;
  position_t *position;
  size_t index;
} lexer_t;

lexer_t *lexer_create(lexer_impl_t *implementation);
void lexer_delete(lexer_t *lexer);

typedef struct
{
  void (*init_parser)(struct compiler *compiler);
  void (*deinit_parser)(struct compiler *compiler);

  struct AST_node *(*parse)(struct compiler *compiler);
} parser_impl_t;

typedef struct
{
  parser_impl_t *implementation;
} parser_t;

parser_t *parser_create(parser_impl_t *implementation);
void parser_delete(parser_t *parser);

typedef struct compiler
{
  lexer_t *lexer;
  parser_t *parser;
} compiler_t;

compiler_t *compiler_create(lexer_t *lexer, parser_t *parser);
void compiler_delete(compiler_t *compiler);

typedef struct
{
  char *input_filepath;
  char *output_filepath;
  compiler_t *compiler;
} compilation_process_t;

compilation_process_t *compilation_process_create(const char *input_filepath, const char *output_filepath, compiler_t *compiler);
void compilation_process_delete(compilation_process_t *compilation_process);

#endif
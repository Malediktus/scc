#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>
#include <stdlib.h>
#include "../utils/vec.h"

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

struct lexer;

typedef struct
{
  void (*init_lexer)(struct lexer *lexer, const char *text, const char *filepath);
  void (*deinit_lexer)(struct lexer *lexer);

  token_t *(*lex)(struct lexer *lexer);
} lexer_impl_t;

typedef struct lexer
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
  lexer_t *lexer;
} compiler_t;

compiler_t *compiler_create(lexer_t *lexer);
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
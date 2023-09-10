#include "compiler.h"
#include <string.h>
#include <assert.h>

position_t *position_create(const char *filepath, uint32_t line, uint32_t column)
{
  position_t *position = malloc(sizeof(position_t));
  position->filepath = malloc(strlen(filepath) + 1);
  strcpy(position->filepath, filepath);
  position->line = line;
  position->column = column;

  return position;
}

void position_delete(position_t *position)
{
  assert(position);
  assert(position->filepath);
  free(position->filepath);
  free(position);
}

token_t *token_create(token_type_t type, const char *text, position_t *start, position_t *end)
{
  token_t *token = malloc(sizeof(token_t));
  token->text = malloc(strlen(text) + 1);
  strcpy(token->text, text);
  token->type = type;
  token->start = start;
  token->end = end;

  return token;
}

void token_delete(token_t *token)
{
  assert(token);
  assert(token->text);
  free(token->text);
  free(token);
}

lexer_t *lexer_create(lexer_impl_t *implementation)
{
  lexer_t *lexer = malloc(sizeof(lexer_t));
  lexer->implementation = implementation;

  return lexer;
}

void lexer_delete(lexer_t *lexer)
{
  assert(lexer);
  free(lexer);
}

parser_t *parser_create(parser_impl_t *implementation)
{
  parser_t *parser = malloc(sizeof(parser_t));
  parser->implementation = implementation;

  return parser;
}

void parser_delete(parser_t *parser)
{
  assert(parser);
  free(parser);
}

compiler_t *compiler_create(lexer_t *lexer, parser_t *parser)
{
  compiler_t *compiler = malloc(sizeof(compiler_t));
  compiler->lexer = lexer;
  compiler->parser = parser;

  return compiler;
}

void compiler_delete(compiler_t *compiler)
{
  assert(compiler);
  assert(compiler->lexer);
  lexer_delete(compiler->lexer);
  free(compiler);
}

compilation_process_t *compilation_process_create(const char *input_filepath, const char *output_filepath, compiler_t *compiler)
{
  compilation_process_t *compilation_process = malloc(sizeof(compilation_process_t));
  compilation_process->input_filepath = malloc(strlen(input_filepath) + 1);
  strcpy(compilation_process->input_filepath, input_filepath);
  compilation_process->output_filepath = malloc(strlen(output_filepath) + 1);
  strcpy(compilation_process->output_filepath, output_filepath);
  compilation_process->compiler = compiler;

  return compilation_process;
}

void compilation_process_delete(compilation_process_t *compilation_process)
{
  assert(compilation_process);
  assert(compilation_process->input_filepath);
  assert(compilation_process->output_filepath);

  free(compilation_process);
  free(compilation_process->output_filepath);
  free(compilation_process->input_filepath);
}

#include "lexer.h"
#include <assert.h>

void c11_init_lexer(compiler_t *compiler, const char *text, const char *filepath)
{
  compiler->lexer->text = malloc(strlen(text) + 1);
  strcpy(compiler->lexer->text, text);
  compiler->lexer->position = position_create(filepath, 1, 1);
  compiler->lexer->index = 0;
}

void c11_deinit_lexer(compiler_t *compiler)
{
  assert(compiler->lexer->text);
  assert(compiler->lexer->position);
  position_delete(compiler->lexer->position);
  free(compiler->lexer->text);
}

token_t *c11_lex(compiler_t *compiler)
{
  (void)compiler;
  return NULL;
}

#include "lexer.h"
#include <assert.h>

void c11_init_lexer(lexer_t *lexer, const char *text, const char *filepath)
{
  lexer->text = malloc(strlen(text) + 1);
  strcpy(lexer->text, text);
  lexer->position = position_create(filepath, 1, 1);
  lexer->index = 0;
}

void c11_deinit_lexer(lexer_t *lexer)
{
  assert(lexer->text);
  assert(lexer->position);
  position_delete(lexer->position);
  free(lexer->text);
}

token_t *c11_lex(lexer_t *lexer)
{
  (void)lexer;
  return NULL;
}

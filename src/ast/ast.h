#ifndef AST_H
#define AST_H

#include <stdint.h>
#include "../utils/vec.h"
#include "../compiler/compiler.h"

typedef enum
{
  NODE_HEAD
} node_type_t;

typedef struct
{
  node_type_t type;
  uint32_t level;
  vec_void_t children;
  vec_void_t tokens;
  void *parent;
} AST_node_t;

AST_node_t *AST_node_create(node_type_t type);
void AST_node_delete(AST_node_t *node);

typedef struct
{
  AST_node_t *head;
  AST_node_t *current;
  uint32_t level;
} AST_builder_t;

typedef struct
{
  uint32_t level;
  uint32_t num_children;
} checkpoint_t;

AST_builder_t *AST_builder_create();
void AST_builder_delete(AST_builder_t *builder);
AST_node_t *AST_builder_finish_tree(AST_builder_t *builder);
void AST_builder_begin(AST_builder_t *builder, node_type_t type);
void AST_builder_finish(AST_builder_t *builder);
void AST_build_add_token(AST_builder_t *builder, token_t *token);
checkpoint_t AST_builder_checkpoint(AST_builder_t *builder);
void AST_builder_begin_at(AST_builder_t *builder, checkpoint_t checkpoint, node_type_t type);

#endif
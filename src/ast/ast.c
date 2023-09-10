#include "ast.h"
#include <assert.h>

AST_node_t *AST_node_create(node_type_t type)
{
  AST_node_t *node = malloc(sizeof(AST_node_t));
  node->type = type;
  node->level = 0;
  node->parent = NULL;
  vec_init(&node->children);
  vec_init(&node->tokens);

  return node;
}

void AST_node_delete(AST_node_t *node)
{
  assert(node);
  vec_deinit(&node->children);
  vec_deinit(&node->tokens);
  free(node);
}

AST_builder_t *AST_builder_create()
{
  AST_builder_t *builder = malloc(sizeof(AST_builder_t));
  AST_node_t *node = AST_node_create(NODE_HEAD);

  builder->head = node;
  builder->current = node;
  builder->level = 0;

  return builder;
}

void AST_builder_delete(AST_builder_t *builder)
{
  free(builder);
}

AST_node_t *AST_builder_finish_tree(AST_builder_t *builder)
{
  assert(builder->level == 0);
  assert(builder->head == builder->current);
  return builder->head;
}

void AST_builder_begin(AST_builder_t *builder, node_type_t type)
{
  builder->level++;
  AST_node_t *node = AST_node_create(type);
  node->level = builder->level;
  node->parent = builder->current;

  vec_push(&builder->current->children, node);
  builder->current = node;
}

void AST_builder_finish(AST_builder_t *builder)
{
  assert(builder->level > 0);
  builder->level--;
  builder->current = builder->current->parent;
}

void AST_build_add_token(AST_builder_t *builder, token_t *token)
{
  vec_push(&builder->current->tokens, token);
}

checkpoint_t AST_builder_checkpoint(AST_builder_t *builder)
{
  checkpoint_t result = {builder->current->level, builder->current->children.length};
  return result;
}

void AST_builder_begin_at(AST_builder_t *builder, checkpoint_t checkpoint, node_type_t type)
{
  assert(builder->level == checkpoint.level);
  builder->level++;

  AST_node_t *node = AST_node_create(type);
  node->parent = builder->current;
  node->level = builder->level;

  int i;
  AST_node_t *child;
  vec_foreach(&builder->current->children, child, i)
  {
    vec_push(&node->children, child);
  }
  vec_splice(&builder->current->children, 0, checkpoint.num_children);
  vec_splice(&node->children, checkpoint.num_children + 1, node->children.length - checkpoint.num_children);
  vec_push(&builder->current->children, node);
  builder->current = node;

  vec_foreach(&builder->current->children, child, i)
  {
    child->parent = node;
    child->level = builder->level + 1;
  }
}

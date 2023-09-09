#ifndef ARGS_H
#define ARGS_H

#include <stdint.h>
#include <stdbool.h>
#include "vec.h"

typedef struct
{
  bool generate_symbols;
  uint8_t optimization_level;
  const char *output_filepath;
  vec_str_t enabled_warnings;
  vec_str_t disabled_warnings;
  vec_str_t input_filepaths;
} options;

static options opts;

void print_version(void);
void print_help(void);
void init_options(int argc, char **argv);
void free_options(void);

#endif
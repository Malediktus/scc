#include <stdio.h>
#include "utils/args.h"
#include "compiler/compiler.h"
#include "implementation/c11/lexer.h"

void compile_file(char *filepath)
{
  compiler_t *compiler = compiler_create(lexer_create(&c11_lexer));
  compilation_process_t *process = compilation_process_create(filepath, opts.output_filepath, compiler);
  FILE *fp = fopen(filepath, "r");
  // TODO: Check if is open
  fseek(fp, 0, SEEK_END);
  size_t filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *text = malloc(filesize + 1);
  fread(text, filesize, 1, fp);
  fclose(fp);
  compiler->lexer->implementation->init_lexer(compiler->lexer, text, filepath);

  free(text);
  compilation_process_delete(process);
  compiler_delete(compiler);
}

int main(int argc, char *argv[])
{
  init_options(argc, argv);

  int i;
  char *filepath;
  vec_foreach(&opts.input_filepaths, filepath, i)
  {
    compile_file(filepath);
  }

  free_options();
  return 0;
}

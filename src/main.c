#include "args.h"

int main(int argc, char *argv[])
{
  init_options(argc, argv);
  free_options();
  return 0;
}

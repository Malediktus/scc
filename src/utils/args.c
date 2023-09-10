#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include "args.h"

void print_version(void)
{
  printf("scc 1.0\n"
         "Copyright (C) 2023 Nico Grundei\n"
         "This is free software; see the source for copying conditions.  There is NO\n"
         "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
  exit(0);
}

void print_help(void)
{
  printf("Usage: scc [options] file...\n"
         "Options:\n"
         "  --help\t\t\tDisplay this page\n"
         "  -h\t\t\t\tShort for --help\n"
         "  --version\t\t\tDisplay version information\n"
         "  -v\t\t\t\tShort for --version\n"
         "  -g\t\t\t\tGenerate debug symbols\n"
         "  -O level\t\t\tOptimization level (0-9)\n"
         "  -o file\t\t\tOutput file\n"
         "  -W warning\t\t\tEnable warning\n"
         "  -Wno file\t\t\tDisable warning\n"
         "  -Werror file\t\t\tTreat warnings as errors\n"
         "  -Wall file\t\t\tEnable all warnings\n");
  exit(0);
}

void init_options(int argc, char **argv)
{
  int opt;
  int option_index = 0;

  static struct option long_options[] = {
      {"version", no_argument, 0, 'v'},
      {"help", no_argument, 0, 'h'},
      {0, 0, 0, 0}};

  vec_init(&opts.enabled_warnings);
  vec_init(&opts.disabled_warnings);
  vec_init(&opts.input_filepaths);

  opts.output_filepath = "a.out";
  opts.generate_symbols = false;
  opts.optimization_level = 0;

  while ((opt = getopt_long(argc, argv, "gvhO:W:o:", long_options, &option_index)) != -1)
  {
    switch (opt)
    {
    case 'g':
      opts.generate_symbols = true;
      break;
    case 'v':
      print_version();
      break;
    case 'h':
      print_help();
      break;
    case 'o':
      opts.output_filepath = optarg;
      break;
    case 'W':
      if (strncmp(optarg, "no", 2) == 0)
      {
        vec_push(&opts.disabled_warnings, optarg + 2);
      }
      else
      {
        vec_push(&opts.enabled_warnings, optarg);
      }
      break;
    case 'O':
      if (strlen(optarg) != 1 || !isdigit(optarg[0]))
      {
        fprintf(stderr, "Unknown option: %s\n", argv[optind - 1]);
        print_help();
        break;
      }

      opts.optimization_level = atoi(optarg);
      break;

    case '?':
      fprintf(stderr, "Unknown option: %s\n", argv[optind - 1]);
      print_help();
      break;
    default:
      break;
    }
  }

  for (int i = optind; i < argc; i++)
  {
    vec_push(&opts.input_filepaths, argv[i]);
  }
}

void free_options(void)
{
  vec_deinit(&opts.enabled_warnings);
  vec_deinit(&opts.disabled_warnings);
  vec_deinit(&opts.input_filepaths);
}

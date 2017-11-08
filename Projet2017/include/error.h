
#ifndef ERROR_IS_DEF
#define ERROR_IS_DEF


#include <stdlib.h>
#include <stdio.h>

#define exit_with_error(...) do { \
    fprintf(stderr, "Error: " __VA_ARGS__); \
    exit(EXIT_FAILURE); \
  } while(0)


#endif

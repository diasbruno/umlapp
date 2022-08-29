#include <stdint.h>
#include <stdlib.h>
#include "./command_options.h"

struct command_option_t* command_option_by_shortname(void* command, void* s) {
  struct command_option_t* x = command;
  char n = (char)((intptr_t)s);

  if (x->shortname == n) {
    return x;
  }

  return NULL;
}

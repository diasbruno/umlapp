#include <stdbool.h>
#include <stdint.h>
#include "./command_options.h"

bool command_option_by_shortname(array_item_t command, array_user_data_t s) {
  struct command_option_t* x = command;
  char n = (char)((intptr_t)s);
  return x->shortname == n;
}

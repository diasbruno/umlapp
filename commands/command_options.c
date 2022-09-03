#include <stdbool.h>
#include <stdint.h>

#include "./command_options.h"

#define TO_SHORTNAME(x) ((char)(intptr_t)x)

bool command_option_by_shortname(array_item_t command, array_user_data_t s) {
  return ((command_option_t*)command)->shortname == TO_SHORTNAME(s);
}

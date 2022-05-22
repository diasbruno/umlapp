#include <stdint.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <sdk/command_options.h>

struct command_option_t* command_option_by_shortname(void* command, void* s) {
  struct command_option_t* x = command;
  char n = (char)((intptr_t)s);

  g_print("finding command (%c,%c)\n", x->shortname, n);
  
  if (x->shortname == n) {
    return x;
  }

  return NULL;
}

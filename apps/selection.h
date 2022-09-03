#ifndef _01G3PNGH90T4EK44TZ3XV8B1EX_
#define _01G3PNGH90T4EK44TZ3XV8B1EX_ 1

#include <geometry/frame.h>
#include <collections/array.h>

struct selection_state_t {
  struct pos_t start;
  struct pos_t end;
  int selecting;
};

void register_selection_command_option(struct array_t* a);

#endif

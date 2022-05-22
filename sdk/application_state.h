#ifndef _01G3PNEYAV29ZYWS6PWQQQN5KK_
#define _01G3PNEYAV29ZYWS6PWQQQN5KK_ 1

#include <gtk/gtk.h>
#include <sdk/types.h>
#include <sdk/array.h>
#include <sdk/command_options.h>

typedef struct command_state_t* command_state_t;

struct application_t {
  struct command_option_t* command;
  command_state_t command_state;
  struct array_t* commands;
  struct array_t* selected;
  struct array_t* objects;
  struct array_t* frames;
  GtkWidget* canvas;
};

#endif

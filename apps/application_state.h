#ifndef _01G3PNEYAV29ZYWS6PWQQQN5KK_
#define _01G3PNEYAV29ZYWS6PWQQQN5KK_ 1

#include <gtk/gtk.h>
#include <base/type.h>
#include <collections/array.h>
#include <commands/command_options.h>

typedef struct application_t {
  command_option_t* command;
  any command_state;
  array_t* commands;
  array_t* selected;
  array_t* objects;
  array_t* frames;
  GtkWidget* canvas;
} application_t;

#endif

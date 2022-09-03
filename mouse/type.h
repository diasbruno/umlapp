#ifndef _01GC0N5AHXMRVTQM5Q2RCC0C86_
#define _01GC0N5AHXMRVTQM5Q2RCC0C86_ 1

#include <gdk/gdk.h>

typedef struct mouse_click_t {
  gint n_press;
  gdouble x;
  gdouble y;
  gpointer state;
} mouse_click_t;

#endif

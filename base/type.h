#ifndef _01G3PS7S4Y9MP10354R7YXT1F5_
#define _01G3PS7S4Y9MP10354R7YXT1F5_ 1

#include <stdlib.h>
#include <gdk/gdk.h>

#include <geometry/frame.h>

#define EXISTS(x) ((x) != NULL)

typedef int element_kind_t;

struct line_t {
  int size;
  struct pos_t* ps;
};

struct mouse_click_t {
  gint n_press;
  gdouble x;
  gdouble y;
  gpointer state;
};

#endif

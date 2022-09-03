#include <collections/array.h>
#include <geometry/frame.h>
#include <commands/command_options.h>
#include <mouse/type.h>

#include "./application_state.h"
#include "./creation.h"

static void
init(any s) {}

static void
finish(any s) {}

static void
draw(any s, any cr) {}

static void
key_execute(any s, any data) {}

static void
motion_execute(any s, any data) {}

static void
mouse_pressed_execute(any s, any data) {
  application_t* a = s;
  mouse_click_t* p = data;


  frame_t* f = frame_with_pos_size(p->x, p->y,
				   DEFAULT_OBJECT_WIDTH,
				   DEFAULT_OBJECT_HEIGHT);

  array_push(a->frames, f);

  gtk_widget_queue_draw(a->canvas);
}

static void
mouse_released_execute(any s, any data) {}

static command_option_t opt = {
  draw,
  init,
  finish,
  key_execute,
  motion_execute,
  mouse_pressed_execute,
  mouse_released_execute,
  "creation",
  'c'
};

void register_creation_command_option(array_t* a) {
  array_push(a, &opt);
}

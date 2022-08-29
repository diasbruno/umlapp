#include <cairo.h>
#include <base/type.h>
#include <collections/array.h>
#include <geometry/frame.h>
#include <commands/command_options.h>

#include "./application_state.h"
#include "./selection.h"

#define TO_SELECTION(x) ((struct selection_state_t*)(x))

struct selection_state_t {
  struct pos_t start;
  struct pos_t end;
  int selecting;
};

static struct selection_state_t*
state_new(void) {
  return malloc(sizeof(struct selection_state_t));
}

static void init(struct application_t *s) {
  g_print("selection init\n");
}

static void finish(struct application_t *s) {
  g_print("selection finish\n");
  free((struct selection_state_t*)s->command_state);
}

static void draw(struct application_t *s, void* cr) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  if (!EXISTS(c)) {
    return;
  }

  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 1);
  cairo_rectangle(cr, c->start.x, c->start.y,
		  c->end.x - c->start.x,
		  c->end.y - c->start.y);
  cairo_stroke(cr);
  cairo_restore(cr);
}

static void
key_execute(struct application_t *s, void *data) {
}

static void
motion_execute(struct application_t *s, void *data) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  if (!EXISTS(c) || c->selecting == 0) {
    return;
  }

  struct mouse_click_t* p = data;

  c->end.x = p->x;
  c->end.y = p->y;

  gtk_widget_queue_draw(s->canvas);
}


static void
mouse_pressed_execute(struct application_t *s, void *data) {
  struct mouse_click_t* p = data;

  struct selection_state_t* c = TO_SELECTION(s->command_state);

  if (!EXISTS(c)) {
    c = state_new();
  }

  c->selecting = 1;

  c->start.x = p->x;
  c->start.y = p->y;
  c->end.x = p->x;
  c->end.y = p->y;

  s->command_state = (struct command_state_t*)c;
}

static void* find_frames_by_pos(void *acc, void *i, void *s) {
  struct mouse_click_t* p = s;
  struct array_t* a = acc;
  struct frame_t* f = i;
  struct pos_t ps = {
    .x = p->x,
    .y = p->y
  };

  int x = frame_is_pos_inside(f, &ps);
  if (x == 0) {
    array_push(a, f);
  }

  return a;
}

static void
mouse_released_execute(struct application_t *s, void *data) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  if (!EXISTS(c)) {
    return;
  }

  c->selecting = 0;

  struct array_t* t = array_with_capacity(s->frames->count,
					  s->frames->dealloc);
  t = array_reduce(s->frames, find_frames_by_pos, t, data);

  array_foreach(t, (array_mapper_t)print_frame, NULL);

  gtk_widget_queue_draw(s->canvas);
}

static struct command_option_t opt = {
  draw,
  init,
  finish,
  key_execute,
  motion_execute,
  mouse_pressed_execute,
  mouse_released_execute,
  "selection",
  's'
};

void register_selection_command_option(struct array_t* a) {
  array_push(a, &opt);
}

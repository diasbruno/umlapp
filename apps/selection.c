#include <cairo.h>
#include <base/type.h>
#include <commands/command_options.h>

#include "./application_state.h"
#include "./selection.h"

#define TO_SELECTION(x) ((struct selection_state_t*)(x))

static inline struct selection_state_t*
state_new(void) {
  return malloc(sizeof(struct selection_state_t));
}

static void
init(struct application_t *s) {
  s->command_state = (struct command_state_t*)state_new();
}

static void
finish(struct application_t *s) {
  free((struct selection_state_t*)s->command_state);
}

static void
draw(struct application_t *s, void* cr) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 1);
  cairo_rectangle(cr, c->start.x, c->start.y,
		  c->end.x - c->start.x,
		  c->end.y - c->start.y);
  cairo_stroke(cr);
  cairo_restore(cr);
}

static void
key_execute(struct application_t *s, void *data) {}

static void
motion_execute(struct application_t *s, void *data) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  if (c->selecting == 0) {
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

  c->selecting = 1;

  c->start.x = p->x;
  c->start.y = p->y;
  c->end.x = p->x;
  c->end.y = p->y;
}

static array_item_t
find_frames_by_pos(array_reducer_acc_t acc,
				       array_item_t i,
				       array_user_data_t s) {
  struct mouse_click_t* p = s;
  struct array_t* a = acc;
  struct frame_t* f = i;
  struct pos_t ps = {
    .x = p->x,
    .y = p->y
  };

  if (frame_is_pos_inside(f, &ps) == true) {
    array_push(a, f);
  }

  return a;
}

static void
mouse_released_execute(struct application_t *s, void *data) {
  struct selection_state_t* c = TO_SELECTION(s->command_state);

  c->selecting = 0;

  struct array_t* t = array_with_capacity(s->frames->count,
					  s->frames->dealloc);
  s->selected =
    array_reduce(s->frames, find_frames_by_pos, t, data);

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

void
register_selection_command_option(struct array_t* a) {
  array_push(a, &opt);
}

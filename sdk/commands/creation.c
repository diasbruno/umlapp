#include <sdk/application_state.h>
#include <sdk/array.h>
#include <sdk/commands/creation.h>
#include <sdk/command_options.h>
#include <sdk/frame.h>

static void
init(struct application_t *s) {}

static void finish(struct application_t *s) {}

static void draw(struct application_t *s, cairo_t* cr) {}

static void key_execute(struct application_t *s, void *data) {}

static void motion_execute(struct application_t *s, void *data) {}

static void mouse_pressed_execute(struct application_t *s, void *data) {
  struct mouse_click_t* p = data;

  struct frame_t* f = frame_with_pos_size(p->x, p->y,
					  DEFAULT_OBJECT_WIDTH,
					  DEFAULT_OBJECT_HEIGHT);

  array_push(s->frames, f);

  gtk_widget_queue_draw(s->canvas);
}

static void mouse_released_execute(struct application_t *s, void *data) {
}

static struct command_option_t opt = {
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

void register_creation_command_option(struct array_t* a) {
  array_push(a, &opt);
}

// use case:
//
// the user has clicked on the position
// it must create the element.

// flow:

// - user hit 'c' to create
// - user selected the type of object
// - user clicked on the position to create

#include <assert.h>
#include <stdlib.h>
#include <collections/array.h>
#include <geometry/frame.h>

#include "../application_state.h"
#include "../creation.h"

enum diagram_type_t {
  NONE = 0, // unused
  IF = 1,
};

struct create_command_t {
  int x, y;
  enum diagram_type_t type;
};

struct create_command_t*
create_command_new(int x, int y, enum diagram_type_t d) {
  struct create_command_t* s = malloc(sizeof(struct create_command_t));
  s->x = x;
  s->y = y;
  s->type = d;
  return s;
}

struct object_t* create_object_of(enum diagram_type_t d) {
  return 0;
}

int apply_create_command(struct create_command_t *c,
			 struct application_t *a) {
  struct object_t* o = create_object_of(c->type);
  struct frame_t* f = frame_with_pos_size(c->x, c->y,
					  DEFAULT_OBJECT_WIDTH,
					  DEFAULT_OBJECT_HEIGHT);
  array_push(a->objects, o);
  array_push(a->frames, f);

  return 0;
}

int main(void) {
  struct create_command_t* s =
    create_command_new(0, 0, 1);

  struct application_t* state =
    malloc(sizeof(struct application_t*));

  state->frames = array_new(free);
  state->objects = array_new(free);

  apply_create_command(s, state);

  assert(state->frames->count == 1);
  assert(state->objects->count == 1);

  return 0;
}

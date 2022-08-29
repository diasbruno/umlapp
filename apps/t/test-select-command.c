// use case:
//
// the user hold a click on the mouse, move to form an area
// where the objects are.
// it must select the objects that are inside of the area.
//
// flow:

// - user hit 's' to select
// - user hold the click and moved to form an area
// - user releases the click

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <collections/array.h>
#include <geometry/frame.h>

#include "../application_state.h"
#include "../selection.h"

struct select_command_t {
  int px, py, ex, ey;
};

struct select_command_t*
select_command_new(int px, int py, int ex, int ey) {
  struct select_command_t* s = malloc(sizeof(struct select_command_t));
  s->px = px;
  s->py = py;
  s->ex = ex;
  s->ey = ey;
  return s;
}

struct array_t *filter_in_frame_indexed(array_reducer_acc_t acc, array_item_t b,
					int i, array_user_data_t u) {
  struct frame_t* selection = (struct frame_t*)u;
  struct frame_t* frame = (struct frame_t*)b;

  if (frame_is_frame_inside(selection, frame)) {
    array_push(acc, (void*)(intptr_t)i);
  }

  return acc;
}

void print_selected(void* i) {
  int x = (int)(intptr_t)i;
  printf("selected %d\n", x);
}

int apply_select_command(struct select_command_t *c,
			 struct application_t *a) {
  struct frame_t* selection =
    frame_with_pos_size(c->px, c->py, c->ex, c->ey);

  struct array_t* selected =
    array_reduce_indexed(a->frames,
			 (array_reducer_indexed_t)filter_in_frame_indexed,
			 array_new(NULL),
			 selection);

  a->selected = selected;

  free(selection);

  return 0;
}

int main(void) {
  struct application_t* state =
    malloc(sizeof(struct application_t*));

  state->frames = array_new(free);
  state->selected = NULL;

  array_push(state->frames, frame_with_pos_size(5, 5, 7, 7));
  array_push(state->frames, frame_with_pos_size(1, 1, 2, 2));
  array_push(state->frames, frame_with_pos_size(3, 3, 4, 4));

  struct select_command_t* s =
    select_command_new(0, 0, 5, 5);

  apply_select_command(s, state);

  assert(state->selected->count == 2);

  free(s);

  array_free(state->frames);
  array_free(state->selected);

  free(state);

  return 0;
}

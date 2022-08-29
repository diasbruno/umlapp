#include <assert.h>
#include <stdlib.h>
#include "../frame.h"

void test_frame_new(void) {
  struct frame_t* f = frame_new();

  assert(f->pos.x == 0);
  assert(f->pos.y == 0);
  assert(f->size.width == 0);
  assert(f->size.height == 0);

  free(f);
}

void test_frame_with_pos_size(void) {
  struct frame_t* f = frame_with_pos_size(1, 2, 3, 4);

  assert(f->pos.x == 1);
  assert(f->pos.y == 2);
  assert(f->size.width == 3);
  assert(f->size.height == 4);

  free(f);
}

void test_frame_is_pos_inside_is(void) {
  struct frame_t* f = frame_with_pos_size(0, 0, 10, 10);
  struct pos_t p = { .x = 5, .y = 5 };

  assert(frame_is_pos_inside(f, &p) == 1);

  free(f);
}

void test_frame_is_pos_inside_isnt(void) {
  struct frame_t* f = frame_with_pos_size(0, 0, 10, 10);
  struct pos_t p = { .x = 15, .y = 15 };

  assert(frame_is_pos_inside(f, &p) == 0);

  free(f);
}

void test_frame_is_frame_inside_is(void) {
  struct frame_t *a = frame_with_pos_size(0, 0, 10, 10);
  struct frame_t *b = frame_with_pos_size(5, 5, 6, 6);

  assert(frame_is_frame_inside(a, b) == 1);

  free(a), free(b);
}

void test_frame_is_frame_inside_isnt(void) {
  struct frame_t *a = frame_with_pos_size(0, 0, 10, 10);
  struct frame_t *b = frame_with_pos_size(5, 5, 11, 11);

  assert(frame_is_frame_inside(a, b) == 0);

  free(a), free(b);
}

int main(void) {
  test_frame_new();
  test_frame_with_pos_size();
  test_frame_is_pos_inside_is();
  test_frame_is_pos_inside_isnt();
  test_frame_is_frame_inside_is();
  test_frame_is_frame_inside_isnt();
  return 0;
}

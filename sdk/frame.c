#include <stdlib.h>
#include <sdk/array.h>
#include <sdk/frame.h>

struct frame_t* frame_new() {
  return malloc(sizeof(struct frame_t*));
}

struct frame_t* frame_with_pos_size(float x, float y, float w, float h) {
  struct frame_t* f = frame_new();
  f->pos.x = x;
  f->pos.y = y;
  f->size.width = w;
  f->size.height = h;
  return f;
}

int frame_is_pos_inside(struct frame_t* f, struct pos_t *pos) {
  return !((pos->x >= f->pos.x && pos->x <= f->pos.x + f->size.width) &&
	   (pos->y >= f->pos.y && pos->y <= f->pos.y + f->size.height));
}

void* find_frames_by_pos(void *acc, void *i, void *s) {
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


void print_frame(struct frame_t* f) {
  g_print("frame(%f, %f, %f, %f)\n",
	  f->pos.x, f->pos.y,
	  f->size.width, f->size.height);
}

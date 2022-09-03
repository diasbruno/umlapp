#include <stdlib.h>
#include <stdio.h>

#include "frame.h"

frame_t* frame_new() {
  return malloc(sizeof(frame_t));
}

frame_t* frame_with_pos_size(const float x, const float y,
			     const float w, const float h) {
  frame_t* f = frame_new();
  f->pos.x = x;
  f->pos.y = y;
  f->size.width = w;
  f->size.height = h;
  return f;
}

void frame_free(frame_t* f) {
  free(f);
}

int frame_is_pos_inside(const frame_t* f, const pos_t *pos) {
  const pos_t* p = &f->pos;
  const rect_t* s = &f->size;
  return (pos->x >= p->x && pos->x <= p->x + s->width) &&
    (pos->y >= p->y && pos->y <= p->y + s->height);
}

int frame_is_frame_inside(const frame_t *a, const frame_t *b) {
  return (b->pos.x >= a->pos.x &&
	  b->pos.y >= a->pos.y &&
	  a->size.width >= b->size.width &&
	  a->size.height >= b->size.height);
}

void frame_print(const frame_t* f) {
  printf("frame(%f, %f, %f, %f)\n",
	 f->pos.x, f->pos.y,
	 f->size.width, f->size.height);
}

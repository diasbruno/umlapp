#include <stdlib.h>
#include <stdio.h>
#include "frame.h"

struct frame_t* frame_new() {
  return malloc(sizeof(struct frame_t));
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
  struct pos_t* p = &f->pos;
  struct size_t* s = &f->size;
  return (pos->x >= p->x && pos->x <= p->x + s->width) &&
    (pos->y >= p->y && pos->y <= p->y + s->height);
}

int frame_is_frame_inside(struct frame_t *a, struct frame_t *b) {
  return (b->pos.x >= a->pos.x &&
	  b->pos.y >= a->pos.y &&
	  a->size.width >= b->size.width &&
	  a->size.height >= b->size.height);
}

void print_frame(struct frame_t* f) {
  printf("frame(%f, %f, %f, %f)\n",
	 f->pos.x, f->pos.y,
	 f->size.width, f->size.height);
}

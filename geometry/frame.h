#ifndef _01G3PS8CBPD94GQR6CNTQG2S7E_
#define _01G3PS8CBPD94GQR6CNTQG2S7E_ 1

struct pos_t {
  float x, y;
};

struct size_t {
  float width, height;
};

struct frame_t {
  struct pos_t pos;
  struct size_t size;
};

struct frame_t *frame_new();

struct frame_t *frame_with_pos_size(float x, float y, float w, float h);

int frame_is_pos_inside(struct frame_t *f, struct pos_t *pos);

int frame_is_frame_inside(struct frame_t *a, struct frame_t *b);

void print_frame(struct frame_t* f);

#endif



















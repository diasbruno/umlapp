#ifndef _01G3PS8CBPD94GQR6CNTQG2S7E_
#define _01G3PS8CBPD94GQR6CNTQG2S7E_ 1

typedef struct pos_t {
  float x, y;
} pos_t;

typedef struct rect_t {
  float width, height;
} rect_t;

typedef struct frame_t {
  pos_t pos;
  rect_t size;
} frame_t;

frame_t *frame_new();

void frame_free(frame_t* f);

frame_t *frame_with_pos_size(const float x, const float y,
			     const float w, const float h);

int frame_is_pos_inside(const frame_t *f, const pos_t *pos);

int frame_is_frame_inside(const frame_t *a, const frame_t *b);

void frame_print(const frame_t* f);

#endif

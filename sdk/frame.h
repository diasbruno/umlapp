#ifndef _01G3PS8CBPD94GQR6CNTQG2S7E_
#define _01G3PS8CBPD94GQR6CNTQG2S7E_ 1

#include <sdk/types.h>

struct frame_t *frame_new();

struct frame_t *frame_with_pos_size(float x, float y, float w, float h);

int frame_is_pos_inside(struct frame_t* f, struct pos_t *pos);

void* find_frames_by_pos(void *acc, void *i, void *s);

void print_frame(struct frame_t* f);

#endif

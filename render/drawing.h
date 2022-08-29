#ifndef _01GBMZS9PPN1X8Z9QN0W1X6HV4_
#define _01GBMZS9PPN1X8Z9QN0W1X6HV4_ 1

#include <cairo.h>
#include <base/type.h>

void draw_arrow(cairo_t *cr, struct line_t *ls);

void draw_decision(cairo_t *cr, struct frame_t *frame);

void draw_box(cairo_t *cr, struct frame_t *frame);

void draw_rounded_box(cairo_t *cr, struct frame_t *frame);

#endif

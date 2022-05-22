#ifndef __UMLAPP_DRAWING_H__
#define __UMLAPP_DRAWING_H__ 1

#include <cairo.h>
#include <gtk/gtk.h>
#include <sdk/types.h>

void draw_arrow(cairo_t *cr, struct line_t *ls);

void draw_decision(cairo_t *cr, struct frame_t *frame);

void draw_box(cairo_t *cr, struct frame_t *frame);

void draw_rounded_box(cairo_t *cr, struct frame_t *frame);

#endif // __UMLAPP_DRAWING_H__

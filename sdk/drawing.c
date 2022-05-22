#include "cairo.h"
#include <math.h>
#include <sdk/drawing.h>

void draw_decision(cairo_t *cr, struct frame_t* frame) {
  const float x = frame->pos.x;
  const float y = frame->pos.y;
  const float w = frame->size.width;
  const float h = frame->size.height;
  const float w2 = w * 0.5;
  const float h2 = h * 0.5;
  cairo_save(cr);
  cairo_set_source_rgb(cr, 1, 0, 0);
  cairo_translate(cr, x, y);
  cairo_line_to(cr, w, h2);
  cairo_line_to(cr, w2, h);
  cairo_line_to(cr, 0, h2);
  cairo_line_to(cr, w2, 0);
  cairo_line_to(cr, w, h2);
  cairo_stroke(cr);
  cairo_restore(cr);
}

void draw_arrow(cairo_t *cr, struct line_t *ls) {
  struct pos_t p = ls->ps[0];
  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 1, 0);
  cairo_line_to(cr, p.x, p.y);
  for (int x = 0; x < ls->size; x++) {
    struct pos_t l = ls->ps[x];
    g_print("arrow %f %f\n", l.x, l.y);
    cairo_line_to(cr, l.x, l.y);
  }

  cairo_stroke(cr);
  cairo_restore(cr);
}

void draw_box(cairo_t *cr, struct frame_t *frame) {
  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_rectangle(cr,
		  frame->pos.x, frame->pos.y,
		  frame->size.width, frame->size.height);
  cairo_stroke(cr);
  cairo_restore(cr);
}

void draw_rounded_box(cairo_t *cr, struct frame_t *frame) {
  double
    x             = frame->pos.x,        /* parameters like cairo_rectangle */
    y             = frame->pos.y,
    width         = frame->size.width,
    height        = frame->size.height,
    aspect        = 1.0,
    corner_radius = height / 10.0;

  double radius = corner_radius / aspect;
  double degrees = G_PI / 180.0;

  cairo_save(cr);
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_new_sub_path (cr);
  cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
  cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
  cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
  cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
  cairo_close_path (cr);

  cairo_stroke(cr);
  cairo_restore(cr);
}

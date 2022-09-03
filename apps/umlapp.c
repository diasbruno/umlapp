#include <stdlib.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <base/type.h>
#include <collections/array.h>
#include <geometry/frame.h>
#include <mouse/type.h>
#include <render/drawing.h>

#include "./application_state.h"
#include "./creation.h"
#include "./selection.h"

const gchar* const kAppNamespace = (const gchar*)"io.github.diasbruno.umlapp";
const gchar* const kAppActivate = (const gchar*)"activate";
const gchar* const kKeyPress = (const gchar*)"key-pressed";
const gchar* const kMotion = (const gchar*)"motion";
const gchar* const kMousePress = (const gchar*)"pressed";
const gchar* const kMousePressReleased = (const gchar*)"released";

static application_t state = {
  .command = NULL,
  .commands = NULL,
  .selected = NULL,
  .objects = NULL,
  .frames = NULL,
  .canvas = NULL
};

static void draw_function(GtkDrawingArea *area,
			  cairo_t *cr,
			  int width,
			  int height,
			  gpointer state) {
  application_t* s = state;

  for (int x = 0; x < s->frames->count; x++) {
    frame_t* f = array_at(s->frames, x);
    draw_rounded_box(cr, f);
  }

  if (EXISTS(s->command)) {
    s->command->on_draw(s, cr);
  }
}

static gboolean key_pressed(GtkEventControllerKey* self,
			    guint keyval,
			    guint keycode,
			    GdkModifierType mod,
			    gpointer state) {
  application_t* s = state;

  if (EXISTS(s->command)) {
    s->command->on_finish(s);
  }

  command_option_t* o =
    array_find(s->commands,
	       command_option_by_shortname,
	       (any)((intptr_t)keyval));

  if (EXISTS(o)) {
    o->on_init(s);
    s->command = o;
    return TRUE;
  }

  return FALSE;
}

static void motion(GtkEventControllerMotion* self,
		   gdouble x,
		   gdouble y,
		   gpointer state
		   ) {
  application_t* s = state;

  mouse_click_t motion = {
    .n_press = 0,
    .x = x,
    .y = y,
    .state = NULL
  };

  if (EXISTS(s->command)) {
    s->command->on_mouse_motion(s, &motion);
  }
}

static void mouse_pressed(GtkGestureClick *self,
			  gint n_press,
			  gdouble x,
			  gdouble y,
			  gpointer state) {
  application_t* s = state;

  mouse_click_t press = {
    .n_press = n_press,
    .x = x,
    .y = y,
    .state = state
  };

  if (EXISTS(s->command)) {
    s->command->on_mouse_pressed(s, &press);
  }
}

static void mouse_released(GtkGestureClick *self,
			   gint n_press,
			   gdouble x,
			   gdouble y,
			   gpointer state) {
  application_t* s = state;

  mouse_click_t released = {
    .n_press = n_press,
      .x = x,
      .y = y,
      .state = state
  };

  if (EXISTS(s->command)) {
    s->command->on_mouse_released(s, &released);
  }
}

static void activate (GtkApplication *app, gpointer state) {
  application_t* s = state;

  // create the main window
  GtkWidget *window = gtk_application_window_new (app);

  // basic window settings
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);

  // main drawing surface
  GtkWidget *area = gtk_drawing_area_new();
  gtk_drawing_area_set_content_width (GTK_DRAWING_AREA (area), 500);
  gtk_drawing_area_set_content_height (GTK_DRAWING_AREA (area), 400);
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (area), draw_function, (gpointer)state, NULL);

  // attach surface to window
  gtk_window_set_child (GTK_WINDOW (window), area);

  s->canvas = area;

  // setup events and gestures, and, attach to the window
  GtkEventController *ec = gtk_event_controller_key_new();
  GtkEventController *mc = gtk_event_controller_motion_new();
  GtkGesture *click = gtk_gesture_click_new();

  gtk_widget_add_controller(window, ec);
  gtk_widget_add_controller(window, mc);
  gtk_widget_add_controller(window, (GtkEventController*)click);

  gpointer state_pointer = (gpointer)state;
  g_signal_connect(ec, kKeyPress, G_CALLBACK(key_pressed), state_pointer);
  g_signal_connect(mc, kMotion, G_CALLBACK(motion), state_pointer);
  g_signal_connect(click, kMousePress, G_CALLBACK(mouse_pressed), state_pointer);
  g_signal_connect(click, kMousePressReleased, G_CALLBACK(mouse_released), state_pointer);

  gtk_window_present (GTK_WINDOW (window));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status = 0;

  state.frames = array_new((array_dealloctor_t)frame_free);
  state.commands = array_new(null_free);

  register_creation_command_option(state.commands);
  register_selection_command_option(state.commands);

  app = gtk_application_new(kAppNamespace, G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, kAppActivate, G_CALLBACK(activate), (gpointer)&state);

  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  array_free(state.frames);

  return status;
}

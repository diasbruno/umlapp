#ifndef _01G3PNB439F3BZPGR0R0VDF0YF_
#define _01G3PNB439F3BZPGR0R0VDF0YF_ 1

#include <collections/array.h>

typedef struct application_t* application_t;

typedef void (*command_option_draw_fn_t)(application_t s, void *cr);
typedef void (*command_option_init_fn_t)(application_t s);
typedef void (*command_option_finish_fn_t)(application_t s);
typedef void (*command_option_key_fn_t)(application_t s, void *data);
typedef void (*command_option_motion_fn_t)(application_t s, void *data);
typedef void (*command_option_mouse_fn_t)(application_t s, void *data);

struct command_option_t {
  command_option_draw_fn_t on_draw;
  command_option_init_fn_t on_init;
  command_option_finish_fn_t on_finish;
  command_option_key_fn_t on_key;
  command_option_motion_fn_t on_mouse_motion;
  command_option_mouse_fn_t on_mouse_pressed;
  command_option_mouse_fn_t on_mouse_released;
  char* name;
  char shortname;
  char pad;
};

struct command_option_t* command_option_by_shortname(void* command, void* s);

void register_command_option(struct array_t* commands, struct command_option_t);

#endif

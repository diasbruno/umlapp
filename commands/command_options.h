#ifndef _01G3PNB439F3BZPGR0R0VDF0YF_
#define _01G3PNB439F3BZPGR0R0VDF0YF_ 1

#include <stdbool.h>
#include <base/type.h>
#include <collections/array.h>

#define NO_COMMAND (NULL)

typedef void (*command_option_draw_fn_t)(any s, any cr);
typedef void (*command_option_init_fn_t)(any s);
typedef void (*command_option_finish_fn_t)(any s);
typedef void (*command_option_key_fn_t)(any s, any data);
typedef void (*command_option_motion_fn_t)(any s, any data);
typedef void (*command_option_mouse_fn_t)(any s, any data);

typedef struct command_option_t {
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
} command_option_t;

bool command_option_by_shortname(array_item_t command, array_user_data_t s);

void register_command_option(array_t* commands, command_option_t);

#endif

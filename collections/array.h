#ifndef _01G3PNDWS3VV2704GQPFN91XJG_
#define _01G3PNDWS3VV2704GQPFN91XJG_ 1

#include <stdbool.h>
#include <base/type.h>

#define ARRAY_NO_USER_DATA (NULL)

typedef void* array_reducer_acc_t;
typedef void* array_item_t;
typedef void* array_user_data_t;

typedef void (*array_dealloctor_t)(array_item_t);


typedef void (*array_foreach_t)(array_item_t,
				array_user_data_t);

typedef bool (*array_finder_t)(array_item_t,
			      array_user_data_t);

typedef array_item_t (*array_reducer_t)(array_reducer_acc_t,
					array_item_t,
					array_user_data_t);

typedef array_item_t (*array_reducer_indexed_t)(array_reducer_acc_t,
						array_item_t,
						int,
						array_user_data_t);

typedef struct array_t {
  any* os;
  int count;
  int size;
  array_dealloctor_t dealloc;
} array_t;

inline int array_capacity(const array_t *a) { return a->size; }

inline int array_length(const array_t* a) { return a->count; }

array_t* array_new(array_dealloctor_t dealloc);

array_t* array_with_capacity(int cap, array_dealloctor_t dealloc);

void array_free(array_t*);

array_reducer_acc_t
array_reduce(const array_t*, array_reducer_t,
	     array_reducer_acc_t, array_user_data_t);

array_reducer_acc_t
array_reduce_indexed(const array_t*,
		     array_reducer_indexed_t,
		     array_reducer_acc_t,
		     array_user_data_t);

void array_foreach(const array_t*, array_foreach_t, array_user_data_t);

array_item_t array_find(const array_t*, array_finder_t, array_user_data_t);

void array_push(array_t*, array_item_t);

array_item_t array_at(const array_t*, int);

void null_free(array_item_t);

#endif

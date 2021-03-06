#ifndef _01G3PNDWS3VV2704GQPFN91XJG_
#define _01G3PNDWS3VV2704GQPFN91XJG_ 1

typedef void* array_reducer_acc_t;
typedef void* array_item_t;
typedef void* array_user_data_t;

typedef void (*array_dealloctor_t)(array_item_t);
typedef void (*array_mapper_t)(array_item_t);
typedef array_item_t (*array_finder_t)(array_item_t, array_user_data_t);
typedef array_item_t (*array_reducer_t)(array_reducer_acc_t, array_item_t,
					array_user_data_t);

struct array_t {
  void** os;
  int count;
  int size;
  array_dealloctor_t dealloc;
};

struct array_t* array_new(array_dealloctor_t dealloc);

struct array_t* array_with_capacity(int cap, array_dealloctor_t dealloc);

void array_free(struct array_t*);

array_reducer_acc_t
array_reduce(struct array_t*, array_reducer_t,
	     array_reducer_acc_t, array_user_data_t);

void array_foreach(struct array_t*, array_mapper_t);

array_item_t array_find(struct array_t*, array_finder_t, array_user_data_t);

void array_push(struct array_t*, array_item_t);

array_item_t array_at(struct array_t*, int);

void null_free(array_item_t);

#endif

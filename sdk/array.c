#include <stdlib.h>
#include <sdk/array.h>
#include <sdk/types.h>

struct array_t* array_new(array_dealloctor_t dealloc) {
  struct array_t* a = malloc(sizeof(struct array_t));
  a->os = NULL;
  a->count = 0;
  a->size = 0;
  a->dealloc = dealloc;
  return a;
}

struct array_t* array_with_capacity(int cap, array_dealloctor_t dealloc) {
  struct array_t* a = malloc(sizeof(struct array_t));
  a->os = malloc(sizeof(void*) * cap);
  a->count = 0;
  a->size = cap;
  a->dealloc = dealloc;
  return a;
}

void array_free(struct array_t *a) {
  free(a->os);
  free(a);
}

static void array_resize(struct array_t* arr) {
  int new_size = arr->size == 0 ? 2 : arr->size * 2;
  arr->os = realloc(arr->os, sizeof(void*) * new_size);
  arr->size = new_size;
}

void array_foreach(struct array_t *a, array_mapper_t mapper) {
  for (int x = 0, s = a->count; x < s; x++) {
    mapper(a->os[x]);
  }
}

array_item_t
array_find(struct array_t *a,
	   array_finder_t finder,
	   array_user_data_t data) {
  for (int x = 0, s = a->count; x < s; x++) {
    void* e = finder(a->os[x], data);
    if (EXISTS(e)) {
      return e;
    }
  }
  return NULL;
}

array_reducer_acc_t
array_reduce(struct array_t* a,
	     array_reducer_t reducer,
	     array_reducer_acc_t i,
	     array_user_data_t data) {
  array_reducer_acc_t r = i;
  for (int x = 0, s = a->count; x < s; x++) {
    r = reducer(r, a->os[x], data);
  }
  return r;
}

void array_push(struct array_t* a, array_item_t e) {
  if (a->size == a->count) {
    array_resize(a);
  }
  a->os[a->count] = (void*)e;
  ++a->count;
}

void* array_at(struct array_t* a, int p) {
  return a->os[p];
}

void null_free(void* x) {}

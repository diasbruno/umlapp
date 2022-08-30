#include <stdlib.h>
#include <stdio.h>
#include "./array.h"

void null_free(void* x) {}

struct array_t* array_newd(array_dealloctor_t dealloc) {
  struct array_t* a = malloc(sizeof(struct array_t));
  a->os = NULL;
  a->count = 0;
  a->size = 0;
  a->dealloc = dealloc;
  return a;
}

struct array_t* array_new() {
  return array_newd(null_free);
}

struct array_t* array_with_capacity(int cap,
				    array_dealloctor_t dealloc) {
  struct array_t* a = array_newd(dealloc);
  a->size = cap;
  return a;
}

void array_free(struct array_t *a) {
  array_dealloctor_t dealloc = a->dealloc;
  for (int x = 0, s = a->count; x < s; x++) {
    array_item_t i = a->os[x];
    if (i != NULL) {
      dealloc(i);
    }
  }
  free(a->os);
  free(a);
}

static void array_resize(struct array_t* arr) {
  int new_size = arr->size == 0 ? 2 : arr->size * 2;
  arr->os = realloc(arr->os, sizeof(void*) * new_size);
  arr->size = new_size;
}

void array_foreach(struct array_t *a,
		   array_foreach_t fun,
		   array_user_data_t u) {
  for (int x = 0, s = a->count; x < s; x++) {
    fun(a->os[x], u);
  }
}

array_item_t
array_find(struct array_t *a,
	   array_finder_t fun,
	   array_user_data_t data) {
  for (int x = 0, s = a->count; x < s; x++) {
    array_item_t i = a->os[x];
    if (fun(i, data) != 0) {
      return i;
    }
  }
  return NULL;
}

array_reducer_acc_t
array_reduce(struct array_t* a,
	     array_reducer_t fun,
	     array_reducer_acc_t i,
	     array_user_data_t data) {
  array_reducer_acc_t r = i;
  for (int x = 0, s = a->count; x < s; x++) {
    r = fun(r, a->os[x], data);
  }
  return r;
}

array_reducer_acc_t
array_reduce_indexed(struct array_t* a,
		     array_reducer_indexed_t fun,
		     array_reducer_acc_t i,
		     array_user_data_t data) {
  array_reducer_acc_t r = i;
  for (int x = 0, s = a->count; x < s; x++) {
    r = fun(r, a->os[x], x, data);
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

array_item_t array_at(struct array_t* a, int p) {
  return a->os[p];
}

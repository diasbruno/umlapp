#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "../array.h"

void noop(void* x) {}

void test_array_new(void) {
  struct array_t* a = array_new(NULL);

  assert(a != NULL);

  array_free(a);
}

void test_array_with_capacity(void) {
  struct array_t* a = array_with_capacity(10, noop);

  assert(array_capacity(a) == 10);
  assert(array_length(a) == 0);

  array_free(a);
}

struct meh {};

void meh_free(struct meh *m) {
  free(m);
}

// check using valgrind
void test_array_new_custom_dealloc(void) {
  struct meh *m = malloc(sizeof(struct meh));
  struct array_t* a = array_new((array_dealloctor_t)meh_free);

  array_push(a, m);

  assert(m == a->os[0]);

  array_free(a);
}

void test_array_push(void) {
  struct array_t* a = array_new(noop);
  array_push(a, (array_item_t)(intptr_t)1);

  assert(1 == (int)(intptr_t)a->os[0]);

  array_free(a);
}

array_item_t sum(array_reducer_acc_t acc,
		 array_item_t b,
		 array_user_data_t u) {
  int x = (int)(intptr_t)acc;
  int y = (int)(intptr_t)b;

  return (array_reducer_acc_t)(intptr_t)(x + y);
}

void test_array_reduce(void) {
  struct array_t* a = array_new(noop);

  array_push(a, (array_item_t)1);
  array_push(a, (array_item_t)2);

  int res = (int)(intptr_t)array_reduce(a, sum, (array_reducer_acc_t)1, NULL);

  assert(res == 4);

  array_free(a);
}

array_item_t sum_indexed(array_reducer_acc_t acc,
			 array_item_t b,
			 int i,
			 array_user_data_t u) {
  int x = (int)(intptr_t)acc;
  int y = (int)(intptr_t)b;

  return (array_reducer_acc_t)(intptr_t)(x + y + i);
}

void test_array_reduce_indexed(void) {
  struct array_t* a = array_new(noop);

  array_push(a, (array_item_t)1);
  array_push(a, (array_item_t)2);

  int res = (int)(intptr_t)array_reduce_indexed(a,
						sum_indexed,
						(array_reducer_acc_t)1,
						NULL);

  assert(res == 5);

  array_free(a);
}

void foreach_mapper(array_item_t b, array_user_data_t u) {
  int *x = u;
  *x += (int)(intptr_t)b;
}

void test_array_foreach(void) {
  struct array_t* a = array_new(noop);

  array_push(a, (array_item_t)1);
  array_push(a, (array_item_t)2);

  int res = 0;

  array_foreach(a, (array_mapper_t)foreach_mapper, &res);

  assert(res == 3);

  array_free(a);
}

int finder(array_item_t b, array_user_data_t u) {
  int x = (int)(intptr_t)b;
  int y = (int)(intptr_t)u;
  return x == y;
}

void test_array_find(void) {
  struct array_t* a = array_new(noop);

  array_push(a, (array_item_t)1);
  array_push(a, (array_item_t)2);

  int res = (int)(intptr_t)array_find(a,
				      (array_finder_t)finder,
				      (void*)(intptr_t)2);

  assert(res == 2);

  array_free(a);
}

void test_array_at(void) {
  struct array_t* a = array_new(noop);

  array_push(a, (array_item_t)1);
  array_push(a, (array_item_t)2);

  int res = (int)(intptr_t)array_at(a, 1);

  assert(res == 2);

  array_free(a);
}

int main(void) {
  test_array_new();
  test_array_with_capacity();
  test_array_new_custom_dealloc();
  test_array_push();
  test_array_reduce();
  test_array_reduce_indexed();
  test_array_foreach();
  test_array_find();
  test_array_at();
  return 0;
}

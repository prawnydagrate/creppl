#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef enum {
  STACK_SUCCESS,
  STACK_ERR_MALLOC_FAILURE,
} stack_result_t;

typedef struct {
  void *data;
  size_t esize;
  size_t len;
  size_t capacity;
} stack_s;

stack_result_t stack_init(stack_s *stack, size_t esize, size_t init_capacity);

stack_result_t stack_push(stack_s *stack, void *e);

void *stack_pop(stack_s *stack);

void stack_cleanup(stack_s *stack);

#endif

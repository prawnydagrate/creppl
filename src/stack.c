#include "stack.h"
#include <string.h>

stack_result_t stack_init(stack_s *stack, size_t esize, size_t init_capacity) {
  stack->data = malloc(esize * init_capacity);
  if (stack->data == NULL)
    return STACK_ERR_MALLOC_FAILURE;
  stack->len = 0;
  stack->esize = esize;
  stack->capacity = init_capacity;
  return STACK_SUCCESS;
}

stack_result_t _stack_resize(stack_s *stack, size_t count) {
  if (stack->len + count <= stack->capacity)
    return STACK_SUCCESS;
  size_t capacity = (stack->capacity + 4) * stack->esize;
  void *new = realloc(stack->data, capacity);
  if (new == NULL)
    return STACK_ERR_MALLOC_FAILURE;
  stack->data = new;
  stack->capacity = capacity;
  return STACK_SUCCESS;
}

stack_result_t stack_push(stack_s *stack, void *e) {
  int resize = _stack_resize(stack, 1);
  if (resize != STACK_SUCCESS)
    return resize;
  memcpy(stack->data + stack->len * stack->esize, e, stack->esize);
  stack->len++;
  return STACK_SUCCESS;
}

void *stack_pop(stack_s *stack) {
  if (stack->len == 0)
    return NULL;
  void *e = malloc(stack->esize);
  if (e == NULL) return NULL;
  memcpy(e, stack->data + (stack->len - 1) * stack->esize, stack->esize);
  stack->len--;
  return e;
}

void stack_cleanup(stack_s *stack) {
  free(stack->data);
  stack->data = NULL;
  stack->esize = 0;
  stack->len = 0;
  stack->capacity = 0;
}

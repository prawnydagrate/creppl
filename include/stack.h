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

/**
 * This function takes an empty stack (set to `{0}`),
 * the size of each element of the stack (all elements must
 * be of the same type), and the initial capacity, and
 * initializes the stack. **This function must be executed
 * before the stack is used**, and `stack_cleanup` **must be
 * called after use**.
 *
 * @param stack A pointer to the stack, set to `{0}`.
 * @param esize The size of each element of the stack.
 * @param init_capacity The initial capacity of the stack.
 * @return The result of the initialization. This function
 * may return an error if dynamic memory allocation fails.
 */
stack_result_t stack_init(stack_s *stack, size_t esize, size_t init_capacity);

/**
 * This function pushes an element onto a stack.
 *
 * @param stack A pointer to the stack.
 * @param e A pointer to the element being added. The size of
 * this element must be equivalent to `stack->esize`.
 * @return The result of pushing. This function may return an
 * error if dynamic memory reallocation fails while resizing the stack as needed.
 */
stack_result_t stack_push(stack_s *stack, void *e);

/**
 * This function pops the last element off a stack.
 *
 * @param stack A pointer to the stack.
 * @return A pointer to the popped element. **This pointer
 * must be `free`d after use**. This pointer may point to
 * `NULL`, if the list is empty or if dynamic memory allocation
 * for the element failed.
 */
void *stack_pop(stack_s *stack);

/**
 * This function frees the memory allocated for a stack, and
 * uninitializes it.
 *
 * @param stack A pointer to the stack.
 */
void stack_cleanup(stack_s *stack);

#endif

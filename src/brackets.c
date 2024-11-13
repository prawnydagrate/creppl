#include "brackets.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>

token to_token(char c) {
  bracket b = {0};
  bool is_bracket = true;
  switch (c) {
  case '(':
    b.direction = LEFT;
    b.type = PAREN;
    break;
  case '[':
    b.direction = LEFT;
    b.type = SQUARE;
    break;
  case '{':
    b.direction = LEFT;
    b.type = CURLY;
    break;
  case ')':
    b.direction = RIGHT;
    b.type = PAREN;
    break;
  case ']':
    b.direction = RIGHT;
    b.type = SQUARE;
    break;
  case '}':
    b.direction = RIGHT;
    b.type = CURLY;
    break;
  default:
    is_bracket = false;
  }
  return (token){is_bracket, b};
}

/*
 * \brief Checks if brackets are balanced.
 *
 * This function takes checks if a piece of code
 * has balanced brackets, i.e. (), [], and {}.
 * For example, this is balanced: [{()({[]})}]
 * However, this is not: [{()({[}])}]
 *
 * \param code The code to check.
 * \param len The number of characters in the code.
 * \return TODO idea (with bitshifting):
 * - u8 error      |    8
 * - u8 valid      | +  8
 * - u16 line      | + 16
 * - u16 col       | + 16
 * - char expected | +  8
 * - char got      | +  8
 *   --------------------
 * - u64 result    |   64
 */
uint64_t check(char *code, uint16_t len) {
  // TODO Vec to store relevant tokens
  stack_s brackets = {0};
  stack_init(&brackets, sizeof(btype), 8);
  uint16_t line = 1;
  uint16_t col = 0;
  for (uint16_t i = 0; i < len; i++) {
    char c = code[i];
    if (c == '\n') {
      line++;
      col = 0;
      continue;
    } else {
      col++;
    }
    token t = to_token(c);
    if (!t.is_bracket) {
      continue;
    }
    if (t.b.direction == LEFT) {
      if (stack_push(&brackets, &t.b.type) != STACK_SUCCESS) {
        return ERR_MALLOC_FAILURE;
      }
    } else if (t.b.direction == RIGHT) {
      // TODO account for right bracket with empty stack
      void *popped = stack_pop(&brackets);
      if (popped == NULL)
        return ERR_MALLOC_FAILURE;
      btype last = *(btype *)popped;
      if (last != t.b.type) {
        // TODO
        return (uint64_t)0 << 56/* | */;
      }
    }
  }
  stack_cleanup(&brackets);
  return false;
}

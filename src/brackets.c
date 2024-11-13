#include "brackets.h"
#include "stack.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

token char_to_token(char c) {
  bracket b = {0};
  bool is_bracket = true;
  switch (c) {
  case '(':
    b.direction = B_LEFT;
    b.type = B_PAREN;
    break;
  case '[':
    b.direction = B_LEFT;
    b.type = B_SQUARE;
    break;
  case '{':
    b.direction = B_LEFT;
    b.type = B_CURLY;
    break;
  case ')':
    b.direction = B_RIGHT;
    b.type = B_PAREN;
    break;
  case ']':
    b.direction = B_RIGHT;
    b.type = B_SQUARE;
    break;
  case '}':
    b.direction = B_RIGHT;
    b.type = B_CURLY;
    break;
  default:
    is_bracket = false;
  }
  return (token){is_bracket, b};
}

char bracket_to_char(btype t, bdir d) {
// both btype and bdir are 1 byte long,
// so they can be combined like this:
#define BRACKET(t, d) ((uint16_t)t << 8 | d)

  switch (BRACKET(t, d)) {
  case BRACKET(B_PAREN, B_LEFT):
    return '(';
  case BRACKET(B_PAREN, B_RIGHT):
    return ')';
  case BRACKET(B_SQUARE, B_LEFT):
    return '[';
  case BRACKET(B_SQUARE, B_RIGHT):
    return ']';
  case BRACKET(B_CURLY, B_LEFT):
    return '{';
  case BRACKET(B_CURLY, B_RIGHT):
    return '}';
  default:
    fprintf(stderr, "why did you cast some random ahh value to an enum??\n");
    exit(1);
  }
}

check_result_t check(char *code) {
#define S_CLEANUP stack_cleanup(&brackets);
#define ERR_MALLOC_FAILURE (check_result_t){0}
#define RES(status, line, col, expected, got, level)                          \
  (check_result_t) { status, line, col, expected, got, level }

  stack_s brackets = {0};
  stack_init(&brackets, sizeof(btype), 8);
  uint16_t line = 1;
  uint16_t col = 0;
  uint16_t b_line = 1;
  uint16_t b_col = 0;
  for (uint16_t i = 0; i < strlen(code); i++) {
    char c = code[i];
    if (c == '\n') {
      line++;
      col = 0;
      continue;
    } else {
      col++;
    }
    token t = char_to_token(c);
    if (!t.is_bracket) {
      continue;
    }
    b_line = line;
    b_col = col;
    if (t.b.direction == B_LEFT) {
      // push left brackets onto the stack
      if (stack_push(&brackets, &t.b.type) != STACK_SUCCESS) {
        S_CLEANUP
        return ERR_MALLOC_FAILURE;
      }
    } else if (t.b.direction == B_RIGHT) {
      if (brackets.len == 0) {
        // cannot have a right bracket without a left bracket
        S_CLEANUP
        return RES(CHECK_R_EXTRA, line, col, 0, c, 0);
      }
      void *popped = stack_pop(&brackets);
      if (popped == NULL) {
        S_CLEANUP
        return ERR_MALLOC_FAILURE;
      }
      btype last = *(btype *)popped;
      free(popped);
      if (last != t.b.type) {
        S_CLEANUP
        return RES(CHECK_R_MISMATCH, line, col, bracket_to_char(last, B_RIGHT),
                   bracket_to_char(t.b.type, t.b.direction), brackets.len);
      }
    }
  }
  if (brackets.len == 0) {
    S_CLEANUP
    return RES(CHECK_BALANCED, 0, 0, 0, 0, 0);
  }
  void *popped = stack_pop(&brackets);
  if (popped == NULL) {
    S_CLEANUP
    return ERR_MALLOC_FAILURE;
  }
  btype last = *(btype *)popped;
  free(popped);
  return RES(CHECK_L_UNCLOSED, b_line, b_col, bracket_to_char(last, B_RIGHT), 0,
             brackets.len);
}

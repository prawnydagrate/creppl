#ifndef BRACKETS_H
#define BRACKETS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum : uint8_t {
  B_LEFT,
  B_RIGHT,
} bdir;

typedef enum : uint8_t {
  B_PAREN,
  B_SQUARE,
  B_CURLY,
} btype;

typedef struct {
  bdir direction;
  btype type;
} bracket;

typedef struct {
  bool is_bracket;
  bracket b;
} token;

token char_to_token(char c);

char bracket_to_char(btype t, bdir d);

typedef enum : uint8_t {
  CHECK_ERR_MALLOC_FAILURE = 0,
  CHECK_BALANCED,
  CHECK_R_EXTRA,
  CHECK_R_MISMATCH,
  CHECK_L_UNCLOSED,
} check_status;

typedef struct {
  check_status status;
  uint16_t line;
  uint16_t col;
  char expected;
  char got;
  uint16_t level;
} check_result_t;

/*
 * Checks if brackets are balanced.
 *
 * This function takes checks if a piece of code
 * has balanced brackets, i.e. (), [], and {}.
 * For example, this is balanced: `[{()({[]})}]`
 * However, this is not: `[{()({[}])}]`
 *
 * @param code The code to check.
 * @return The result of checking.
 */
check_result_t check(char *code);

#endif

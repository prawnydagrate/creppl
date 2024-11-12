#include <stdbool.h>
#include <stdlib.h>
#include "brackets.h"

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
 * \return TODO
 */
char *check(char *code, size_t len) {
  // TODO Vec to store relevant tokens
  for (size_t i = 0; i < len; i++) {
    char c = code[i];
    token t = to_token(c);
    if (!t.is_bracket) {
      continue;
    }
  }
  // TODO
  return false;
}

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  LEFT,
  RIGHT,
} bdir;

typedef enum {
  PAREN,
  SQUARE,
  CURLY,
} btype;

typedef struct {
  bdir direction;
  btype type;
} bracket;

typedef struct {
  bool is_bracket;
  bracket b;
} token;

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

// TODO return error messages
bool check(char* code, size_t len) {
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

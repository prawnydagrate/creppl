#ifndef BRACKETS_H
#define BRACKETS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define ERR_MALLOC_FAILURE ((uint64_t)0xff << 56)

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

token to_token(char c);

uint64_t check(char *code, uint16_t len);

#endif

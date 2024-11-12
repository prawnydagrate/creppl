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


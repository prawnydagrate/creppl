#include "repl.h"
const unsigned long LINE_SIZE = 1 << 10;
const unsigned long BLOCK_SIZE = 1 << 15;

int main() {
  // TODO use actual temp files
  const char *main_fname = "__main.c";
  // includes and code in separate files, to combine later
  const char *includes_fname = "__includes.c";
  const char *code_fname = "__code.c";
  begin_repl(LINE_SIZE, BLOCK_SIZE, main_fname, includes_fname, code_fname);
}

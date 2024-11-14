#include "brackets.h"
#include "files.h"
#include <stdio.h>
#include <string.h>

long long handle_result(check_result_t res) {
  switch (res.status) {
  case CHECK_BALANCED:
    return 0;
  case CHECK_L_UNCLOSED:
    return res.level;
  case CHECK_R_EXTRA:
    fprintf(stderr, "Extra right bracket on line %lu, col %lu: %c\n", res.line,
            res.col, res.got);
    return -1;
  case CHECK_R_MISMATCH:
    fprintf(stderr, "Mismatched right bracket on line %lu, col %lu: %c\n",
            res.line, res.col, res.got);
    return -1;
  case CHECK_ERR_MALLOC_FAILURE:
    fprintf(stderr, "Dynamic memory allocation failed\n");
    return -1;
  }
}

void begin_repl(const unsigned long LINE_SIZE, const unsigned long BLOCK_SIZE,
                const char *main_fname, const char *includes_fname,
                const char *code_fname) {
  char block[BLOCK_SIZE];
  while (true) {
    // input
    char line[LINE_SIZE];
    printf("%s ", strlen(block) > 0 ? "..." : ">>>");
    if (fgets(line, sizeof(line), stdin) == NULL) {
      puts("[ABORT]");
      exit(0);
    }
    // separate includes from code
    if (strncmp(line, "#include", 8) == 0) {
      add_lines(includes_fname, line);
      continue;
    }
    // add line to block of code
    strcat(block, line);
    // handle depending on brackets
    long long status = handle_result(check(block));
    if (status == 0) {
      // code can be executed
      add_lines(code_fname, block);
      combine_code(includes_fname, code_fname, main_fname);
      // TODO compile and execute code
    }
    if (status <= 0) {
      memset(block, 0, sizeof(block));
    }
  }
}

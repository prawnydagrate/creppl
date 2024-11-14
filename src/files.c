#include "files.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const char *FILE_ERROR_MSG = "Error with temp file";

bool file_exists(const char *fname) { return !ACCESS(fname, F_OK); }

#define FILE_ERROR                                                             \
  perror(FILE_ERROR_MSG);                                                      \
  return -1;
#define FILE_CHECK(f)                                                          \
  if (f == NULL) {                                                             \
    FILE_ERROR                                                                 \
  }
#define FILE_OP(OP)                                                            \
  if (OP != 0) {                                                               \
    FILE_ERROR                                                                 \
  }

short add_lines(const char *fname, char *lines) {
  if (!strlen(lines))
    return 0;
  FILE *f = fopen(fname, "a");
  FILE_CHECK(f)
  fprintf(f, "%s\n", lines);
  FILE_OP(fclose(f))
  return 0;
}

short combine_code(const char *includes_fname, const char *code_fname,
                   const char *main_fname) {
  FILE *fm = fopen(main_fname, "w");
  char buffer[1024];
  if (file_exists(includes_fname)) {
    FILE *fi = fopen(includes_fname, "r");
    FILE_CHECK(fi)
    while (fgets(buffer, sizeof(buffer), fi)) {
      fprintf(fm, "%s", buffer);
    }
    FILE_OP(fclose(fi));
  }
  if (file_exists(code_fname)) {
    fputs("\nint main() {\n", fm);
    FILE *fc = fopen(code_fname, "r");
    FILE_CHECK(fc)
    while (fgets(buffer, sizeof(buffer), fc)) {
      fprintf(fm, "%s", buffer);
    }
    fputs("\n}", fm);
  }
  FILE_OP(fclose(fm));
  return 0;
}


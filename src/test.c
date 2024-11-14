#include "brackets.h"
#include <stdio.h>
#include <string.h>

void print_res(char *code) {
  check_result_t res = check(code);
  char status[24] = {0};
  switch (res.status) {
  case CHECK_ERR_MALLOC_FAILURE:
    strcpy(status, "malloc failure");
    break;
  case CHECK_BALANCED:
    strcpy(status, "balanced");
    break;
  case CHECK_R_EXTRA:
    strcpy(status, "extra right bracket");
    break;
  case CHECK_R_MISMATCH:
    strcpy(status, "right bracket mismatch");
    break;
  case CHECK_L_UNCLOSED:
    strcpy(status, "unclosed left bracket");
    break;
  }
  printf("code: %s\n"
         "status: %s\n"
         "line %lu, col %lu\n"
         "expected %c, got %c\n"
         "level: %lu\n"
         "\n",
         code, status, res.line, res.col, res.expected ? res.expected : '-',
         res.got ? res.got : '-', res.level);
}

int main() {
  // brackets test
  char *pass1 = "[{((([([])])))}]";
  char *pass2 = "(()[][(){}({[{()}]})])";
  char *rextra1 = "(()[][(){}({[{()}]})])]";
  char *rmismatch1 = "[{((([([])])))}}]";
  char *rmismatch2 = "(()[][(){}({[{()}]})}])";
  char *lunclosed1 = "[([(()[][(){}({[{()}]})]){{}}])()";
  char *lunclosed2 = "[";
  char *level_test = "[[{({[]})}[]([{()}]";
  print_res(pass1);
  print_res(pass2);
  print_res(rextra1);
  print_res(rmismatch1);
  print_res(rmismatch2);
  print_res(lunclosed1);
  print_res(lunclosed2);
  print_res(level_test);
}

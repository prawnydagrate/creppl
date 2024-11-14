#ifndef FILES_H

#define FILES_H

#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#define ACCESS _access
#define F_OK 0
#else
#include <unistd.h>
#define ACCESS access
#endif

bool file_exists(const char *fname);

short add_lines(const char *fname, char *lines);

short combine_code(const char *includes_fname, const char *code_fname,
                   const char *main_fname);

#endif

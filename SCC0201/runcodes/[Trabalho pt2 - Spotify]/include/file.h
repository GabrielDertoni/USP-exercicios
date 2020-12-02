#ifndef __FILE_H__
#define __FILE_H__

#include <stdbool.h>
#include <parsing.h>

typedef struct _file file_t;

file_t *file_read(const char *fname);
bool file_eof(file_t *file);
void file_close(file_t *file);

slice_t file_slice(const file_t *file);

#endif

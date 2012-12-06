#ifndef SOURCE_H
#define SOURCE_H

#include <apr_file_io.h>

typedef struct Source {
    apr_int64_t shift_direction;
    int shift_offset;
    char *filename;
    apr_file_t *file;
} Source;

apr_status_t source_open(Source *source, apr_pool_t *mp);
void source_init(Source **source, apr_pool_t *mp);
apr_status_t source_set_options(Source *source, int argc, const char **argv, apr_pool_t *mp);
apr_status_t source_shift_character(Source *source, char *ch);
void source_cleanup(Source *source);

#endif
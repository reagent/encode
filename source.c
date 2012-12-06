#include <apr_getopt.h>
#include <apr_strings.h>

#include "error.h"
#include "source.h"
#include "char.h"

apr_status_t
source_open(Source *source, apr_pool_t *mp)
{
    apr_status_t status;

    if (source->filename == NULL) {
        status = apr_file_open_stdin(&source->file, mp);
    } else {
        status = apr_file_open(&source->file, source->filename, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, mp);
    }

    return status;
}

void
source_init(Source **source, apr_pool_t *mp)
{
    Source *new_source = apr_palloc(mp, sizeof(Source));

    new_source->shift_direction = 1;
    new_source->shift_offset    = 1;
    new_source->filename        = NULL;
    new_source->file            = NULL;

    *source = new_source;
}

apr_status_t
source_set_options(Source *source, int argc, const char **argv, apr_pool_t *mp)
{
    apr_status_t status;
    apr_getopt_t *options;
    char option;
    const char *option_argument;

    status = apr_getopt_init(&options, mp, argc, argv);
    handle_and_display_error(status);

    while (apr_getopt(options, "dn:f:", &option, &option_argument) == APR_SUCCESS) {
        switch (option) {
            case 'd':
                source->shift_direction = -1;
                break;
            case 'n':
                source->shift_offset = abs(apr_atoi64(option_argument));
                break;
            case 'f':
                source->filename = apr_pstrndup(mp, option_argument, 64);
                break;
        }
    }

error:
    return status;
}

apr_status_t
source_shift_character(Source *source, char *ch)
{
    apr_status_t status;
    int offset = source->shift_offset * source->shift_direction;

    status = apr_file_getc(ch, source->file);

    if (status == APR_SUCCESS) {
        *ch = char_shift(*ch, offset);
    } else {
        *ch = '\0';
    }

    return status;
}

void
source_cleanup(Source *source)
{
    if (source->file != NULL) {
        apr_file_close(source->file);
    }
}
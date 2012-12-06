// C standard library includes
#include <stdio.h>
#include <stdlib.h>

// APR includes
#include <apr_pools.h>

// Local includes
#include "error.h"
#include "source.h"
#include "char.h"

int
main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    apr_status_t status;
    char next_char;
    Source *source = NULL;

    apr_initialize();

    status = apr_pool_create(&mp, NULL);
    handle_and_display_error(status);

    source_init(&source, mp);

    status = source_set_options(source, argc, argv, mp);
    handle_and_display_error(status);

    status = source_open(source, mp);
    handle_and_display_error(status);

    while (source_shift_character(source, &next_char) == APR_SUCCESS) {
        printf("%c", next_char);
    }

    source_cleanup(source);
    apr_pool_destroy(mp);
    apr_terminate();

    return 0;

error:
    if (source) { source_cleanup(source); }
    apr_pool_destroy(mp);
    apr_terminate();

    return 1;
}
// C standard library includes
#include <stdio.h>
#include <stdlib.h>

// APR includes
#include <apr_getopt.h>
#include <apr_file_io.h>
#include <apr_strings.h>

typedef char (*shift_cb)(char source);

char
next_character(char source)
{
    char next = '\0';

    if(source == 'Z') {
        next = 'a';
    } else if(source == 'z') {
        next = 'A';
    } else {
        next = (char) source + 1;
    }

    return next;
}

char
previous_character(char source)
{
    char previous = '\0';

    if(source == 'a') {
        previous = 'Z';
    } else if(source == 'A') {
        previous = 'z';
    } else {
        previous = (char) source - 1;
    }

    return previous;
}

int
character_between(char character, char lower_limit, char upper_limit)
{
    return character >= lower_limit && character <= upper_limit;
}

int
can_shift(char source)
{
    return character_between(source, 'A', 'Z') || character_between(source, 'a', 'z');
}

char
shift_character(char source, int offset)
{
    int position = 0;
    char shifted = source;
    shift_cb shift = (offset < 0) ? previous_character : next_character;

    if(can_shift(source)) {
        for(position = 0; position < abs(offset); position++) {
            shifted = shift(shifted);
        }
    }

    return shifted;
}

int
main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    char next_char;

    apr_initialize();

    apr_pool_create(&mp, NULL);

    apr_getopt_t *options;
    char option;
    const char *option_argument;

    apr_int64_t shift_direction   = 1;
    int shift_offset      = 1;

    char *filename = NULL;

    apr_getopt_init(&options, mp, argc, argv);
    while (apr_getopt(options, "dn:f:", &option, &option_argument) == APR_SUCCESS) {
        switch (option) {
            case 'd':
                shift_direction = -1;
                break;
            case 'n':
                shift_offset = apr_atoi64(option_argument);
                break;
            case 'f':
                filename = apr_pstrndup(mp, option_argument, 64);
                break;
        }
    }

    apr_file_t *source;

    if (filename == NULL) {
        apr_file_open_stdin(&source, mp);
    } else {
        apr_file_open(&source, filename, APR_FOPEN_READ, APR_FPROT_OS_DEFAULT, mp);
    }

    while (apr_file_getc(&next_char, source) == APR_SUCCESS) {
        printf("%c", shift_character(next_char, shift_offset * shift_direction));
    }

    apr_pool_destroy(mp);
    apr_terminate();

    return 0;
}
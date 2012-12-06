#include "char.h"

char
char_next(char source)
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
char_previous(char source)
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
char_between(char character, char lower_limit, char upper_limit)
{
    return character >= lower_limit && character <= upper_limit;
}

int
char_can_shift(char source)
{
    return char_between(source, 'A', 'Z') || char_between(source, 'a', 'z');
}

char
char_shift(char source, int offset)
{
    int position = 0;
    char shifted = source;
    shift_cb shift = (offset < 0) ? char_previous : char_next;

    if(char_can_shift(source)) {
        for(position = 0; position < abs(offset); position++) {
            shifted = shift(shifted);
        }
    }

    return shifted;
}

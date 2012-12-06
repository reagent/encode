#ifndef CHAR_H
#define CHAR_H

#include <stdlib.h>

typedef char (*shift_cb)(char source);

char char_shift(char source, int offset);

#endif
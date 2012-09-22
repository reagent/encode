#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char next_character(char source)
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

char previous_character(char source)
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

char shift_character(char source, int offset)
{
  int position = 0;
  char shifted = source;

  for(position = 0; position < abs(offset); position++) {
    // TODO: use callbacks to supply shifting functions?
    if(offset < 0) {
      shifted = previous_character(shifted);
    } else {
      shifted = next_character(shifted);
    }
  }

  return shifted;
}

int character_between(char character, char lower_limit, char upper_limit)
{
  return character >= lower_limit && character <= upper_limit;
}

int can_shift(char source)
{
  return character_between(source, 'A', 'Z') || character_between(source, 'a', 'z');
}

int main(int argc, char *argv[])
{
  int i = 0, offset = 1, should_increment = 1;
  char ch;

  while((ch = getopt(argc, argv, "dn:")) != -1) {
    switch(ch) {
      case 'd':
        should_increment = 0;
        break;
      case 'n':
        offset = abs(atoi(optarg));
        break;
      default:
        break;
    }
  }

  if(should_increment == 0) {
    offset = -offset;
  }

  char source[BUFFER_SIZE];
  char *destination = strdup(source);

  while(fgets(source, BUFFER_SIZE, stdin)) {
    for(i = 0; source[i] != '\0'; i++) {
      if(can_shift(source[i])) {
        destination[i] = shift_character(source[i], offset);
      } else {
        destination[i] = source[i];
      }
    }

    puts(destination);
  }

  return 0;
}
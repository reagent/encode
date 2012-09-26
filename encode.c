#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void die(char *message)
{
  printf("Got error: '%s', exiting.\n", message);
  exit(1);
}

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

int character_between(char character, char lower_limit, char upper_limit)
{
  return character >= lower_limit && character <= upper_limit;
}

int can_shift(char source)
{
  return character_between(source, 'A', 'Z') || character_between(source, 'a', 'z');
}

char shift_character(char source, int offset)
{
  int position = 0;
  char shifted = source;

  if(can_shift(source)) {
    for(position = 0; position < abs(offset); position++) {
      // TODO: use callbacks to supply shifting functions?
      if(offset < 0) {
        shifted = previous_character(shifted);
      } else {
        shifted = next_character(shifted);
      }
    }
  }

  return shifted;
}

int main(int argc, char *argv[])
{
  int offset = 1;
  int should_increment = 1;
  char ch = '\0';
  char stream_source = 's';
  FILE *input = stdin;

  while((ch = getopt(argc, argv, "dn:f:")) != -1) {
    switch(ch) {
      case 'd':
        should_increment = 0;
        break;
      case 'n':
        offset = abs(atoi(optarg));
        break;
      case 'f':
        input = fopen(optarg, "r");
        if(input == NULL) { die("Could not open input file"); }
        stream_source = 'f';
        break;
      default:
        break;
    }
  }

  if(should_increment == 0) {
    offset = -offset;
  }

  while((ch = fgetc(input)) != EOF) {
    printf("%c", shift_character(ch, offset));
  }

  if(stream_source == 'f') {
    fclose(input);
  }

  return 0;
}
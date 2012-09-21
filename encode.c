#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char shift_character(char source)
{
  char next;
  if(source == 'Z') {
    next = 'a';
  } else if(source == 'z') {
    next = 'A';
  } else {
    next = (char) source + 1;
  }
  
  return next;
}

int main(int argc, char *argv[])
{
  int i = 0;
  
  char source[BUFFER_SIZE];
  char *destination = strdup(source);

  while(fgets(source, BUFFER_SIZE, stdin)) {
    for(i = 0; source[i] != '\0'; i++) {
      destination[i] = shift_character(source[i]);
    }
  
    puts(destination);
  }
  
  return 0;
}
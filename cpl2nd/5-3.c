#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

void strcat2(char *s, char *t) {
  int i = strlen(s);
  char c;
  while ((c = *t) != '\0') {
    *(s + i++) = c;
    t++;
  }
  *(s + i) = '\0';
}
int main (int argc, char *argv[])
{
  if (argc > 2){
    printf("Too many args!\n");
    exit(1);
  }
  char s[MAX_LENGTH] = "This is my string: ";
  printf("%s\n", s);
  strcat2(s, argv[1]);
  printf("%s\n", s);
  return 0;
}

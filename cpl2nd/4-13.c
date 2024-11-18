#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

static void _reverse(char *s, int *idx, int *p) {
  char c = s[(*idx)++];
  if (c != '\0') {
    _reverse(s, idx, p);
    s[(*p)++] = c;
  }
}

void reverse(char *s) {
  int idx = 0;
  int p = 0;
  _reverse(s, &idx, &p);
}

int main (int argc, char *argv[])
{
  char str[MAX_LENGTH];
  printf("%s %s\n", argv[0], argv[1]);
  if (argc > 2){
    printf("Too many arguments! 1 allowed.\n");
    exit(1);
  }
  strncpy(str, argv[1], MAX_LENGTH - 1);
  str[MAX_LENGTH - 1] = '\0';
  printf("%s\n", str);
  reverse(str);
  printf("%s\n", str);
  return 0;
}

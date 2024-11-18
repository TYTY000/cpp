#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_LENGTH 100

void itoaRe(int i, char s[]);
void itoa(int i, char s[]){
  s[0] = '\0';
  itoaRe(i, s);
}

void itoaRe(int i, char s[]){
  int reminder, k;
  if (i / 10){
    itoa(i / 10, s);
  }
  k = strlen(s);
  if (i / 10 == 0 && i < 0){
    s[k++] = '\0';
  }
  reminder = i % 10;
  s[k++] = ((i > 0)? reminder: -reminder) + '0';
  s[k] = '\0';
}

int main (int argc, char *argv[])
{
  char str[MAX_LENGTH];
  int i = atoi(argv[1]);
  itoa(i, str);
  printf("%s\n", str);
  return 0;
}

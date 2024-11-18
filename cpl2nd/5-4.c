#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define MAX_LENGTH 100

int strend2(char *s, char *t) {
  int lens = strlen(s);
  int lent = strlen(t);
  if (!lent || lens < lent)  return 0;
  while (lent > 1) {
    if(*(s + lens--) != *(t + lent--))
      return 0;
  }
  return 1;
}
int main (int argc, char *argv[])
{
  if (argc > 2){
    printf("Too many args!\n");
    exit(1);
  }
  assert(strend2("abcde", "cde"));
  assert(!strend2("abcde", "cdef"));
  return 0;
}

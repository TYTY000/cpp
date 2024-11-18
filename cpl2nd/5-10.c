#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define MAXOP 100

int getop(char *s);

int main (int argc, char *argv[])
{
  if (!strcmp(argv[0],"expr")){
    printf("argv[0] != expr!\n");
    exit(1);
  }
  if (argc < 3){
    printf(" not enough args!\n");
    exit(1);
  }

  int *type;
  double op2;
  char s[MAXOP];
  int i = 1;
  while (*type = *argv[i++]) {
    switch (*type) {
      case '0': case '1': case '2': case '3': case '4': 
      case '5': case '6': case '7': case '8': case '9': 
        push(atoi(s));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0)
          push(pop() / op2);
        else
          printf("error: zero divisor\n");
        break;
      case '\n':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  return 0;
}

#include <stdio.h>
#include <ctype.h>

#define IN 0
#define OUT 1

int main(){
  char c;
  int test = IN;

  while ((c = getchar()) != EOF){
  if (test == IN){
      if (isspace(c)){
        test = IN;
        putchar('\n');
      } else {
        putchar(c);
      }
    }else if (test == OUT){
      if (!isspace(c)){
        test = OUT;
        putchar(c);
      }
    }
  }
}

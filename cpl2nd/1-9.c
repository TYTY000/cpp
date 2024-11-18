#include <stdio.h>
  
  int space = 0;
  int tab = 0;
  int new = 0 ;

int main(){
  char c;
  char d;

  while ((c = getchar()) != EOF){
    if (c != ' ' || d != ' ')
      putchar(d = c);
  }
}


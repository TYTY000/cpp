#include <stdio.h>
  
  int space = 0;
  int tab = 0;
  int new = 0 ;

int main(){
  int c;
  while ((c = getchar()) != EOF){
    switch (c) {
      case ' ':
        space ++;
        break;
      case '\t':
        tab ++;
        break;
      case '\n':
        new ++;
        break;
      default:
        break;
    }
  }
  printf("space: %d , tab: %d , newline : %d\n", space, tab , new);

}

#include <stdio.h>
#include <stdlib.h>

/* printd: print n in decimal */
void printd(int n)
{
if (n < 0) {
putchar('-');
n = -n;
}
if (n / 10)
printd(n / 10);
putchar(n % 10 + '0');
}

void main(){
  int d = 123123;
  printd(d);
  putchar('\n');
  d = -123123;
  printd(d);
}

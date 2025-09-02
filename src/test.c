#include <stdlib.h>
#include <stdio.h>


int main() {
  int a, b, c, d;
  a = Add(10, 5);
  printf("Addition = %d\n", a);

  b = Subtract(10, 5);
  printf("Subtraction = %d\n", b);

  c = Divide(10, 5);
  printf("Division = %d\n", c);

  d = Multiply(10, 5);
  printf("Multiplication = %d\n", d);

  return 0;
}
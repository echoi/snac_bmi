#define PI 3.14159265358979323846
#include <stdio.h>
#include <math.h>
int main(void)
{
  double x = 1.0 / 3.0 * PI / 2;
  double result = sin(x);
  printf("The sine of %lf is %lf\n", x, result);
  return 0;
}
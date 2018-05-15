// 1.Using 'long' to avoid integer overflow;
// 2.Add 'L' to avoid overflow compute.
#include <stdio.h>

int main(int argc, char **argv)
{
  long n = (1L << 31) - 1;
  printf("max int:%ld\n", n);
  return 0;
}

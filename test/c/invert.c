#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  if (argc < 2)
    goto err;

  int n = atoi(argv[1]);
  if (n < 0) {
    n = ~(n - 1);
    printf("invert n:%d\n", n);
    return 0;
  }

err:
  printf("please input a negative number.\n");
  return -1;
}

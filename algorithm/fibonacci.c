#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  if (argc < 2) {
    printf("fibonacci sequence:please input n...\n");
    return -1;
  }

  int n = atoi(argv[1]);
  if (n < 0) {
    printf("fibonacci sequence:n >= 0 is must...\n");
    return -1;
  }

  int i;
  int fn_2 = 1, fn_1 = 1;
  for (i = 2; i < n; i++) {
    int tmp = fn_1;
    fn_1 += fn_2;
    fn_2 = tmp;
  }

  if (i == n)
    printf("%d\n", fn_1 + fn_2);
  else
    printf("1\n");
  return 0;
}

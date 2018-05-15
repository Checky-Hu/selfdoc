#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *num, int l)
{
  if (l <= 1)
    return;
  int flag = num[0];
  int i = 0, j = l - 1;
  while (i < j) {
    while (i < j && num[j] >= flag)
      j--;
    num[i] = num[j];
    while (i < j && num[i] <= flag)
      i++;
    num[j] = num[i];
  }
  num[i] = flag;
  quick_sort(num, i);
  quick_sort(num + i, l - i - 1);
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("please input number list...\n");
    return -1;
  }

  int *num = malloc((argc -1) * sizeof(int));
  if (!num) {
    printf("out of memory\n");
    return -1;
  }

  printf("input number list:");
  for (int i = 0; i < argc - 1; i++) {
    num[i] = atoi(argv[i + 1]);
    printf("%d ", num[i]);
  }
  printf("\n");

  quick_sort(num, argc - 1);

  printf("after sort number list:");
  for (int i = 0; i < argc - 1; i++)
    printf("%d ", num[i]);
  printf("\n");
  return 0;
}

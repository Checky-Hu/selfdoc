#include <stdio.h>
#include <stdlib.h>

struct node {
  int val;
  struct node *next;
};

void binary_insert(struct node *num, int l, int *head_change)
{
  int i;
  for (i = 0; i < l - 1; i++)
    if (num[i].val >= num[l - 1].val)
      break;
  if (i == 0) {
    num[l - 2].next = NULL;
    num[l - 1].next = num;
    *head_change = 1;
  } else if (i == l - 1)
    num[l - 1].next = NULL;
  else {
    num[i - 1].next = num + l - 1;
    num[l - 1].next = num + i;
    if (i == l - 2)
      num[i].next = NULL;
  }
}

int main(int argc, char **argv)
{
  if (argc < 3) {
    printf("please input sequenced number list and target (n)...\n");
    return -1;
  }

  struct node *num = malloc((argc - 1) * sizeof(struct node));
  if (!num) {
    printf("out of memory\n");
    return -1;
  }

  int i;
  printf("input number list:");
  for (i = 0; i < argc - 1; i++) {
    num[i].val = atoi(argv[i + 1]);
    if (i < argc - 2) {
      num[i].next = num + i + 1;
      printf("%d ", num[i].val);
    } else
      printf("\ntarget (n):%d\n", num[i].val);
  }

  int head_change = 0;
  binary_insert(num, argc - 1, &head_change);
  struct node *tmp = num;
  if (head_change)
    tmp = num + argc - 2;

  printf("after insert number list:");
  for (; tmp; tmp = tmp->next)
    printf("%d ", tmp->val);
  printf("\n");
  free(num);
  return 0;
}

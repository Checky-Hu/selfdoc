#include <stdio.h>

int main()
{
  FILE * fp = popen("echo hello", "r");
  if (!fp)
    return -1;

  char res[32];
  while (fgets(res, sizeof(res), fp) != NULL)
    printf("%s", res);
  printf("\n");
  pclose(fp);
  return 0;
}

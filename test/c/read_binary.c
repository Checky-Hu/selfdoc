//process for read and show binary file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LEN 1024

int main(int argc, char ** argv)
{
  if (argc < 2) {
    printf("invalid parameters\n");
    return -1;
  }

  FILE* file = fopen(argv[1], "r");
  int i, len, total = 0;
  unsigned char buffer[BUF_LEN];
  do {
    memset(buffer, 0, BUF_LEN);
    if ((len = fread(buffer, 1, BUF_LEN, file)) > 0) {
      for (i = 0; i < len; i++)
        printf("%02x ", buffer[i]);
      printf("\n");
      total += len;
    } else
      break;
  } while (1);

  fclose(file);
  printf("total = %d\n", total);
  return 0;
}

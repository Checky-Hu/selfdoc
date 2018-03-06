#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  free(0);
  printf("%s\n", argv[1]);
  return 0;
}

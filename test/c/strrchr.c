#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv)
{
  if (argc > 1) {
    char * tmp = strrchr(argv[1], '/');
    if (tmp) {
      argv[1][tmp - argv[1]] = 0;
      printf("directory : %s\n", argv[1]);
    }
  }
  return 0;
}

// This testcase tell us that we should
// implements command line by our own.
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
  char * tmp[2];
  memset(tmp, 0, sizeof(char *) * 2);
  while (1) {
    int ret = getopt(argc, argv, "nz::o:");
    if (ret < 0)
      break;

    switch (ret) {
      case 'n':
        printf("n:no parameter\n");
        break;
      case 'z':
        tmp[0] = optarg;
        if (tmp[0])
          printf("z:%s\n", tmp[0]);
        else
          printf("z:no parameter mode\n");
        break;
      case 'o':
        tmp[1] = optarg;
        printf("o:%s\n", tmp[1]);
        break;
      default :
        printf("parameters - nz::o:\n");
    }
  }

  for (int i = 0; i < argc; i++)
    printf("argv[%d]:%s\n", i, argv[i]);
  return 0;
}

#include <stdio.h>

int main()
{
  unsigned int a = 0x1234;
  if ((char)a == 0x12)
    printf("big endian\n");
  else
    printf("little endian\n");
  return 0;
}

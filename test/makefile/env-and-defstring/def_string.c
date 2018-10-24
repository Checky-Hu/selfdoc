// show how to define a string marco in makefile
#include <stdio.h>

#ifndef DEFSTRING
#define DEFSTRING "DEFSTRING"
#error "DEFSTRING must be defined"
#endif

int main(int argc, char ** argv)
{
  printf(DEFSTRING"\n");
  return 0;
}

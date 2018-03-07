#include <stdio.h>

typedef int (* func_type)(int, int);
struct test_pfunc {
  void * pfunc;
};

int main()
{
  struct test_pfunc tmp;
  int self_func(int a, int b) {
    return a + b;
  }

  func_type func = self_func;
  tmp.pfunc = (void *)func;
  printf("result : %d == %d?\n", self_func(1, 2),
    ((func_type)tmp.pfunc)(1, 2));
  return 0;
}

#include <stdio.h>
#include <unistd.h>

int main()
{
  unsigned long pages = sysconf(_SC_PHYS_PAGES);
  unsigned long page_size1 = sysconf(_SC_PAGESIZE);
  unsigned long page_size2 = getpagesize();
  printf("page num:%ld, page size by sysconf:%ld,"
    " page size by getpagesize:%ld\n", pages,
    page_size1, page_size2);
  return 0;
}

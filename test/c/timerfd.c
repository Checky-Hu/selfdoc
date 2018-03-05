#include <errno.h>
#include <stdio.h>
#include <sys/timerfd.h>

int main()
{
  int fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
  printf("%d : %d\n", fd, errno);
  return 0;
}

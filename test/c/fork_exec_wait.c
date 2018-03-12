#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();
  if (pid < 0)
    return -1;
  else if (pid > 0) {
    int status = 0;
    while (1) {
      printf("parent waiting...\n");
      if (pid == waitpid(pid, &status, WNOHANG) &&
          WIFEXITED(status)) {
        printf("child return:%d\n", WEXITSTATUS(status));
        return 0;
      } else
        sleep(1);
    }
  } else {
    sleep(3);
    execlp("/bin/echo", "/bin/echo", "hello world!\n", NULL);
    return 2;
  }
}

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CHILD_CMD "echo"
#define CHILD_CMD_DIR "/bin/"

int main(int argc, char ** argv)
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
    // Exec family include : execl/execlp/execle/execv/
    // execvp. All these functions point to execve().
    // Use 'man exec' for more information.
    char * child_argv[3] = {CHILD_CMD, NULL, NULL};
    if (argc > 1)
      child_argv[1] = argv[1];
    else
      child_argv[1] = "hello world!";
    char * child_envp[1] = {NULL};
    execve(CHILD_CMD_DIR CHILD_CMD, child_argv, child_envp);
    return 2;
  }
}

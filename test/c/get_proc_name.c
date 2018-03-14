#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  DIR * dir = opendir("/proc");
  if (!dir) {
    perror("open /proc failed");
    return -1;
  }

  struct dirent * tmp_dir;
  char proc_info_path[32];
  char exe_name[PATH_MAX + 1];
  int count = 0;
  while (count < 10 && (tmp_dir = readdir(dir)) != NULL) {
    int pid = atoi(tmp_dir->d_name);
    if (pid > 900) {
      // is a normal process
      snprintf(proc_info_path, sizeof(proc_info_path),
          "/proc/%s/exe", tmp_dir->d_name);
      int len = readlink(proc_info_path, exe_name, PATH_MAX);
      exe_name[len] = 0;
      printf("pid:%d,name:%s\n", pid, exe_name);
      count++;
    }
  }
  closedir(dir);
  return 0;
}

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TMP_BUFFER_SIZE 1024
#define BUFFER_SIZE 65536

#define UTIME_POS 13
#define RSS_POS 23

static pid_t cur_pid = 0;

static int ReadFileToBuffer(const char* path, char* result) {
  FILE* file = fopen(path, "rb");
  if (!file) {
    return -1;
  }

  char buf[TMP_BUFFER_SIZE];
  int len;
  int size = 0;

  while ((len = fread(buf, 1, TMP_BUFFER_SIZE, file)) > 0) {
    memcpy(result + size, buf, len);
    size += len;
  }
  fclose(file);
  result[size] = 0;
  return 0;
}

int GetMemoryUsage() {
  if (cur_pid == 0) {
    cur_pid = getpid();
  }

  char proc_file[128];
  snprintf(proc_file, 128, "/proc/%d/stat", cur_pid);
  char result[BUFFER_SIZE];
  if (ReadFileToBuffer(proc_file, result)) {
    return 0;
  }

  char* p = strtok(result, " ");
  int i = 1;
  for (; i <= RSS_POS; i++) {
    p = strtok(NULL, " ");
  }

  int value = atoi(p);
  return value / 250;
}


int64_t ClockNowInMS() {
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
    return 0;
  }
  return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

int64_t ClockTicksToTimeDelta(int clock_ticks) {
  // This queries the /proc-specific scaling factor which is
  // conceptually the system hertz.  To dump this value on another
  // system, try
  //   od -t dL /proc/self/auxv
  // and look for the number after 17 in the output; mine is
  //   0000040          17         100           3   134512692
  // which means the answer is 100.
  // It may be the case that this value is always 100.
  static int kHertz = 0;
  if (kHertz == 0) {
    kHertz = sysconf(_SC_CLK_TCK);
  }

  return 1000000 * clock_ticks / kHertz;
}

// Get the total CPU of a single process.  Return value is number of jiffies
// on success or -1 on error.
int GetProcessCPU() {
  // Use /proc/<pid>/task to find all threads and parse their /stat file.
  if (cur_pid == 0) {
    cur_pid = getpid();
  }

  char task_file[128];
  snprintf(task_file, 128, "/proc/%d/task", cur_pid);

  DIR* dir = opendir(task_file);
  if (!dir) {
    return -1;
  }

  int total_cpu = 0;
  char result[BUFFER_SIZE];
  struct dirent* ent = NULL;
  while ((ent = readdir(dir)) != NULL) {
    if (strncmp(ent->d_name, ".", 1) == 0 || strncmp(ent->d_name, "..", 2) == 0)
      continue;

    char task_thread_file[512];
    snprintf(task_thread_file, sizeof(task_thread_file), "/proc/%d/task/%s/stat", cur_pid, ent->d_name);
    if (ReadFileToBuffer(task_thread_file, result) == 0) {
      char* p = strtok(result, " ");
      int i = 1;
      for (; i <= UTIME_POS; i++) {
        p = strtok(NULL, " ");
      }

      int utime = atoi(p);
      p = strtok(NULL, " ");
      int stime = atoi(p);
      total_cpu += utime + stime;
    }
  }
  closedir(dir);

  return total_cpu;
}

static int last_cpu = 0;
static int64_t last_cpu_time = 0;

int GetCPUUsage() {
  int64_t time = ClockNowInMS();

  if (last_cpu == 0) {
    // First call, just set the last values.
    last_cpu_time = time;
    last_cpu = GetProcessCPU();
    return 0;
  }

  int64_t time_delta = time - last_cpu_time;
  if (time_delta == 0) {
    return 0;
  }

  int cpu = GetProcessCPU();

  // We have the number of jiffies in the time period.  Convert to percentage.
  // Note this means we will go *over* 100 in the case where multiple threads
  // are together adding to more than one CPU's worth.
  int64_t cur_cpu_time = ClockTicksToTimeDelta(cpu);
  int64_t cur_last_cpu_time = ClockTicksToTimeDelta(last_cpu);

  // If the number of threads running in the process has decreased since the
  // last time this function was called, |last_cpu_time| will be greater than
  // |cpu_time| which will result in a negative value in the below percentage
  // calculation. We prevent this by clamping to 0. crbug.com/546565.
  // This computation is known to be shaky when threads are destroyed between
  // "last" and "now", but for our current purposes, it's all right.
  int percentage = 0;
  if (cur_last_cpu_time < cur_cpu_time) {
    percentage = 100 * (cur_cpu_time - cur_last_cpu_time) /
        time_delta;
  }

  last_cpu_time = time;
  last_cpu = cpu;

  // two cores.
  return percentage / 2;
}

int main(int argc, char ** argv) {
  int mem_usage = GetMemoryUsage();
  int cpu_usage = GetCPUUsage();
  printf("Mem: %d%%, Cpu: %d%%\n", mem_usage, cpu_usage);
}

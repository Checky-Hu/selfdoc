#include <linux/netlink.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_LEN 2048

int main()
{
  struct sockaddr_nl sa_nl;
  memset(&sa_nl, 0, sizeof(struct sockaddr_nl));
  sa_nl.nl_family = AF_NETLINK;
  sa_nl.nl_pid = getpid();
  sa_nl.nl_groups = 1;

  int sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
  if (sock < 0) {
    perror("socket call");
    return -1;
  }

  const int buf_size = 1 << 24;
  setsockopt(sock, SOL_SOCKET, SO_RCVBUFFORCE, &buf_size, sizeof(buf_size));
  int ret = bind(sock, (struct sockaddr*)&sa_nl, sizeof(struct sockaddr_nl));
  if (ret < 0) {
    perror("bind call");
    close(sock);
    return -1;
  }

  char buf[BUF_LEN] = {0};
  while (1) {
    recv(sock, buf, BUF_LEN, 0);
    printf("%s\n", buf);
  }
  return 0;
}

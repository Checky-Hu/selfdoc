// test struct cmsghdr
// 's' as server, 'c' as client
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_NAME "/tmp/testsock"

void start_client(char * str)
{
  int sock_fd;
  if ((sock_fd = socket(PF_LOCAL, SOCK_SEQPACKET | SOCK_CLOEXEC, 0)) < 0) {
    perror("socket : socket failed at client.");
    return;
  }

  struct sockaddr_un serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sun_family = AF_LOCAL;
  strcpy(serv_addr.sun_path, SOCK_NAME);

  if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("socket : connect failed at client.");
    return;
  }

  int size = write(sock_fd, str, strlen(str));
  printf("socket : client already send %d bytes[%s].\n", size, str);
  close(sock_fd);
  return;
}

void start_server()
{
  int listen_fd;
  if ((listen_fd = socket(PF_LOCAL, SOCK_SEQPACKET, 0)) < 0) {
    perror("socket : socket failed at server.");
    return;
  }

  int on = 1;
  setsockopt(listen_fd, SOL_SOCKET, SO_PASSCRED, &on, sizeof(on));

  unlink(SOCK_NAME);
  struct sockaddr_un serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sun_family = AF_LOCAL;
  strcpy(serv_addr.sun_path, SOCK_NAME);

  if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("socket : bind failed at server.");
    return;
  }

  if (listen(listen_fd, 1) < 0) {
    perror("socket : listen failed at server.");
    return;
  }

  int conn_fd;
  char buffer[128];
  struct iovec iov = {buffer, sizeof(buffer)};
  char control[CMSG_SPACE(sizeof(struct ucred))];
  struct msghdr hdr = {
    NULL, 0, &iov, 1, control, sizeof(control), 0};
  int size;
  struct ucred *cred = NULL;
  struct cmsghdr *cmsg = NULL;
  while (1) {
    memset(buffer, 0, sizeof(buffer));
    if ((conn_fd = accept(listen_fd, NULL, NULL)) < 0) {
      perror("socket : accept failed at server");
      continue;
    }

    size = recvmsg(conn_fd, &hdr, 0);
    cmsg = CMSG_FIRSTHDR(&hdr);
    while (cmsg) {
      if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_CREDENTIALS) {
        cred = (struct ucred *)CMSG_DATA(cmsg);
        break;
      }
      cmsg = CMSG_NXTHDR(&hdr, cmsg);
    }

    //buf[size] = 0;
    printf("socket : server already receive %d bytes.\n", size);
    printf("socket : server receive credentials [pid=%d][uid=%d][gid=%d].\n",
        cred->pid, cred->uid, cred->gid);
    printf("socket : server receive message [msg_name=%s][msg_namelen=%d]"\
        "[iov_buffer=%s][msg_controllen=%ld].\n", (char *)hdr.msg_name, hdr.msg_namelen,\
        buffer, hdr.msg_controllen);
    close(conn_fd);
  }
  close(listen_fd);
  return;
}

int main(int argc, char ** argv)
{
  if (argc < 2) {
    printf("socket : need at least 1 param.\n");
    return -1;
  }

  if (argv[1][0] == 'c') {
    if (argc < 3) {
      printf("socket : client need at least 2 param.\n");
      return -1;
    } else
      start_client(argv[2]);
  } else if (argv[1][0] == 's')
    start_server();
  else {
    printf("socket : first param must be 's' or 'c'.\n");
    return -1;
  }

  return 0;
}

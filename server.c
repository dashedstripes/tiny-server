#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int running = 1;

void sighandler(int signum) {
  running = 0;
  printf("Caught signal, exiting...\n");
  exit(1);
}

int main() {
  signal(SIGINT, sighandler);

  int sfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sfd == -1) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8080);

  socklen_t addr_size = sizeof(addr);

  if (bind(sfd, (struct sockaddr *)&addr, addr_size) == -1) {
      perror("bind failed");
      close(sfd);
      exit(EXIT_FAILURE);
  }

  if (listen(sfd, 10) < 0) {
      perror("Listen failed");
      close(sfd);
      return -1;
  }

  while (running) {
      int addrlen = sizeof(addr);
      int new_socket = accept(sfd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
      if (new_socket < 0) {
          perror("Accept failed");
          break;
      }

      char buffer[1024] = {0};
      ssize_t bytes_read = read(new_socket, buffer, 1024);
      if (bytes_read > 0) {
          printf("Message from client: %s\n", buffer);
      }

      close(new_socket);
  }

  close(sfd); // Close the socket descriptor

  return 0;
}
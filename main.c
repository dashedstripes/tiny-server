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

  int socketId = socket(AF_INET, SOCK_STREAM, 0);

  if (socketId == -1) {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr)); // Ensure the structure is empty
  addr.sin_family = AF_INET; // Address family (IPv4)
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // Any local IP address
  addr.sin_port = htons(8080); // Convert port number to network byte order

  socklen_t addr_size = sizeof(addr);

  if (bind(socketId, (struct sockaddr *)&addr, addr_size) == -1) {
      perror("bind failed");
      close(socketId);
      exit(EXIT_FAILURE);
  }
  
  if (getsockname(socketId, (struct sockaddr *)&addr, &addr_size) == -1) {
      perror("getsockname failed");
      close(socketId);
      exit(EXIT_FAILURE);
  }

  printf("Socket bound to IP: %s, Port: %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

  while(running) {
    printf("Going to sleep for a second...\n");
    sleep(1);
  }

  close(socketId); // Close the socket descriptor

  return 0;
}
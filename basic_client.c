#include "pipe_networking.h"

int main() {
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  char s[50];
  int i = 0;

  while (1) {
    sprintf(s, "client pid %d request #%d", getpid(), i++);
    if (write(to_server, s, sizeof(s)) == -1) {
      perror("client write");
      exit(1);
    }
    printf("sent: %s\n", s);
  }
}

#include "pipe_networking.h"

int main() {
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  char s[50];
  int i = 0;

  while (1) {
    sprintf(s, "client pid %d request #%d", getpid(), i++);
    if (write(to_server, s, sizeof(s)) <= 0) {
      exit(0);
    }
    printf("sent: %s\n", s);
    sleep(1);
  }
  close(to_server);
	close(from_server);
}

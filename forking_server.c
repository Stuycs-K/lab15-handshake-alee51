#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove(WKP);
        exit(0);
    }
}

int main() {
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, sighandler);

  while (1) {
    int to_client;
    int from_client;
    from_client = server_setup();
    int f = fork();
    if (f == 0) { //subserver
        server_handshake_half(&to_client, from_client);

        char buff[256];
        while (1) {
            if (read(from_client, buff, sizeof(buff)) == -1) {
                break;
            }
            printf("received: %s\n", buff);
            sleep(1);
        }
        exit(0);
    }
    close(to_client);
    close(from_client);
  }
}

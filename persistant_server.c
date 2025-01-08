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
  int to_client;
  int from_client;
  while (1) {
    from_client = server_handshake( &to_client );

    int rand_int;
    int r_file = open("/dev/random", O_RDONLY, 0);
    while(1) {
        read(r_file, &rand_int, 4);
        rand_int = abs(rand_int) % 101;
        // printf("rand_int = %d\n", rand_int);
        if (write(to_client, &rand_int, 4) == -1) {
            break;
        }
        sleep(1);
    }
    close(to_client);
    close(from_client);
  }
}

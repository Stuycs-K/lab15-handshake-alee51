#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  while (1) {
    int rand_int;
    int bytes = read(from_server, &rand_int, 4);
    if (bytes <= 0) {
      exit(0);
    }
    printf("%d\n", rand_int);
  }
}

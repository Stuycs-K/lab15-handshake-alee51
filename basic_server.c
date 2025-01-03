#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  int rand_int;
  int r_file = open("/dev/random", O_RDONLY, 0);
  while(1) {
    read(r_file, &rand_int, 4);
    rand_int = abs(rand_int) % 101;
    // printf("rand_int = %d\n", rand_int);
    write(to_client, &rand_int, 4);
    sleep(1);
  }
}

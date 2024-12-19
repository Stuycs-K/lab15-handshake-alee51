#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
#define PIPE_NAME "./wkp"
int server_setup() {
  int from_client = mkfifo(PIPE_NAME, 0666);
  if (from_client == -1) {
    perror("mkfifo fail");
    exit(1);
  }
  int wkp = open(PIPE_NAME, O_RDONLY);
  if (wkp == -1) {
    perror("open wkp fail");
    exit(1);
  }
  remove(PIPE_NAME);
  return from_client;
}

/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  //making private pipe
  char pp[10];
  int bytes = sprintf(pp, "./%d", getpid());
  if (bytes == -1) {
    perrof("sprintf");
    exit(1);
  }
  int from_server = mkfifo(pp, 0666);
  //opening WKP
  int wkp_c = open(PIPE_NAME, O_WRONLY);
  if (wkp_c == -1) {
    perror("open wkp_c fail");
  }
  //writing PP to WKP
  int wkp_w = write(PIPE_NAME, getpid(), 4);
  if (wkp_w == -1) {
    perror("write wkp fail");
    exit(1);
  }
  //opening PP
  int to_server = open(pp, O_RDONLY);
  if (to_server == -1) {
    perror("open pp fail");
    exit(1);
  }
  
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}



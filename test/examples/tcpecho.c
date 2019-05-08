#include <pico_icmp4.h>
#include <pico_bsd_sockets.h>
/*** START TCP ECHO ***/
#define BSIZE 1024


// based off of https://github.com/mafintosh/echo-servers.c/blob/master/tcp-echo-server.c
void app_tcpecho()
{
  char buf[BSIZE];
  struct sockaddr_in server = {0}, client={0};
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 6667;

  /* end of argument parsing */
  int s = pico_newsocket(AF_INET, SOCK_STREAM, PICO_PROTO_TCP);

  // pico_socket_setoption(s, PICO_TCP_NODELAY, &yes);

  int ret = pico_bind(s, &server, sizeof(server));

  if (ret < 0) {
    printf("%s: error binding socket to port %u: %d\n", __FUNCTION__, short_be(55), pico_err);
    exit(1);
  }

  if (pico_listen(s, 128) != 0) {
    printf("%s: error listening on port %u\n", __FUNCTION__, short_be(55));
    exit(1);
  }

  printf("Launching PicoTCP echo server\n");

  while(1) {
    int client_len;
    ret = pico_accept(s, &client, &client_len);
    if (ret < 0) {
      printf("error accepting connection\n");
      exit(1);
    }
    printf("got a connection.\n");

    while(1) {
      int read = pico_recv(ret, buf, BSIZE, 0);
      if (!read) break;
      if (read < 0) {
        printf("error reading\n");
        exit(1);
      }
      if (pico_send(ret, buf, read, 0) < 0) {
        printf("error writing\n");
        exit(1);
      }
    }
  }
  return;
}

/*** END TCP ECHO ***/

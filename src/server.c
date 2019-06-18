#include "game.h"
#include "util.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int c1, c2;
struct game game;
pthread_mutex_t game_lock;

void *handle_client(void *argv) {
  int client = *(int *)argv;

  while (1) {
    int c;
    if (recv(client, &c, sizeof(c), 0) == 0) {
      printf("Client %i exited\n", client);
      break; // Client quit
    }
    printf("Got %c from client %i\n", c, client);
    if (c == 'q') {
      game.over = 1;
      break;
    }

    const float dy = 0.01;
    pthread_mutex_lock(&game_lock);
    switch (c) {
    case 'k':
      if (client == c1) {
        game.left_bar.y -= dy;
      } else if (client == c2) {
        game.right_bar.y -= dy;
      }
      break;
    case 'j':
      if (client == c1) {
        game.left_bar.y += dy;
      } else if (client == c2) {
        game.right_bar.y += dy;
      }
      break;
    }
    pthread_mutex_unlock(&game_lock);
  }

  return NULL;
}

int serve(int port) {
  int sock = socket(PF_INET, SOCK_STREAM, 0), opt = 1;
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = INADDR_ANY,
      .sin_port = htons(port),
  };

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("bind");
    exit(1);
  }

  if (listen(sock, 1) == -1) {
    perror("listen");
    exit(1);
  }

  printf("Listening on port %i\n", port);
  return sock;
}

int main(int argc, char *argv[]) {

  // Check arguments
  if (argc != 2) {
    die("Please provide a port\n");
  }

  int port;
  if (!(port = atoi(argv[1]))) {
    die("Invalid port\n");
  }

  int sock = serve(port);

  pthread_t t1;
  c1 = accept(sock, NULL, NULL);
  pthread_create(&t1, NULL, handle_client, &c1);
  puts("Client 1/2 connected");

  pthread_t t2;
  c2 = accept(sock, NULL, NULL);
  pthread_create(&t2, NULL, handle_client, &c2);
  puts("Client 2/2 connected");

  if (c1 == -1 || c2 == -1) {
    perror("accept");
    exit(1);
  }

  if (pthread_mutex_init(&game_lock, NULL) != 0) {
    die("Mutex failed");
  }

  game_init(&game);
  do {

    pthread_mutex_lock(&game_lock);
    game_step(&game);
    send(c1, &game, sizeof(struct game), 0);
    send(c2, &game, sizeof(struct game), 0);
    pthread_mutex_unlock(&game_lock);

    const int UPS = 100;
    const int MS_IN_S = 1000000;
    usleep(MS_IN_S / UPS);

  } while (!game.over);

  pthread_mutex_destroy(&game_lock);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  close(c1);
  close(c2);
  close(sock);
}

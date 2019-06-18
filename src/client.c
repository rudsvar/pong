#include "game.h"
#include "util.h"
#include <arpa/inet.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Establish a TCP connection to the
// given ip and port, then return the socket.
int connect_to_server(const char *ip, int port) {
  int sock = socket(PF_INET, SOCK_STREAM, 0), opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_addr.s_addr = inet_addr(ip),
      .sin_port = htons(port),
  };

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("connect");
    exit(1);
  }
  printf("Connected to host %s:%i\n", ip, port);

  return sock;
}

void ncurses_init() {
  initscr();
  nodelay(stdscr, 1);
  cbreak();
  noecho();
  curs_set(0);
}

void ball_display(struct ball *ball, int maxy, int maxx) {
  mvprintw(ball->y * maxy, ball->x * maxx, "O");
}

void bar_display(struct bar *bar, int maxy, int maxx) {
  for (int i = 0; i < bar->height * maxy; ++i) {
    mvprintw(bar->y * maxy + i, bar->x * maxx, "#");
  }
}

void game_display(struct game *game) {
  int maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);

  ball_display(&game->ball, maxy, maxx);
  bar_display(&game->left_bar, maxy, maxx);
  bar_display(&game->right_bar, maxy, maxx);
}

int main(int argc, char *argv[]) {

  // Check arguments
  if (argc != 3) {
    die("Please provide the server IP and port\n");
  }

  const char *ip = argv[1];
  int port;
  if (!(port = atoi(argv[2]))) {
    die("Invalid port\n");
  }

  int sock = connect_to_server(ip, port);

  ncurses_init();
  mvprintw(0, 0, "Waiting for opponent");

  while (1) {
    // Send input to server
    int c = getch();
    if (c != -1) {
      if (send(sock, &c, sizeof(c), 0) == 0) {
        perror("send");
        break;
      }
    }

    struct game game;
    if (recv(sock, &game, sizeof(struct game), 0) == 0) {
      break;
    }

    if (game.over) {
      break;
    }

    erase();
    game_display(&game);
    refresh();

    const int UPS = 60;
    sleep_ms(1000 / UPS);
  }

  close(sock);
  endwin();
}

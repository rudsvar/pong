#pragma once

#include "game.h"

enum message_type { DRAW, QUIT };

struct message {
  enum message_type type;
  struct game game;
};

int send_message(int fd, struct message msg);
int recv_message(int fd, struct message msg);

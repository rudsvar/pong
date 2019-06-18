#pragma once

#include "ball.h"
#include "bar.h"

struct game {
  int over;
  struct bar left_bar, right_bar;
  struct ball ball;
};

void game_init(struct game *game);
void game_step(struct game *game);

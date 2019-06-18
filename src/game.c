#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game_init(struct game *game) {
  game->over = 0;
  game->left_bar = (struct bar){0.001, 0.5, 0.2};
  game->right_bar = (struct bar){0.999, 0.5, 0.2};
  srand(time(NULL));
  float rand_dx = (rand() % 150 + 150) / 100000.0;
  if (rand() % 2 == 0)
    rand_dx = -rand_dx;
  float rand_dy = (rand() % 300 - 150) / 100000.0;
  game->ball = (struct ball){0.5, 0.5, rand_dx, rand_dy};
}

void game_step(struct game *game) {

  ball_step(&game->ball);

  int bounce = 0;

  // Hit left
  struct bar lbar = game->left_bar;
  if (game->ball.x <= lbar.x) {
    if (lbar.y < game->ball.y && game->ball.y < lbar.y + lbar.height) {
      game->ball.dx *= -1;
      bounce = 1;
    }
  }

  // Hit right
  struct bar rbar = game->right_bar;
  if (rbar.x <= game->ball.x) {
    if (rbar.y < game->ball.y && game->ball.y < rbar.y + rbar.height) {
      game->ball.dx *= -1;
      bounce = 1;
    }
  }

  if (!bounce && (game->ball.x <= 0 || 1 <= game->ball.x)) {
    game->over = 1;
  }
}

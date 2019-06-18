#include "game.h"
#include <stdio.h>

void game_init(struct game *game) {
  game->over = 0;
  game->left_bar = (struct bar){0.01, 0.5, 0.2};
  game->right_bar = (struct bar){0.99, 0.5, 0.2};
  game->ball = (struct ball){0.5, 0.5, 0.002, 0.002};
}

void game_step(struct game *game) {
  if (game->ball.x <= 0 || 1 <= game->ball.x) {
    game->over = 1;
  }

  ball_step(&game->ball);

  const double precision = 0.002;

  // Hit left
  struct bar lbar = game->left_bar;
  if (lbar.x - precision < game->ball.x && game->ball.x < lbar.x + precision) {
    if (lbar.y < game->ball.y && game->ball.y < lbar.y + lbar.height) {
      game->ball.dx *= -1;
    }
  }

  // Hit right
  struct bar rbar = game->right_bar;
  if (rbar.x - precision < game->ball.x && game->ball.x < rbar.x + precision) {
    if (rbar.y < game->ball.y && game->ball.y < rbar.y + rbar.height) {
      game->ball.dx *= -1;
    }
  }
}

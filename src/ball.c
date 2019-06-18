#include "ball.h"

void ball_step(struct ball *ball) {
  ball->x += ball->dx;
  ball->y += ball->dy;

  // Reverse if bottom or top hit
  if (ball->y <= 0 || 1 <= ball->y) {
    ball->dy = -ball->dy;
  }
}

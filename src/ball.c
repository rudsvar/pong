#include "ball.h"

void ball_step(struct ball *ball) {
  ball->x += ball->dx;
  ball->y += ball->dy;
  ball->dx *= 1.001;
  ball->dy *= 1.001;

  // Reverse if bottom or top hit
  if (ball->y <= 0 || 1 <= ball->y) {
    ball->dy = -ball->dy;
  }
}

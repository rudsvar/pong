#pragma once

struct ball {
  float x, y;
  float dx, dy;
};

void ball_step(struct ball *ball);

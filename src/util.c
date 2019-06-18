#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void die(char *msg) {
  fwrite(msg, sizeof(char), strlen(msg), stderr);
  exit(1);
}

void sleep_ms(int ms) { usleep(1000 * ms); }

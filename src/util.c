#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(char *msg) {
  fwrite(msg, sizeof(char), strlen(msg), stderr);
  exit(1);
}

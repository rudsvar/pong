#include "message.h"
#include <arpa/inet.h>

int send_message(int fd, struct message msg) {
  return send(fd, &msg, sizeof(struct message), 0);
}

int recv_message(int fd, struct message msg) {
  return recv(fd, &msg, sizeof(struct message), 0);
}

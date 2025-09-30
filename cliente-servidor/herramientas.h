#ifndef HERRAMIENTAS_H
#define HERRAMIENTAS_H

#include <sys/socket.h>
#include <signal.h>

int reuse(int socket_fd);

void manejar_ctrl_c(int sigmal);

void llamada_manejar(int socket_fd);

#endif

#ifndef __TRAITEMENT__
#define __TRAITEMENT__
#define ERR_FORK 1
#define ERR_SOCKCLI 2

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "http.h"

#define TAILLE_BUFFER 8192

int gererRequete(int socketServeur, char* root);

#endif
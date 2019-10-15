#ifndef __RESEAU__
#define __RESEAU__
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define ERR_SOCKSERV 3
#define ERR_BIND 4

struct sockaddr_in construireAdresseDepuisChaine(char* adresseIP, char* port);
int creerSocketTCPServeur(struct sockaddr_in adresse);

#endif
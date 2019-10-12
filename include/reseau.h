#ifndef __RESEAU__
#define __RESEAU__
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in construireAdresseDepuisChaine(char* adresseIP, char* port);
int creerSocketTCPServeur(struct sockaddr_in adresse);

#endif
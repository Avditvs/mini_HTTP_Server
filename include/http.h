#ifndef __HTTP__
#define __HTTP__
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/stat.h>


int sendHttpResponse(char* fileName, int socketClient);


#endif
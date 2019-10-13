#include "traitement.h"

int sendHttpResponse(FILE* file, int socketClient)
{
    int erreur;
    char* httpHeader = malloc(500*sizeof(char));
    strcpy(httpHeader, "HTTP/1.0 200 OK\r\n\n");

    fseek(file, 0, SEEK_END);
    int contentLenght = ftell(file);
    rewind(file);

    char* responseData = malloc(contentLenght+1);
    fread(responseData, contentLenght, 1, file);
    responseData[contentLenght]=0;
    
    erreur = send(socketClient, httpHeader, strlen(httpHeader)*sizeof(char),0);
    erreur = send(socketClient, responseData, contentLenght, 0);

    free(httpHeader);
    free(responseData);
    return erreur;
}

int traiterRequete(int socketClient){
    char* buffer = malloc(TAILLE_BUFFER*sizeof(char));
    read(socketClient, buffer, TAILLE_BUFFER);
    char* getRequest = strtok(buffer, "\n");
    int i =0;
    getRequest = strtok(getRequest, " ");
    while(i!=1){
        i++;
        getRequest = strtok(NULL, " ");
    }
    printf("%s\n", getRequest);

    FILE* fptr;
    fptr = fopen(getRequest+1,"r");
    if(!fptr){
        return -1;
    }
    else{
        
        sendHttpResponse(fptr, socketClient);
        close(socketClient);
    }

    free(buffer);


    return -1;
}




int gererRequete(int socketServeur){
    socklen_t longueurAdresseClient;
    struct sockaddr_in adresseClient;
    int socketClient;
    int erreur = 0;
    longueurAdresseClient=sizeof adresseClient;
    socketClient = accept(socketServeur, (struct sockaddr *) &adresseClient, &longueurAdresseClient);
    if(socketClient!=-1){
        if(traiterRequete(socketClient))
            close(socketClient);
        else
            erreur=-1;
    }
    else
        erreur=-1;
    return erreur;
}


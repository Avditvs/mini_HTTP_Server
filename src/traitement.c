#include "traitement.h"


int traiterRequete(int socketClient){
    char* buffer = calloc(1, TAILLE_BUFFER*sizeof(char));
    read(socketClient, buffer, TAILLE_BUFFER);
    printf("Requete : \n %s\n", buffer);
    char* getRequest = strtok(buffer, "\n");
    int i =0;
    getRequest = strtok(getRequest, " ");
    while(i!=1){
        i++;
        getRequest = strtok(NULL, " ");
    }
    sendHttpResponse(getRequest, socketClient);

    free(buffer); buffer=NULL;
    getRequest = NULL;
    return -1;
}




int gererRequete(int socketServeur){
    socklen_t longueurAdresseClient;
    struct sockaddr_in adresseClient;
    int socketClient;
    int erreur = 0;
    pid_t PID;
    longueurAdresseClient=sizeof adresseClient;
    socketClient = accept(socketServeur, (struct sockaddr *) &adresseClient, &longueurAdresseClient);
    if(socketClient!=-1){
        if((PID=fork())!=-1){
            if(PID==0){
                if(traiterRequete(socketClient)){
                    close(socketClient);
                    exit(0);
                }
                else{
                    erreur = -1;
                }
            }else{
                close(socketClient);
            }
        }else{
            erreur=-1;
        }
    }
    else
        erreur=-1;
    return erreur;
}


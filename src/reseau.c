#include "reseau.h"


struct sockaddr_in construireAdresseDepuisChaine(char* adresseIP, char* port){
    struct sockaddr_in adresse;
    memset(&adresse,0,sizeof adresse);
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(atoi(port));
    adresse.sin_addr.s_addr = inet_addr(adresseIP);/* ou INADDR_ANY */
    return adresse;
}

int creerSocketTCPUDPServeur(struct sockaddr_in adresse,int mode){
    int resultat;
    int longueurAdresse;

    resultat = socket(PF_INET,mode,0);

    if (setsockopt(resultat, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
        exit(1);
        
    if((resultat == -1) || (adresse.sin_addr.s_addr== INADDR_NONE))
        return ERR_SOCKSERV;
    else{
        longueurAdresse = sizeof adresse;
        if(bind(resultat,(struct sockaddr *)&adresse,longueurAdresse)!=-1)
            return resultat;
        else
            return ERR_BIND;
    }
}

int creerSocketTCPServeur(struct sockaddr_in adresse){
    int socket = creerSocketTCPUDPServeur(adresse,SOCK_STREAM);
    return socket;
}


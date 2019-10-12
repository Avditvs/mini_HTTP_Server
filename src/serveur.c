#include "reseau.h"
#include "traitement.h"
#include <stdio.h>

int obtenirSocketServeur(char* adresseServeur, char* portServeur){
    struct sockaddr_in adresseTCPUDP = construireAdresseDepuisChaine(adresseServeur, portServeur);
    return creerSocketTCPServeur(adresseTCPUDP);
}

int ecouter(int socketServeur,int longueurFileDAttente){
    int erreur=0;
    erreur=listen(socketServeur,longueurFileDAttente);
    while(erreur!=-1){
        erreur = gererLaRequete(socketServeur);
    }
    return erreur;
}

int main(int argc, char** argv){
    char* adresseServeur = NULL;
    char* portServeur = "9099";
    if( argc >= 2 ){
        adresseServeur=argv[1];
    }
    else{
        adresseServeur="127.0.0.1";
    }
    if( argc >= 3 )
        portServeur=argv[2];

    printf("%i", obtenirSocketServeur(adresseServeur, portServeur));
}
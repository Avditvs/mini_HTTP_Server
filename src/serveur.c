#include "reseau.h"
#include "traitement.h"
#include <stdio.h>

int obtenirSocketServeur(char* adresseServeur, char* portServeur){
    struct sockaddr_in adresseTCPUDP = construireAdresseDepuisChaine(adresseServeur, portServeur);
    free(adresseServeur);
    free(portServeur);
    return creerSocketTCPServeur(adresseTCPUDP);
}

int ecouter(int socketServeur,int longueurFileDAttente, char* root){
    int erreur=0;
    erreur=listen(socketServeur,longueurFileDAttente);
    while(erreur==0){
        erreur = gererRequete(socketServeur, root);
    }
    return erreur;
}

int main(int argc, char** argv){
    char* adresseServeur = malloc(100*sizeof(char));
    char* portServeur = malloc(100*sizeof(char));
    char* fichierConfig;
    char* str = malloc(100*sizeof(char));
    char* conf;
    char* param;
    char* root = malloc(100*sizeof(char));
    int erreur;

    strcpy(adresseServeur, "127.0.0.1");
    strcpy(portServeur, "8080");
    strcpy(root, "www");

    if(argc>=2){
        fichierConfig = argv[1];
        if( access( fichierConfig, F_OK ) == -1 ) {
            fichierConfig = "/etc/serverHttp.conf";
            printf("%s\n", "Fichier de config introuvable, utilisation de /etc/serverHttp.conf");
        }
    }else{
        fichierConfig = "/etc/serverHttp.conf";
        printf("Pas de configuration spécifiée, utilisation de /etc.serverHttp.conf\n");
    }

    
    FILE* config = fopen(fichierConfig, "r");
    if(!config){
        printf("%s\n", "Fichier de configuration /etc/serverHttp.conf introuvable, utilisation des paramètres par défaut");
    }else{
        while (fgets(str, 99, config) != NULL){
            if(strlen(str)>1){
                conf = strtok(str, "=");
                param = strtok(NULL, "=");
                param[strlen(param)-1]='\0';

                if(strcmp(conf, "websiteRoot")==0){
                    strcpy(root, param);
                }else if(strcmp(conf, "ipAddr")==0){
                    strcpy(adresseServeur, param);
                }else if(strcmp(conf, "port")==0){
                    strcpy(portServeur, param);
                }
            }
        }
        fclose(config);
    }

        printf("%s", "Starting server on port ");
        printf("%s", portServeur);
        printf("%s", ", with address : ");
        printf("%s\n", adresseServeur);
        printf("Root directory : %s\n", root);

        free(str);
        erreur = ecouter(obtenirSocketServeur(adresseServeur, portServeur),10, root);
        free(root);
        printf("%i", erreur);
}
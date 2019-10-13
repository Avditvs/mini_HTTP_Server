#include "http.h"

char* generateHttpHeader(int responseCode){
    char* httpHeader = malloc(100*sizeof(char));
    switch(responseCode){
        case 200:
            strcpy(httpHeader, "HTTP/1.0 200 OK\r\n\0");
            break;
        case 404:
            strcpy(httpHeader, "HTTP/1.0 404 Not Found\r\n\0");
            break;
        case 500:
            strcpy(httpHeader, "HTTP/1.0 500 Internal Server Error\r\n\0");
        default:
            return 0;
        }
    return httpHeader;
}


char* addHeaderField(char* httpHeader, char* nom, char* champ){
    int fieldLen = strlen(httpHeader) + strlen(nom) + strlen(champ)+5;
    char* newHeader = malloc((fieldLen)*sizeof(char));

    strcpy(newHeader, httpHeader);
    strcat(newHeader, nom);
    strcat(newHeader, " : \0");
    strcat(newHeader, champ);
    strcat(newHeader, "\r\n\0");


    free(httpHeader);
    return newHeader;
}

char* endHeader(char* httpHeader){
    char* newHeader = malloc((strlen(httpHeader)+1)*sizeof(char));
    strcpy(newHeader, httpHeader);
    strcpy(newHeader+strlen(newHeader), "\n");
    free(httpHeader);
    return newHeader;
}


char* addContentType(char* httpHeader, char* fileName){
    char* copyFn = malloc(strlen(fileName) + 1); 
    strcpy(copyFn, fileName);
    char* extension = strtok(copyFn, ".");
    extension = strtok(NULL, ".");


    if(strcmp(extension,"")){
        httpHeader = addHeaderField(httpHeader,"content-type", "text/plain");
    }else{
        httpHeader = addHeaderField(httpHeader,"content-type", "text/plain");
    }

    free(copyFn);
    return httpHeader;
}

int sendHttpResponse(char* fileName, int socketClient)
{
    fileName = fileName+1; // enlever le / devant le nom de fichier
    FILE* fptr;
    fptr = fopen(fileName,"r");
    if(!fptr){
        return -1;
    }
    else{
        int erreur;
        char* httpHeader = generateHttpHeader(200);
        httpHeader = addHeaderField(httpHeader, "test", "field");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");
        httpHeader = addHeaderField(httpHeader, "fé", "lool");

        httpHeader = addContentType(httpHeader, fileName);
        httpHeader = addContentType(httpHeader, fileName);


        httpHeader = endHeader(httpHeader);
        printf("%s", httpHeader);

        fseek(fptr, 0, SEEK_END);
        int contentLenght = ftell(fptr);
        rewind(fptr);

        char* responseData = malloc(contentLenght+1);
        fread(responseData, contentLenght, 1, fptr);
        responseData[contentLenght]=0;
        fclose(fptr);
        erreur = send(socketClient, httpHeader, strlen(httpHeader)*sizeof(char),0);
        erreur = send(socketClient, responseData, contentLenght, 0);

        free(httpHeader); httpHeader=NULL;
        free(responseData); responseData=NULL;
        return erreur;
    }
}



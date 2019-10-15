#include "http.h"

char* generateHttpHeader(int responseCode){
    char* httpHeader = malloc(100*sizeof(char));
    switch(responseCode){
        case 200:
            strcpy(httpHeader, "HTTP/1.0 200 OK\r\n");
            break;
        case 404:
            strcpy(httpHeader, "HTTP/1.0 404 Not Found\r\n");
            break;
        case 500:
            strcpy(httpHeader, "HTTP/1.0 500 Internal Server Error\r\n");
        default:
            return 0;
        }

    return httpHeader;
}


char* addHeaderField(char* httpHeader, char* nom, char* champ){
    int fieldLen = strlen(httpHeader) + strlen(nom) + strlen(champ)+6;
    char* newHeader = malloc((fieldLen)*sizeof(char));
    strcpy(newHeader, httpHeader);
    strcat(newHeader, nom);
    strcat(newHeader, " : ");
    strcat(newHeader, champ);
    strcat(newHeader, "\r\n");


    free(httpHeader);
    return newHeader;
}

char* endHeader(char* httpHeader){
    char* newHeader = malloc((strlen(httpHeader)+2)*sizeof(char));
    strcpy(newHeader, httpHeader);
    strcat(newHeader, "\n");
    free(httpHeader);
    return newHeader;
}


char* addContentType(char* httpHeader, char* fileName){
    char* copyFn = malloc(strlen(fileName)+1); 
    strcpy(copyFn, fileName);
    char* extension = strrchr(copyFn, '.');
    if(strcmp(extension, ".jpg")==0|| strcmp(extension, ".jpeg")==0){
        httpHeader = addHeaderField(httpHeader,"content-type", "image/jpeg");
    }else if(strcmp(extension,".html")==0){
        httpHeader = addHeaderField(httpHeader,"content-type", "text/html; charset=utf-8");
    }else if(strcmp(extension, ".png")==0){
        httpHeader = addHeaderField(httpHeader,"content-type", "image/png");
    }else if(strcmp(extension, ".js")==0){
        httpHeader = addHeaderField(httpHeader,"content-type", "application/javascript; charset=utf-8");
    }else{
        httpHeader = addHeaderField(httpHeader,"content-type", "text/plain; charset=utf-8");
    }

    free(copyFn);
    return httpHeader;
}

char* addContentLength(char* httpHeader, int len){
    char* lenStr = malloc(12*sizeof(char));
    sprintf(lenStr,"%d", len);
    httpHeader = addHeaderField(httpHeader, "content-length", lenStr);
    free(lenStr);
    return httpHeader;
}

int is_file(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

int sendHttpResponse(char* fileName, int socketClient)
{
    //fileName = fileName+1; // enlever le / devant le nom de fichier
    FILE* fptr;
    printf("%s\n", fileName);
    fptr = fopen(fileName,"r");
    char* httpHeader;
    int erreur;
    int contentLenght;
    char* responseData;
    if(!fptr||!is_file(fileName)){
        httpHeader = generateHttpHeader(404);
        httpHeader = endHeader(httpHeader);
        erreur = send(socketClient, httpHeader, strlen(httpHeader)*sizeof(char),0);
        erreur = send(socketClient, "<h2>Erreur 404 : Fichier introuvable</h2>", strlen("<h2>Erreur 404 : Fichier introuvable</h2>")*sizeof(char), 0);
    }
    else{
        httpHeader = generateHttpHeader(200);

        httpHeader = addContentType(httpHeader, fileName);

        fseek(fptr, 0, SEEK_END);
        contentLenght = ftell(fptr);
        rewind(fptr);

        httpHeader = addContentLength(httpHeader, contentLenght);

        httpHeader = endHeader(httpHeader);

        responseData = malloc(contentLenght+1);
        fread(responseData, contentLenght, 1, fptr);
        responseData[contentLenght]=0;
        fclose(fptr);
        

        erreur = send(socketClient, httpHeader, strlen(httpHeader)*sizeof(char),0);
        erreur = send(socketClient, responseData, contentLenght, 0);
        free(responseData); responseData=NULL;

    }
    free(fileName);
    printf("Réponse :\n%s\n", httpHeader);
    free(httpHeader); httpHeader=NULL;
    return erreur;
}



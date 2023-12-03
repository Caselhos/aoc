#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define path "input.txt"
#define LINE_LENGTH 200

int main(){
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    long total=0;
    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    while(fgets(buffer, LINE_LENGTH,fp)){
        char *save_ptr;
        long gameId;
        char *token = strtok_r(buffer,":",&save_ptr);

        gameId = strtol(&token[4],NULL,10);
        token = strtok_r(NULL,";",&save_ptr);

        char *save_ptr2;
        int numberFailedGames=0;
        while(token){
            char *secondaryToken = strtok_r(token,",",&save_ptr2);
            while(secondaryToken){
                long nBlueCubes=0;
                long nRedCubes=0;
                long nGreenCubes=0;
                if(strstr(secondaryToken,"blue")){
                    nBlueCubes=nBlueCubes + strtol(secondaryToken,NULL,10);
                }
                if(strstr(secondaryToken,"green")){
                    nGreenCubes=nGreenCubes + strtol(secondaryToken,NULL,10);
                }
                if(strstr(secondaryToken,"red")){
                    nRedCubes=nRedCubes + strtol(secondaryToken,NULL,10);
                }
                if(nRedCubes>12 || nGreenCubes>13 || nBlueCubes >14){
                    numberFailedGames++;
                }
                secondaryToken = strtok_r(NULL,",",&save_ptr2);
            }
            token = strtok_r(NULL,";",&save_ptr);
        }
        if(numberFailedGames){
            numberFailedGames=0;
        }
        else {total=total+gameId;}
    }
    free(buffer);
    fclose(fp);
    printf("%ld\n",total);
    return EXIT_SUCCESS;
}
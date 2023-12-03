#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#define path "input.txt"
#define LINE_LENGTH 200
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


int main(){
    TICK(TIME_A);
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    long sumPowerSetCubes=0;
    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    while(fgets(buffer, LINE_LENGTH,fp)){
        char *save_ptr;
        long gameId;

        char *token = strtok_r(buffer,":",&save_ptr);
        gameId = strtol(&token[4],NULL,10);
        token = strtok_r(NULL,";",&save_ptr);

        char *save_ptr2;
        long minimumBlueCubes=0;
        long minimumRedCubes=0;
        long minimumGreenCubes=0;
        while(token){
            char *secondaryToken = strtok_r(token,",",&save_ptr2);
            while(secondaryToken){
                if(strstr(secondaryToken,"blue")){
                    if(minimumBlueCubes < strtol(secondaryToken, NULL, 10)){minimumBlueCubes=strtol(secondaryToken, NULL, 10);}
                }
                if(strstr(secondaryToken,"green")){
                    if(minimumGreenCubes < strtol(secondaryToken, NULL, 10)){minimumGreenCubes=strtol(secondaryToken, NULL, 10);}
                }
                if(strstr(secondaryToken,"red")){
                    if(minimumRedCubes < strtol(secondaryToken, NULL, 10)){minimumRedCubes=strtol(secondaryToken, NULL, 10);}
                }
                secondaryToken = strtok_r(NULL,",",&save_ptr2);
            }
            token = strtok_r(NULL,";",&save_ptr);
        }
        sumPowerSetCubes=sumPowerSetCubes+minimumGreenCubes*minimumRedCubes*minimumBlueCubes;
    }
    free(buffer);
    fclose(fp);
    printf("%ld\n",sumPowerSetCubes);
    TOCK(TIME_A);
    return EXIT_SUCCESS;
}
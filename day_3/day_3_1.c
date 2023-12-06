#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#define path "input.txt"
#define LINE_LENGTH 150
#define ROW_LENGTH 140
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)

bool checkNeighbours(char **array,size_t x,size_t y,const char *nString,bool rUpper,bool rLower, bool rForward,bool rBackward){
    int n=0;
    u_long wow = strlen(nString);
        if(!rUpper && !rForward){
            if(ispunct(array[y-1][x+strlen(nString)])){
                n++;
            }
        }
        if(!rLower && !rForward){
            if(ispunct(array[y+1][x+strlen(nString)])){
                n++;
            }
        }
        if(!rUpper && !rBackward){
            if(ispunct(array[y-1][x-1])){
                n++;
            }
        }
        if(!rLower&& !rBackward){
            if(ispunct(array[y+1][x-1])){
                n++;
            }
        }
        if(!rForward){
            if(ispunct(array[y][x+strlen(nString)])){
                n++;
            }
        }
        if(!rBackward){
            if(ispunct(array[y][x-1])){
                n++;
            }
        }
        if(!rUpper){
            for(size_t test=0;test<wow;test++){
                if(ispunct(array[y-1][x+test])){
                    n++;
                }
            }
        }
        if(!rLower){
            for(size_t test=0;test<wow;test++){
                if(ispunct(array[y+1][x+test])){
                    n++;
                }
            }
        }
    if(n!=0){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    TICK(TIME_A);
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    char **array = malloc(ROW_LENGTH * sizeof(char *));
    for(size_t x=0;x<ROW_LENGTH;x++){
        array[x] = malloc(LINE_LENGTH * sizeof(char));
    }
    int z=0;
    while(fgets(array[z], LINE_LENGTH,fp)){
        z++;
    }
    long total=0;
    for(size_t y=0;y<ROW_LENGTH;y++) {
        for (size_t x = 0; x < LINE_LENGTH; x++) {
            if (array[y][x] == '.') {
                array[y][x] = ' ';
            }
        }
    }
    for(size_t y=0;y<ROW_LENGTH;y++){
        for(size_t x=0;x<LINE_LENGTH;x++){
            if(isdigit(array[y][x])){
                long number = strtol(&array[y][x],NULL,10);
                char numberString[4];
                sprintf(numberString,"%ld",number);
                bool rUpper = false;
                bool rLower = false;
                bool rForward = false;
                bool rBackward = false;
                if(y==0){
                    rUpper=true;
                }
                if(x==0){
                    rBackward=true;
                }
                if(y==139){
                    rLower=true;
                }
                if(x+strlen(numberString)==140){
                    rForward=true;
                }
                if(checkNeighbours(array,x,y,numberString,rUpper,rLower,rForward,rBackward)){
                    total=total+number;
                }

                x=x+strlen(numberString);
            }
        }
    }
    for(size_t x=0;x<ROW_LENGTH;x++){
        free(array[x]);
    }
    free(array);
    fclose(fp);
    printf("%ld",total);
    TOCK(TIME_A);
    return EXIT_SUCCESS;
}
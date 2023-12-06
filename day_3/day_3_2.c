#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#define path "input.txt"
#define LINE_LENGTH 150
#define ROW_LENGTH 150
#define TICK(X) clock_t X = clock()
#define TOCK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)

long checkNeighbours(char **array,size_t x,size_t y,bool rUpper,bool rLower, bool rForward,bool rBackward){
    int z;
    int testing[8]={0};
    int testingPositionsAxis[8][2]={{0,0}};
    if(!rUpper && !rForward){
        if(isdigit(array[y-1][x+1])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y-1][(x+1)-z])){
                    break;
                }
            }
            testingPositionsAxis[0][1]=y-1;
            testingPositionsAxis[0][0]=(x+1)-z+1;
            testing[0]=strtol(&array[y-1][(x+1)-z],NULL,10);

        }
    }
    if(!rLower && !rForward){
        if(isdigit(array[y+1][x+1])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y+1][(x+1)-z])){
                    break;
                }
            }
            testingPositionsAxis[1][1]=y+1;
            testingPositionsAxis[1][0]=(x+1)-z+1;
            testing[1]=strtol(&array[y+1][(x+1)-z],NULL,10);

        }
    }
    if(!rUpper && !rBackward){
        if(isdigit(array[y-1][x-1])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y-1][(x-1)-z])){
                    break;
                }
            }
            testingPositionsAxis[2][1]=y-1;
            testingPositionsAxis[2][0]=(x-1)-z+1;
            testing[2]=strtol(&array[y-1][(x-1)-z],NULL,10);

        }
    }
    if(!rLower&& !rBackward){
        if(isdigit(array[y+1][x-1])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y+1][(x-1)-z])){
                    break;
                }
            }
            testingPositionsAxis[3][1]=y+1;
            testingPositionsAxis[3][0]=(x-1)-z+1;
            testing[3]=strtol(&array[y+1][(x-1)-z],NULL,10);

        }
    }
    if(!rForward){
        if(isdigit(array[y][x+1])){
            testingPositionsAxis[4][1]=y;
            testingPositionsAxis[4][0]=(x+1);
            testing[4]=strtol(&array[y][x+1],NULL,10);

        }
    }
    if(!rBackward){
        if(isdigit(array[y][x-1])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y][(x-1)-z])){
                    break;
                }
            }
            testingPositionsAxis[5][1]=y;
            testingPositionsAxis[5][0]=(x-1)-z+1;
            testing[5]=strtol(&array[y][(x-1)-z],NULL,10);

        }
    }
    if(!rUpper){
        if(isdigit(array[y-1][x])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y-1][x-z])){
                    break;
                }
            }
            testingPositionsAxis[6][1]=y-1;
            testingPositionsAxis[6][0]=x-z+1;
            testing[6]=strtol(&array[y-1][x-z],NULL,10);

        }
    }
    if(!rLower){
        if(isdigit(array[y+1][x])){
            for(z=0;z<INT_MAX;z++){
                if(!isdigit(array[y+1][x-z])){
                    break;
                }
            }
            testingPositionsAxis[7][1]=y+1;
            testingPositionsAxis[7][0]=x-z+1;
            testing[7]=strtol(&array[y+1][x-z],NULL,10);

        }
    }
    int n=8;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; ) {
            if (testingPositionsAxis[i][0] == testingPositionsAxis[j][0] && testingPositionsAxis[i][1] == testingPositionsAxis[j][1]) {
                testingPositionsAxis[j][0] = testingPositionsAxis[n-1][0];
                testingPositionsAxis[j][1] = testingPositionsAxis[n-1][1];
                n--;
            } else {
                j++;
            }
        }
    }
    int idk=0;
    long total=1;
    for (int i = 0; i < n; i++){
        if(testingPositionsAxis[i][0]==0 && testingPositionsAxis[i][1]==0) {

        }
        else{
            long test=strtol(&array[testingPositionsAxis[i][1]][testingPositionsAxis[i][0]],NULL,10);
            total=total* test;
            idk++;
        }
    }
    if(total != 1 && idk ==2){
        return total;
    }
    return 0;
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
            if(array[y][x]=='*'){
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
                if(x==139){
                    rForward=true;
                }
                total=total+checkNeighbours(array,x,y,rUpper,rLower,rForward,rBackward);
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
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#define path "input.txt"
#define LINE_LENGTH 40
#define N_RACES 4
#define TIME_OFFSET 5
#define DISTANCE_OFFSET 9
#define TICK(X) clock_t X = clock()
#define TACK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


int main(){
    TICK(TIME_A);
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }
    int arrayTime[N_RACES]={0};
    int arrayDistance[N_RACES]={0};
    int iteration=0;
    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    while(fgets(buffer, LINE_LENGTH,fp)){
        if(iteration) sscanf(&buffer[DISTANCE_OFFSET],"%d %d %d %d",&arrayDistance[0],&arrayDistance[1],&arrayDistance[2],&arrayDistance[3]);
        sscanf(&buffer[TIME_OFFSET],"%d %d %d %d",&arrayTime[0],&arrayTime[1],&arrayTime[2],&arrayTime[3]);
        iteration++;
    }
    free(buffer);
    fclose(fp);
    int arrayNumberWaysBeatRecord[N_RACES]={0};
    for(int x=0;x<N_RACES;x++){
        for(int y=0;y<arrayTime[x];y++){
            int racingTime=arrayTime[x]-y;
            int travel=racingTime*y;
            if(travel>arrayDistance[x]){
                arrayNumberWaysBeatRecord[x]++;
            }
        }
    }
    int total=1;
    for(int x=0;x<N_RACES;x++){
        total = total* arrayNumberWaysBeatRecord[x];
    }
    printf("Part 1 = %d\n",total);
    char completeTime[50]={};
    char completeRange[50]={};
    for(int x=0;x<N_RACES;x++){
        char str1[5]={};
        char str2[5]={};
        sprintf(str1,"%d",arrayTime[x]);
        strcat(completeTime,str1);
        sprintf(str2,"%d",arrayDistance[x]);
        strcat(completeRange,str2);
    }
    long completeRangeLong = strtol(completeRange,NULL,10);
    long completeTimeLong = strtol(completeTime,NULL,10);
    long nWays=0;
    long previousNumber=-1;
    for(long y=0;y<completeTimeLong;y++){
        long racingTime=completeTimeLong-y;
        long travel=racingTime*y;
        if(travel==previousNumber){
            break;
        }
        if(travel>completeRangeLong){
            previousNumber=travel;
            nWays++;
        }
    }
    printf("Part 2 = %ld\n",nWays);
    TACK(TIME_A);
    return EXIT_SUCCESS;
}
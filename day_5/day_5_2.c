#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>
#include <ctype.h>
#include <limits.h>

#define path "input.txt"
#define LINE_LENGTH 250
#define SEED_OFFSET 7
#define ARRAY_LENGTH 50
#define ARRAY_SIZE 3
#define TICK(X) clock_t X = clock()
#define TACK(X) printf("time %s: %g sec.\n", (#X), (double)(clock() - (X)) / CLOCKS_PER_SEC)


long calculateProgress(long seed,long array[ARRAY_SIZE][ARRAY_SIZE]);
long calculateProgressSpecial(long seed,long array[ARRAY_LENGTH][ARRAY_SIZE]);
void divideInputFile(char const *buffer,long array[ARRAY_LENGTH][ARRAY_SIZE],int index);


int main(){
    TICK(TIME_A);
    FILE * fp = fopen(path,"r");
    if(fp == NULL){
        perror("ERROR");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(LINE_LENGTH * sizeof(char));
    char *seeds = malloc(LINE_LENGTH *sizeof(char));
    long seedToSoil[ARRAY_SIZE][ARRAY_SIZE]={};
    long soilToFertilizer[ARRAY_LENGTH][ARRAY_SIZE]={};
    long fertilizerToWater[ARRAY_LENGTH][ARRAY_SIZE]={};
    long waterToLight[ARRAY_LENGTH][ARRAY_SIZE]={};
    long lightToTemperature[ARRAY_LENGTH][ARRAY_SIZE]={};
    long temperatureToHumidity[ARRAY_LENGTH][ARRAY_SIZE]={};
    long humidityToLocation[ARRAY_LENGTH][ARRAY_SIZE]={};
    int iteration=0;
    int index=0;
    while(fgets(buffer, LINE_LENGTH,fp)) {

        if(strcmp(buffer,"\n")==0){
            iteration++;
            index=0;
        }
        int initialChar=isdigit(buffer[0]);

        if(iteration==0){
            strncpy(seeds,buffer+SEED_OFFSET, strlen(buffer));
            seeds[strlen(seeds)-1]='\0';
        }
        if(iteration==1 && initialChar){
            long try;
            int index2=0;
            char *endPtr;
            try= strtol(buffer,&endPtr,10);
            while(index2!=3){
                seedToSoil[index][index2]=try;
                index2++;
                try = strtol(endPtr,&endPtr,10);
            }
            index++;
        }
        if(iteration==2 && initialChar){
            divideInputFile(buffer,soilToFertilizer,index);
            index++;
        }
        if(iteration==3 && initialChar){
            divideInputFile(buffer,fertilizerToWater,index);
            index++;
        }
        if(iteration==4 && initialChar){
            divideInputFile(buffer,waterToLight,index);
            index++;
        }
        if(iteration==5 && initialChar){
            divideInputFile(buffer,lightToTemperature,index);
            index++;
        }
        if(iteration==6 && initialChar){
            divideInputFile(buffer,temperatureToHumidity,index);
            index++;
        }
        if(iteration==7 && initialChar){
            divideInputFile(buffer,humidityToLocation,index);
            index++;
        }


    }
    free(buffer);
    fclose(fp);
    long start;
    long range;
    char *endPtr;
    start= strtol(seeds,&endPtr,10);
    range= strtol(endPtr,&endPtr,10);
    long result=LONG_MAX;

    while(range){
        for(long x=start;x<(start+range);x++){
            long variable=0;
            variable=calculateProgress(x,seedToSoil);
            variable= calculateProgressSpecial(variable,soilToFertilizer);
            variable= calculateProgressSpecial(variable,fertilizerToWater);
            variable= calculateProgressSpecial(variable,waterToLight);
            variable= calculateProgressSpecial(variable,lightToTemperature);
            variable= calculateProgressSpecial(variable,temperatureToHumidity);
            variable= calculateProgressSpecial(variable,humidityToLocation);
            if(result>=variable){
                result=variable;
            }
        }
        start = strtol(endPtr,&endPtr,10);
        range= strtol(endPtr,&endPtr,10);
    }
    printf("%ld\n",result);
    TACK(TIME_A);
    return EXIT_SUCCESS;
}

long calculateProgress(long seed,long array[ARRAY_SIZE][ARRAY_SIZE]){
    size_t x;
    for(x=0;x<ARRAY_SIZE;x++){
        if(array[x][1]+array[x][2]>=seed && array[x][1]<=seed){
            long differece= labs(array[x][1] - array[x][0]);
            if(array[x][0]>array[x][1]){
                return seed+differece;
            }
            if(array[x][0]<array[x][1]){
                return seed-differece;
            }
        }
    }
    return seed;
}

long calculateProgressSpecial(long seed,long array[ARRAY_LENGTH][ARRAY_SIZE]){
    size_t x;
    for(x=0;x<ARRAY_LENGTH;x++){
        if(array[x][1]+array[x][2]>=seed && array[x][1]<=seed){
            long differece= labs(array[x][1] - array[x][0]);
            if(array[x][0]>array[x][1]){
                return seed+differece;
            }
            if(array[x][0]<array[x][1]){
                return seed-differece;
            }

        }
    }
    return seed;

}

void divideInputFile(char const *buffer,long array[ARRAY_LENGTH][ARRAY_SIZE],int index){
    int index2=0;
    char *endPtr;
    long try= strtol(buffer,&endPtr,10);
    while(index2!=3){
        array[index][index2]=try;
        index2++;
        try = strtol(endPtr,&endPtr,10);
    }
}